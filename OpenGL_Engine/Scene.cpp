#include "Scene.h"
#include "Application.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
	for (auto l : m_vPointLights) {
		if (TheApp::Instance()->m_userInterface->mLightShouldUpdate) {
			TheApp::Instance()->strength += 1.5f;
	
			l->setStrength((TheApp::Instance()->m_userInterface->lflickerRange * cos(TheApp::Instance()->strength * Util::DegToRad())) + TheApp::Instance()->m_userInterface->lFactor);
		}
		l->setPosition(glm::vec3(3 * cos((TheApp::Instance()->angleDelta + (l->index == 0 ? 0 : 180.0f)) * Util::DegToRad()), l->getPosition().y, 3 * sin((TheApp::Instance()->angleDelta + (l->index == 0 ? 0 : 180.0f)) * Util::DegToRad())));
		static_cast<PointLight*>(l)->updateBuffers(TheApp::Instance()->getCoreProgram());
	}
		
}

void Scene::draw()
{
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(TheApp::Instance()->getCoreProgram());

	for (auto ri : m_vRenderItems)
	{
		ri->update(this);
		ri->draw(this);
	}
}

void Scene::setup()
{
	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(3, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f), 1.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	static_cast<PointLight*>(m_vPointLights.back())->updateBuffers(TheApp::Instance()->getCoreProgram());

	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(-3, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f), 1.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	static_cast<PointLight*>(m_vPointLights.back())->updateBuffers(TheApp::Instance()->getCoreProgram());

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

	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE , FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "water", 0.2f, glm::vec3(0.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, 0.0f), glm::vec3(65.f, 0.01f, 65.f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bShouldAnimate = true;
	// Future project, ice blocks drop from the sky and bob in the ocean

	// Water plane will animate. To do this we simply use a uniform vec2 variable in the fragment shader
	// as a uv that updates in the game loop. The result is the illusion of flowing water.
	
	// Alternatively, we could just access each uv and increase them and just re-bind the vertex array buffer.
	// (potentially a slower method without using Dynamic Draw calls).

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
	m_vRenderItems.back()->m_fCntr = random_float_in_range(0.5f, 5.5f);   // Prevent all floaters from bobbing at the same rate
	// -----------------------------------

	// Bob #2 ----------------------------
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(-7.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, -12.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bApplyPhysics = true;
	
	// Comment this out to see the effect of all the floaters being in the same range
	m_vRenderItems.back()->m_fCntr = random_float_in_range(0.5f, 7.5f);	  // Prevent all floaters from bobbing at the same rate
	// -----------------------------------

	// Bob #3 ----------------------------
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(0.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, -8.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bApplyPhysics = true;
	
	// Comment this out to see the effect of all the floaters being in the same range
	m_vRenderItems.back()->m_fCntr = random_float_in_range(0.5f, 7.5f);	  // Prevent all floaters from bobbing at the same rate
	// -----------------------------------

	// Bob #4 ----------------------------
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "ice", 0.5f, glm::vec3(-4.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, -9.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bApplyPhysics = true;
	
	// Comment this out to see the effect of all the floaters being in the same range
	m_vRenderItems.back()->m_fCntr = random_float_in_range(0.5f, 7.5f);   // Prevent all floaters from bobbing at the same rate
	// -----------------------------------

	Camera::UpdateCameraFacing(TheApp::Instance()->getWindow());


}

void Scene::clean()
{
	for (auto it : m_vPointLights)
	{
		static_cast<PointLight*>(it)->clean(TheApp::Instance()->getCoreProgram());
		delete it;
		it = nullptr;
	}
	m_vPointLights.shrink_to_fit();
}
