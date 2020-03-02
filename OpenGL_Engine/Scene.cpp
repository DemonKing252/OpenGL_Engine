#include "Scene.h"
#include "Application.h"
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS)
	{
		cout << "Mouse down called back" << endl;

		glfwGetCursorPos(window, &Camera::mouseX, &Camera::mouseY);
	}
}
void window_resize_callback(GLFWwindow* window, int x, int y)
{
	cout << "Window resized" << endl;
}
Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
	for (PointLight* light : pLights) {
		if (Application::Instance()->mUserInterface->updateLight) {
			Application::Instance()->strength += 1.5f;

			light->setStrength((Application::Instance()->mUserInterface->lflickerRange * cos(Application::Instance()->strength * Util::DegToRad())) + Application::Instance()->mUserInterface->lFactor);
		}
		light->setPosition(glm::vec3(3 * cos((Application::Instance()->angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad()), light->getPosition().y, 3 * sin((Application::Instance()->angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad())));
	}
}

void Scene::Render()
{
	// Bind a texture ID (an unsigned integer that points to a texture buffer)
	mMaterialMap["theSims"].bindTexture();

	// Important Order: Scale-Rotate-Translate
	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(0.0f, 0.5f - 0.12f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

	geoGen.mGeometry[GeometryGenerator::SPHEAR]->bindVAO();
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(-0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(-0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(+0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(+0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	mMaterialMap["grass"].bindTexture();
	TheShaderManager::Instance()->SetFragmentAllTypes(Application::Instance()->getCoreProgram());

	geoGen.mGeometry[GeometryGenerator::PLANE]->bindVAO();
	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PLANE);

	mMaterialMap["stoneBrick"].bindTexture();
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(Application::Instance()->getCoreProgram());
	geoGen.mGeometry[GeometryGenerator::SPHEAR]->bindVAO();
	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	// Set a texture ID to be the active one in memory
	mMaterialMap["theSims"].bindTexture();

	// Tell the fragment shader to only map out vertex colours
	TheShaderManager::Instance()->SetFragmentColourOnly(Application::Instance()->getCoreProgram());
	for (PointLight* light : pLights)
	{
		Util::Transform(Application::Instance()->getCoreProgram(), light->getPosition(), glm::vec3(0.5), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		geoGen.draw(GeometryGenerator::SPHEAR);
	}
	// Tell the fragment shader to only map out lighting and vertex textures
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(Application::Instance()->getCoreProgram());

	mMaterialMap["brick"].bindTexture();

	// Set a vertex vao to be the active one in memory
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->bindVAO();
	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PYRAMID);

	TheShaderManager::Instance()->SetFragmentBlend(Application::Instance()->getCoreProgram(), 0.4f);

	mMaterialMap["ice"].bindTexture();

	geoGen.mGeometry[GeometryGenerator::CUBE]->bindVAO();

	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::CUBE);

	mMaterialMap["stoneBrick"].bindTexture();
	TheShaderManager::Instance()->SetFragmentBlend(Application::Instance()->getCoreProgram(), 1.0f);

	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(0.0f, -0.65f*1.2, 0.0f), glm::vec3(1.2f, 0.3f, 1.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::CUBE);

	mMaterialMap["fence"].bindTexture();
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->bindVAO();

	Util::Transform(Application::Instance()->getCoreProgram(), glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PYRAMID);

	
}

void Scene::Init()
{
	// Point Light
	pLights.push_back(new PointLight(glm::vec3(2, 0, 0), glm::vec3(1, 1, 0), 1.5f));
	pLights.back()->index = pLights.size() - 1;
	pLights.back()->updateBuffers(Application::Instance()->getCoreProgram());

	// Point Light
	pLights.push_back(new PointLight(glm::vec3(2, 0, 0), glm::vec3(1, 1, 0), 1.5f));
	pLights.back()->index = pLights.size() - 1;
	pLights.back()->updateBuffers(Application::Instance()->getCoreProgram());

	geoGen.createMesh(GeometryGenerator::CUBE);
	geoGen.mGeometry[GeometryGenerator::CUBE]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::PYRAMID);
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::SPHEAR);
	geoGen.mGeometry[GeometryGenerator::SPHEAR]->generateBuffers();


	geoGen.createMesh(GeometryGenerator::PLANE);
	geoGen.mGeometry[GeometryGenerator::PLANE]->generateBuffers();

	Camera::UpdateCameraFacing(Application::Instance()->getWindow());
	Camera::UpdateCameraPosition();


	glfwSetMouseButtonCallback(Application::Instance()->getWindow(), mouse_button_callback);
	glfwSetWindowSizeCallback(Application::Instance()->getWindow(), window_resize_callback);



	mMaterialMap["ice"].load("ice.png");
	mMaterialMap["brick"].load("Brick5.png");
	mMaterialMap["theSims"].load("TheSims.jfif");
	mMaterialMap["fence"].load("Fence.png");
	mMaterialMap["grass"].load("tile.png");
	mMaterialMap["stoneBrick"].load("StoneBrick.jpg");


	
}
