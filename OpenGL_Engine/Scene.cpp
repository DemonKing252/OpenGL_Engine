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

	TheApp::GetInstance()->frameBufferW = _width;
	TheApp::GetInstance()->frameBufferH = _height;

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
	for (PointLight* light : m_vPointLights) {
		if (TheApp::GetInstance()->mUserInterface->mLightShouldUpdate) {
			TheApp::GetInstance()->strength += 1.5f;

			light->setStrength((TheApp::GetInstance()->mUserInterface->lflickerRange * cos(TheApp::GetInstance()->strength * Util::DegToRad())) + TheApp::GetInstance()->mUserInterface->lFactor);
		}
		light->setPosition(glm::vec3(3 * cos((TheApp::GetInstance()->angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad()), light->getPosition().y, 3 * sin((TheApp::GetInstance()->angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad())));
	}
}

void Scene::Render()
{
	// Bind a texture ID (an unsigned integer that points to a texture buffer)
	mMaterialMap["theSims"].bindTexture();

	// Important Order: Scale-Rotate-Translate
	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(0.0f, 0.5f - 0.12f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

	geoGen.mGeometry[GeometryGenerator::SPHEAR]->bindVAO();
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(Application::GetInstance()->getCoreProgram(), glm::vec3(-0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(-0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(+0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(+0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	mMaterialMap["grass"].bindTexture();
	TheShaderManager::Instance()->SetFragmentAllTypes(TheApp::GetInstance()->getCoreProgram());

	geoGen.mGeometry[GeometryGenerator::PLANE]->bindVAO();
	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PLANE);

	mMaterialMap["stoneBrick"].bindTexture();
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(TheApp::GetInstance()->getCoreProgram());
	geoGen.mGeometry[GeometryGenerator::SPHEAR]->bindVAO();
	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	// Set a texture ID to be the active one in memory
	mMaterialMap["theSims"].bindTexture();

	// Tell the fragment shader to only map out vertex colours
	TheShaderManager::Instance()->SetFragmentColourOnly(TheApp::GetInstance()->getCoreProgram());
	for (PointLight* light : m_vPointLights)
	{
		Util::Transform(TheApp::GetInstance()->getCoreProgram(), light->getPosition(), glm::vec3(0.5), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		geoGen.draw(GeometryGenerator::SPHEAR);
	}
	// Tell the fragment shader to only map out lighting and vertex textures
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(TheApp::GetInstance()->getCoreProgram());

	mMaterialMap["brick"].bindTexture();

	// Set a vertex vao to be the active one in memory
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->bindVAO();
	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PYRAMID);

	TheShaderManager::Instance()->SetFragmentBlend(TheApp::GetInstance()->getCoreProgram(), 0.4f);

	mMaterialMap["ice"].bindTexture();

	geoGen.mGeometry[GeometryGenerator::CUBE]->bindVAO();

	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::CUBE);

	mMaterialMap["stoneBrick"].bindTexture();
	TheShaderManager::Instance()->SetFragmentBlend(TheApp::GetInstance()->getCoreProgram(), 1.0f);

	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(0.0f, -0.65f*1.2, 0.0f), glm::vec3(1.2f, 0.3f, 1.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::CUBE);

	mMaterialMap["fence"].bindTexture();
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->bindVAO();

	Util::Transform(TheApp::GetInstance()->getCoreProgram(), glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PYRAMID);

	
}

void Scene::Setup()
{
	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(2, 0, 0), glm::vec3(1, 1, 0), 1.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	m_vPointLights.back()->updateBuffers(TheApp::GetInstance()->getCoreProgram());

	// Point Light
	m_vPointLights.push_back(new PointLight(glm::vec3(2, 0, 0), glm::vec3(1, 1, 0), 1.5f));
	m_vPointLights.back()->index = m_vPointLights.size() - 1;
	m_vPointLights.back()->updateBuffers(TheApp::GetInstance()->getCoreProgram());

	geoGen.createMesh(GeometryGenerator::CUBE);
	geoGen.mGeometry[GeometryGenerator::CUBE]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::PYRAMID);
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::SPHEAR);
	geoGen.mGeometry[GeometryGenerator::SPHEAR]->generateBuffers();


	geoGen.createMesh(GeometryGenerator::PLANE);
	geoGen.mGeometry[GeometryGenerator::PLANE]->generateBuffers();

	Camera::UpdateCameraFacing(TheApp::GetInstance()->getWindow());


	glfwSetMouseButtonCallback(TheApp::GetInstance()->getWindow(), mouse_btn_down_callback);
	glfwSetWindowSizeCallback(TheApp::GetInstance()->getWindow(), window_resize_callback);



	mMaterialMap["ice"].load("ice.png");
	mMaterialMap["brick"].load("Brick5.png");
	mMaterialMap["theSims"].load("TheSims.jfif");
	mMaterialMap["fence"].load("Fence.png");
	mMaterialMap["grass"].load("tile.png");
	mMaterialMap["stoneBrick"].load("StoneBrick.jpg");


	
}

void Scene::Clean()
{
	for (auto iter : m_vPointLights)
	{
		iter->clean(TheApp::GetInstance()->getCoreProgram());
		delete iter;
		iter = nullptr;
	}
	m_vPointLights.shrink_to_fit();
}
