#include "Scene.h"
#include "Application.h"

Scene::Scene()
{
	ParticleSystem = std::make_unique<ParticleSystem3D>();
}

Scene::~Scene()
{
}

void Scene::update(float DeltaTime)
{
	t += DeltaTime;
	if (t >= 4.0f && t <= 5.0f)
	{
		t = 6.0f;

		ParticleSystem->SpawnEmitter(glm::vec3(1.0f, 0.0f, 0.0f), 5, 2.0f, glm::vec3(3.0f, 5.0f, -5.0f), Axis::Z, GeometryGenerator::Mesh::CUBE);
	}

	// Orbiting lights
	for (auto l : m_vPointLights) {
		if (TheApp::Instance()->m_userInterface->m_bLightShouldUpdate) {
			TheApp::Instance()->strength += 1.5f;
	
			l->setStrength((TheApp::Instance()->m_userInterface->lflickerRange * cos(TheApp::Instance()->strength * Util::DegToRad())) + TheApp::Instance()->m_userInterface->lFactor);
		}
		l->setPosition(glm::vec3(3 * cos((TheApp::Instance()->angleDelta + (l->index == 0 ? 0 : 180.0f)) * Util::DegToRad()), l->getPosition().y, 3 * sin((TheApp::Instance()->angleDelta + (l->index == 0 ? 0 : 180.0f)) * Util::DegToRad())));
		l->updateBuffers(TheApp::Instance()->getCoreProgram());
	}
	// Waves
	for (int i = 0; i < geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->getNumVertices(); i++)
	{
		geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->verticies[i].m_xDist += 0.0625f;
		geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->verticies[i].setPosition
		(
			glm::vec3
			(
				geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->verticies[i].getPosition().x,
				0.2f * sin(0.5f * geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->verticies[i].m_xDist),
				geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->verticies[i].getPosition().z
			)
		);
	}
	// Delete old memory
	geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->deleteBuffers();

	// Re-generate the vertex buffers of the waves respective to the new heights
	geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->generateBuffers();

	//cntr1 += 3.0f;

	//TheApp::Instance()->m_userInterface->theta = cos_radians(cntr1);
	//TheApp::Instance()->m_userInterface->pi = cos_radians(cntr2);
	cntr1 += 70.0f * DeltaTime;
	angle = 30.0f * cos_radians(cntr1) - 90.0f;

	cntr2 += 60.0f * DeltaTime;
	float x = (5.5f + cos_radians(angle) * .25f) * cos_radians(angle);
	float z = cos_radians(cntr2)*1.f;
	float y = (5.5f + cos_radians(angle) * .25f) * sin_radians(angle);

	// swing around
	//float x = (2.5f +cos_radians(cntr2) * .75f) * cos_radians(cntr1);
	//float z = (2.5f +cos_radians(cntr2) * .75f) * sin_radians(cntr1);
	//float y = -4.0f + cos_radians(cntr2) * .5f;


	//float x = -6.0f * sin_radians(TheApp::Instance()->m_userInterface->pi) * cos_radians(TheApp::Instance()->m_userInterface->theta);
	//float y = -6.0f * sin_radians(TheApp::Instance()->m_userInterface->pi) * sin_radians(TheApp::Instance()->m_userInterface->theta);
	//float z = -6.0f * cos_radians(TheApp::Instance()->m_userInterface->pi);

	//float x = -6.0f * sin_radians(TheApp::Instance()->m_userInterface->pi) * cos_radians(TheApp::Instance()->m_userInterface->theta);
	//float y = -6.0f * sin_radians(TheApp::Instance()->m_userInterface->pi) * sin_radians(TheApp::Instance()->m_userInterface->theta);
	//float z = -6.0f * cos_radians(TheApp::Instance()->m_userInterface->pi);

	//0, 1, 
	swingArm.verticies[0] = Vertex(glm::vec3(x + -0.5f, y +  -0.5f,z +  -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f));
	swingArm.verticies[1] = Vertex(glm::vec3(x + 0.5f,  y + -0.5f, z + -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f));
	swingArm.verticies[2] = Vertex(glm::vec3(x + 0.5f,  y + -0.5f, z + +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.5f, -0.5f, +0.5f));
	swingArm.verticies[3] = Vertex(glm::vec3(x + -0.5f, y +  -0.5f,z +  +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-0.5f, -0.5f, +0.5f));


	swingArm.verticies[8] = Vertex(glm::vec3(x + -0.5f, y + -0.5f, z + +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, +0.5f));
	swingArm.verticies[9] = Vertex(glm::vec3(x + 0.5f, y + -0.5f, z + +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, +0.5f));


	swingArm.verticies[12] = Vertex(glm::vec3(x + -0.5f, y + -0.5f, z + -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f));
	swingArm.verticies[13] = Vertex(glm::vec3(x + 0.5f, y + -0.5f, z + -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f));//12,13
	
	
	swingArm.verticies[16] = Vertex(glm::vec3(x+ +0.5f, y + -0.5f, z + -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(+0.5f, -0.5f, -0.5f));
	swingArm.verticies[17] = Vertex(glm::vec3(x+ +0.5f, y + -0.5f, z + +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(+0.5f, -0.5f, +0.5f));//16,17

	swingArm.verticies[21] = Vertex(glm::vec3(x + -0.5f, y + -0.5f, z + -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f));
	swingArm.verticies[20] = Vertex(glm::vec3(x + -0.5f, y + -0.5f, z + +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-0.5f, -0.5f, +0.5f));//21, 20
	
	swingArm.deleteBuffers();
	swingArm.generateBuffers();
	

}

void Scene::draw(float DeltaTime)
{
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(TheApp::Instance()->getCoreProgram());

	for (auto ri : m_vRenderItems)
	{
		ri->update(this);
		ri->draw(this);
	}
	TheShaderManager::Instance()->SetFragmentLightAndColourOnly(TheApp::Instance()->getCoreProgram());
	Util::Transform(TheApp::Instance()->getCoreProgram(), glm::vec3(0.0f, 9.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	swingArm.bindVertexArrayObject();
	glDrawElements(GL_LINE_LOOP, swingArm.getNumIndicies(), GL_UNSIGNED_INT, 0);

	ParticleSystem->UpdateParticles(DeltaTime);
}

void Scene::setup()
{
	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(3, 0, 0), glm::vec3(0.5f), 1.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	m_vPointLights.back()->updateBuffers(TheApp::Instance()->getCoreProgram());

	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(-3, 0, 0), glm::vec3(0.5f), 1.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	m_vPointLights.back()->updateBuffers(TheApp::Instance()->getCoreProgram());

	// These must be in sequential order.
	geoGen.createMesh(GeometryGenerator::CUBE);
	geoGen.mGeometryMesh[GeometryGenerator::CUBE]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::PYRAMID);
	geoGen.mGeometryMesh[GeometryGenerator::PYRAMID]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::SPHEAR);
	geoGen.mGeometryMesh[GeometryGenerator::SPHEAR]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::PLANE);
	geoGen.mGeometryMesh[GeometryGenerator::PLANE]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::SKULL);
	geoGen.mGeometryMesh[GeometryGenerator::SKULL]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::CAR);
	geoGen.mGeometryMesh[GeometryGenerator::CAR]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::WATER_PLANE);
	geoGen.mGeometryMesh[GeometryGenerator::WATER_PLANE]->generateBuffers();

	TheShaderManager::Instance()->SetFragmentAlphaBlend(TheApp::Instance()->getCoreProgram(), 1.0f);

	// Render Item:
	/*
		Mesh type, 
		Fragment style, 
		material, 
		translation, scale, 
		rotationAxis, 
		angle (based on rotation axis ^)
	*/
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::PLANE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "grass", 1.0f, glm::vec3(0.0f, -3.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));

	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::WATER_PLANE , FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "water", 0.3f, glm::vec3(0.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bShouldAnimate = true;
	m_vRenderItems.back()->m_bHeightEffects = true;
	
	// Water plane will animate. To do this we simply use a uniform vec2 variable in the fragment shader
	// as a uv that updates in the game loop. The result is the illusion of flowing water.
	
	// Alternatively, we could just access each uv and increase them and just re-bind the vertex array buffer.
	// ^ But this would be very performance heavy

	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SPHEAR, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "theSims", 1.0f,glm::vec3(-0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SPHEAR, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "theSims", 1.0f,glm::vec3(-0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SPHEAR, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "theSims", 1.0f,glm::vec3(-0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SPHEAR, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "theSims", 1.0f,glm::vec3(+0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SPHEAR, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "theSims", 1.0f,glm::vec3(+0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SPHEAR, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "theSims", 1.0f,glm::vec3(+0.0f, +0.5f - 0.03f, +0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::PYRAMID, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "stoneBrick", 1.0f, glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(0.8f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::PYRAMID, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "fence", 1.0f, glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "stoneBrick", 1.0f, glm::vec3(0.0f, -0.65f*1.2 - (0.9f / 2.0f), 0.0f), glm::vec3(2.4f, 1.2f, 2.4f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SKULL, FragmentStyle::LIGHT_AND_COLOR_ONLY, "null", 1.0f, glm::vec3(-0.85f, -0.62f, 0.0f), glm::vec3(0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SKULL, FragmentStyle::LIGHT_AND_COLOR_ONLY, "null", 1.0f, glm::vec3(+0.85f, -0.62f, 0.0f), glm::vec3(0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 270.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SKULL, FragmentStyle::LIGHT_AND_COLOR_ONLY, "null", 1.0f, glm::vec3(0.0f, -0.62f, +0.85f), glm::vec3(0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SKULL, FragmentStyle::LIGHT_AND_COLOR_ONLY, "null", 1.0f, glm::vec3(0.0f, -0.62f, -0.85f), glm::vec3(0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::SPHEAR, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "stoneBrick", 1.0f, glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	
	// Bob #1 ----------------------------
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(+7.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bApplyPhysics = true;
	
	

	// Comment this out to see the effect of all the floaters being in the same range
	m_vRenderItems.back()->m_y = random_float_in_range(0.5f, 7.5f);
	float distance = glm::length(Util::waveCentre - m_vRenderItems.back()->transform->position);
	m_vRenderItems.back()->currY = 0.5f * sin(0.5f * distance);
	m_vRenderItems.back()->m_desiredFactor = distance;
	// -----------------------------------

	// Bob #2 ----------------------------
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(-7.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, -12.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bApplyPhysics = true;
	
	// Comment this out to see the effect of all the floaters being in the same range
	m_vRenderItems.back()->m_y = random_float_in_range(0.5f, 7.5f);	  // Prevent all floaters from bobbing at the same rate
	distance = glm::length(Util::waveCentre - m_vRenderItems.back()->transform->position);
	m_vRenderItems.back()->currY = 0.5f * sin(0.5f * distance);
	m_vRenderItems.back()->m_desiredFactor = distance;
	// -----------------------------------

	// Bob #3 ----------------------------
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(0.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bApplyPhysics = true;
	
	// Comment this out to see the effect of all the floaters being in the same range
	m_vRenderItems.back()->m_y = random_float_in_range(0.5f, 7.5f);	  // Prevent all floaters from bobbing at the same rate
	distance = glm::length(Util::waveCentre - m_vRenderItems.back()->transform->position);
	m_vRenderItems.back()->currY = 0.5f * sin(0.5f * distance);
	m_vRenderItems.back()->m_desiredFactor = distance;
	// -----------------------------------

	// Bob #4 ----------------------------
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(-4.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, -9.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bApplyPhysics = true;
	
	// Comment this out to see the effect of all the floaters being in the same range
	m_vRenderItems.back()->m_y = random_float_in_range(0.5f, 7.5f);   // Prevent all floaters from bobbing at the same rate
	distance = glm::length(Util::waveCentre - m_vRenderItems.back()->transform->position);
	m_vRenderItems.back()->currY = 0.5f * sin(0.5f * distance);
	m_vRenderItems.back()->m_desiredFactor = distance;
	// -----------------------------------

	// Car
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CAR, FragmentStyle::LIGHT_AND_COLOR_ONLY, "null", 1.0f, glm::vec3(-7.0f, 2.0f+-0.65f*1.2 - (0.9f / 2.0f), 0.0f), glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));

	Camera::UpdateCameraFacing(TheApp::Instance()->getWindow());
	

	swingArm.setPrimitiveType(GL_QUADS);
	swingArm.setNumIndicies(24);
	swingArm.setNumVertices(24);
	swingArm.verticies = new Vertex[swingArm.getNumVertices()]
	{

		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-0.5f, -0.5f, +0.5f)),

		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, 0.5f, -0.5f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, 0.5f, -0.5f)),
		Vertex(glm::vec3(0.5f, 0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.5f, 0.5f, +0.5f)),
		Vertex(glm::vec3(-0.5f, 0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(-0.5f, 0.5f, +0.5f)),

		Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.5f, +0.5f, +0.5f)),
		Vertex(glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-0.5f, +0.5f, +0.5f)),

		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(0.5f, +0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.5f, +0.5f, -0.5f)),
		Vertex(glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-0.5f, +0.5f, -0.5f)),

		Vertex(glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(+0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(+0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(+0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(+0.5f, +0.5f, +0.5f)),
		Vertex(glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(+0.5f, +0.5f, -0.5f)),

		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(-0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),glm::vec3(-0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(-0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),glm::vec3(-0.5f, +0.5f, +0.5f)),
		Vertex(glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-0.5f, +0.5f, -0.5f)),


	};
	swingArm.indicies = new GLuint[swingArm.getNumIndicies()];

	for (int i = 0; i < swingArm.getNumIndicies(); i++)
	{
		swingArm.indicies[i] = i;
	}
	swingArm.generateBuffers();


}

void Scene::clean()
{
	for (auto it : m_vPointLights)
	{
		it->clean(TheApp::Instance()->getCoreProgram());
		delete it;
		it = nullptr;
	}
	m_vPointLights.shrink_to_fit();
}
