#include "Scene.h"
#include "Application.h"
void mouse_btn_down_callback(GLFWwindow* window, int button, int action, int mods)
{
	if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &Camera::mouseX, &Camera::mouseY);
	}
}
void window_resize_callback(GLFWwindow* window, int x, int y)
{
	GLint _width;
	GLint _height;
	glfwGetWindowSize(window, &_width, &_height);

	TheApp::Instance()->frameBufferW = _width;
	TheApp::Instance()->frameBufferH = _height;

	// Change the view port size respective to the new window size.
	glViewport(0, 0, _width, _height);


}
Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
	// Not sure what to do about these yet.

	for (auto light : m_vPointLights) {
		if (TheApp::Instance()->mUserInterface->mLightShouldUpdate) {
			TheApp::Instance()->strength += 1.5f;
	
			light->setStrength((TheApp::Instance()->mUserInterface->lflickerRange * cos(TheApp::Instance()->strength * Util::DegToRad())) + TheApp::Instance()->mUserInterface->lFactor);
		}
		light->setPosition(glm::vec3(3 * cos((TheApp::Instance()->angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad()), light->getPosition().y, 3 * sin((TheApp::Instance()->angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad())));
	}
}

void Scene::Render()
{
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(TheApp::Instance()->getCoreProgram());
	
	for (auto ri : m_vRenderItems)
	{
		if (ri->m_bShouldAnimate)
			ri->update(this);

		ri->draw(this);
	}

}

void Scene::Setup()
{
	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(3, 0, 0), glm::vec3(1), 2.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	m_vPointLights.back()->updateBuffers(TheApp::Instance()->getCoreProgram());

	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(-3, 0, 0), glm::vec3(1), 2.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	m_vPointLights.back()->updateBuffers(TheApp::Instance()->getCoreProgram());

	geoGen.createMesh(GeometryGenerator::CUBE);
	geoGen.mGeometry[GeometryGenerator::CUBE]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::PYRAMID);
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::SPHEAR);
	geoGen.mGeometry[GeometryGenerator::SPHEAR]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::PLANE);
	geoGen.mGeometry[GeometryGenerator::PLANE]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::SKULL);
	geoGen.mGeometry[GeometryGenerator::SKULL]->generateBuffers();

	TheShaderManager::Instance()->SetFragmentAlphaBlend(TheApp::Instance()->getCoreProgram(), 1.0f);

	mMaterialMap["ice"].load("ice.png");
	mMaterialMap["brick"].load("Brick5.png");
	mMaterialMap["theSims"].load("TheSims.jfif");
	mMaterialMap["fence"].load("Fence.png");
	mMaterialMap["grass"].load("tile.png");
	mMaterialMap["stoneBrick"].load("StoneBrick.jpg");
	mMaterialMap["water"].load("water.png");

	// Render Item:
	// Mesh type, Fragment style, material, translation, scale, rotationAxis, angle.s
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::PLANE, FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "grass", 1.0f, glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.push_back(new RenderItem(GeometryGenerator::Mesh::CUBE , FragmentStyle::TEXTURE_AND_LIGHT_ONLY, "water", 0.2f, glm::vec3(0.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, 0.0f), glm::vec3(65.f, 0.01f, 65.f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	m_vRenderItems.back()->m_bShouldAnimate = true;

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


	Camera::UpdateCameraFacing(TheApp::Instance()->getWindow());

	glfwSetMouseButtonCallback(TheApp::Instance()->getWindow(), mouse_btn_down_callback);
	glfwSetWindowSizeCallback(TheApp::Instance()->getWindow(), window_resize_callback);

}

void Scene::Clean()
{
	for (auto it : m_vPointLights)
	{
		it->clean(TheApp::Instance()->getCoreProgram());
		delete it;
		it = nullptr;
	}
	m_vPointLights.shrink_to_fit();
}
