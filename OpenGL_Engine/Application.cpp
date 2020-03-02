#include "Application.h"
Application* Application::p_sInstance = nullptr;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS)
	{
		cout << "Mouse down called back" << endl;
	
		glfwGetCursorPos(window, &Camera::mouseX, &Camera::mouseY);
	}
}
void Application::Update()
{
	while (glfwGetTime() < lasttime + 1.0 / mUserInterface->fps) {
		// Put the thread to sleep.
		// -> 1000.0f / 60.0f => 16.666 milliseconds perframe
		// Reminder that OpenGL only works on one thread.

	}
	lasttime += 1.0 / mUserInterface->fps;

	glClearColor(mUserInterface->clear_color.x, 
				 mUserInterface->clear_color.y, 
				 mUserInterface->clear_color.z, 
				 mUserInterface->clear_color.w);
	// Light will increase and decrease intensity (look at this equation in desmos for the pattern)
	
	// light.strength = flickerRange * cos(strength * 3.14159f / 180.0f) + factor
	
	// Cosf supposedly accepts an angle in degrees but it was giving me rounding issues so I reverted back here.
	// Same thing happened when I used it for the sphear (cartesian coordinates)
	
	for (PointLight* light : pLights) {
		if (mUserInterface->updateLight) {
			strength += 1.5f;
			
			light->setStrength((mUserInterface->lflickerRange * cos(strength * Util::DegToRad())) + mUserInterface->lFactor);
		}
		light->setPosition(glm::vec3(3 * cos((angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad()), light->getPosition().y, 3 * sin((angleDelta + (light->index == 0 ? 0 : 180.0f)) * Util::DegToRad())));
	}
	if (mUserInterface->updateLight)
		angleDelta += 3.0f;

	if (Camera::EventMouseClick(window) && mUserInterface->allowCameraMovement) {
		Camera::UpdateCameraPosition();
		Camera::UpdateCameraFacing(window);

		// Update the camera facing vector 
		TheShaderManager::Instance()->SetUniform3f(core_program, "mCameraFacing", Camera::getPosition());
	}

	// Clear buffers (ie: Color, Depth, and Stencil) to prepare to swap the back and front buffers
	// The concept of swapping buffers is important because the front buffer is being shown to the screen
	// while the back buffer is still being drawn to

	glClear(GL_COLOR_BUFFER_BIT |			// Clear colour buffers
			GL_DEPTH_BUFFER_BIT |			// Clear depth buffers (ie: Only whats in front is shown to the camera)
			GL_STENCIL_BUFFER_BIT);			// Clear stencil buffers (ie: mirroring and shadowing (not used yet)

	Util::viewMatrix = glm::lookAt(
		Camera::getPosition(),		// Camera position in world space
		glm::vec3(0, 0, 0),			// Camera is looking at (0, 0, 0) 
		glm::vec3(0, 1, 0)			// Head is up (0, -1, 0) to look upside down
	);

	// Camera can see 45 degrees left/right, with a minimum vocal range of (0.1 - 300)
	// Any object within the range of 0.1-300 of the projection view can be seen on the viewport
	Util::projMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);

}
void Application::PollEvents()const
{
	glfwPollEvents();
}

void Application::Draw()
{
	
	// Bind a texture ID (an unsigned integer that points to a texture buffer)
	mMaterialMap["theSims"].bindTexture();

	// Important Order: Scale-Rotate-Translate
	Util::Transform(core_program, glm::vec3(0.0f, 0.5f - 0.12f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

	geoGen.mGeometry[GeometryGenerator::SPHEAR]->bindVAO();
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(core_program, glm::vec3(-0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(core_program, glm::vec3(-0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(core_program, glm::vec3(+0.5f, -0.5f - 0.03f, +0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	Util::Transform(core_program, glm::vec3(+0.5f, -0.5f - 0.03f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	mMaterialMap["grass"].bindTexture();
	TheShaderManager::Instance()->SetFragmentAllTypes(core_program);

	geoGen.mGeometry[GeometryGenerator::PLANE]->bindVAO();
	Util::Transform(core_program, glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PLANE);

	mMaterialMap["stoneBrick"].bindTexture();
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(core_program);
	geoGen.mGeometry[GeometryGenerator::SPHEAR]->bindVAO();
	Util::Transform(core_program, glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::SPHEAR);

	// Set a texture ID to be the active one in memory
	mMaterialMap["theSims"].bindTexture(); 

	// Tell the fragment shader to only map out vertex colours
	TheShaderManager::Instance()->SetFragmentColourOnly(core_program);
	for (PointLight* light : pLights)
	{
		Util::Transform(core_program, light->getPosition(), glm::vec3(0.5), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		geoGen.draw(GeometryGenerator::SPHEAR);
	}
	// Tell the fragment shader to only map out lighting and vertex textures
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(core_program);

	mMaterialMap["brick"].bindTexture();

	// Set a vertex vao to be the active one in memory
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->bindVAO();
	Util::Transform(core_program, glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PYRAMID);

	TheShaderManager::Instance()->SetFragmentBlend(core_program, 0.4f);

	mMaterialMap["ice"].bindTexture();

	geoGen.mGeometry[GeometryGenerator::CUBE]->bindVAO();
	
	Util::Transform(core_program, glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::CUBE);

	mMaterialMap["stoneBrick"].bindTexture();
	TheShaderManager::Instance()->SetFragmentBlend(core_program, 1.0f);
	
	Util::Transform(core_program, glm::vec3(0.0f, -0.65f*1.2, 0.0f), glm::vec3(1.2f, 0.3f, 1.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::CUBE);

	mMaterialMap["fence"].bindTexture();
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->bindVAO();
	
	Util::Transform(core_program, glm::vec3(0.0f, -0.12f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
	geoGen.draw(GeometryGenerator::PYRAMID);

	mUserInterface->Render(pLights);
}

void Application::SwapBuffers() const
{
	glfwSwapBuffers(window);
}

void Application::Clean() const
{
	mUserInterface->Clean();
	glfwTerminate();

	glDeleteProgram(core_program);
}

GLFWwindow * Application::getWindow() const
{
	return window;
}

Application * Application::Instance()
{
	if (p_sInstance == nullptr)
	{
		p_sInstance = new Application();
		return p_sInstance;
	}
	return p_sInstance;
}

bool Application::Init(const char * titleName, const char * vertShader, const char * fragShader, const GLint width, const GLint height)
{
	srand((unsigned)time(NULL));
	///* Initialize the library */
	/* Initialize the library */
	//ImGui::SameLine();

	if (glfwInit() == 0)
		return false;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, titleName, NULL, NULL);

	if (!window)
		return false;

	mUserInterface = new GUI();

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	// Read the instructions from each shader and link them to the core program
	vert_shader = TheShaderManager::Instance()->CompileShader(GL_VERTEX_SHADER, vertShader);
	frag_shader = TheShaderManager::Instance()->CompileShader(GL_FRAGMENT_SHADER, fragShader);

	core_program = TheShaderManager::Instance()->AttachShader(vert_shader, frag_shader);

	// Delete unused memory
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	// Our pipeline is setup
	glUseProgram(core_program);

	// Point Light
	pLights.push_back(new PointLight(glm::vec3(2, 0, 0), glm::vec3(1, 1, 0), 1.5f));
	pLights.back()->index = pLights.size() - 1;
	pLights.back()->updateBuffers(core_program);

	// Point Light
	pLights.push_back(new PointLight(glm::vec3(2, 0, 0), glm::vec3(1, 1, 0), 1.5f));
	pLights.back()->index = pLights.size() - 1;
	pLights.back()->updateBuffers(core_program);

	geoGen.createMesh(GeometryGenerator::CUBE);
	geoGen.mGeometry[GeometryGenerator::CUBE]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::PYRAMID);
	geoGen.mGeometry[GeometryGenerator::PYRAMID]->generateBuffers();

	geoGen.createMesh(GeometryGenerator::SPHEAR);
	geoGen.mGeometry[GeometryGenerator::SPHEAR]->generateBuffers();


	geoGen.createMesh(GeometryGenerator::PLANE);
	geoGen.mGeometry[GeometryGenerator::PLANE]->generateBuffers();

	Camera::UpdateCameraFacing(window);
	Camera::UpdateCameraPosition();


	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mMaterialMap["ice"].load("ice.png");
	mMaterialMap["brick"].load("Brick5.png");
	mMaterialMap["theSims"].load("TheSims.jfif");
	mMaterialMap["fence"].load("Fence.png");
	mMaterialMap["grass"].load("tile.png");
	mMaterialMap["stoneBrick"].load("StoneBrick.jpg");


	mUserInterface->core_program = this->core_program;
	mUserInterface->Init(window);

		
	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(core_program);

}
