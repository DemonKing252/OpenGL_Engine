#include "Application.h"
Application* Application::p_sInstance = nullptr;


void Application::Update()
{
	while (glfwGetTime() < lasttime + 1.0 / mUserInterface->fps) {
		// Put the thread to sleep : )
		// -> 1000.0f / 60.0f => 16.66667 milliseconds perframe
		// Reminder that OpenGL only works on one thread.

	}
	lasttime += 1.0 / mUserInterface->fps;

	mUserInterface->ClearColour();
	// Light will increase and decrease intensity (look at this equation in desmos for the pattern)
	
	// light.strength = flickerRange * cos(strength * 3.14159f / 180.0f) + factor
	
	// Cosf supposedly accepts an angle in degrees but it was giving me rounding issues so I reverted back here.
	// Same thing happened when I used it for the sphear (cartesian coordinates)
	mPlayerScene->Update();
	mGuestScene->Update();
	
	if (mUserInterface->mLightShouldUpdate)
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
			GL_STENCIL_BUFFER_BIT);			// Clear stencil buffers (ie: mirroring and shadowing (not used yet))

	

	// Camera can see 45 degrees left/right, with a minimum vocal range of (0.1 - 300)
	// Any object within the range of 0.1-300 of the projection view can be seen on the viewport
	Util::m_4x4ProjMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);

}
void Application::PollEvents()const
{
	glfwPollEvents();
}

void Application::Draw()
{

	// Player #1
	Util::m_4x4ViewMatrix = glm::lookAt(
		glm::vec3(0, 1, 6),		// Camera position in world space
		glm::vec3(0, 0, 0),			// Camera is looking at (0, 0, 0) 
		glm::vec3(0, 1, 0)			// Head is up (0, -1, 0) to look upside down
	);
	glViewport(0, 0, 1024, 384);
	mPlayerScene->Render();
	mUserInterface->Render(mPlayerScene->m_vPointLights);


	// Player #2
	Util::m_4x4ViewMatrix = glm::lookAt(
		Camera::getPosition(),		// Camera position in world space
		glm::vec3(0, 0, 0),			// Camera is looking at (0, 0, 0) 
		glm::vec3(0, 1, 0)			// Head is up (0, -1, 0) to look upside down
	);
	glViewport(0, 384, 1024, 384);
	mGuestScene->Render();

	mUserInterface->Render(mGuestScene->m_vPointLights);
}

void Application::SwapBuffers() const
{
	glfwSwapBuffers(window);
}

void Application::Clean() const
{
	mUserInterface->Clean();

	mPlayerScene->Clean();
	mGuestScene->Clean();
	
	glfwTerminate();

	glDeleteProgram(core_program);
}

GLFWwindow * Application::getWindow() const
{
	return window;
}

GLuint Application::getCoreProgram() const
{
	return core_program;
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

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		return false;

	mPlayerScene = new Scene();
	mGuestScene = new Scene();
	mUserInterface = new GUI();

	// Read the instructions from each shader and link them to the core program
	vert_shader = TheShaderManager::Instance()->CompileShader(GL_VERTEX_SHADER, vertShader);
	frag_shader = TheShaderManager::Instance()->CompileShader(GL_FRAGMENT_SHADER, fragShader);

	core_program = TheShaderManager::Instance()->AttachShader(vert_shader, frag_shader);

	// Delete unused memory
	// If I was using Java I wouldn't have to worry about this! (Memory Management...)
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	// Pipeline is setup
	glUseProgram(core_program);

	mPlayerScene->Setup();
	mGuestScene->Setup();

	mUserInterface->core_program = this->core_program;
	mUserInterface->Init(window);

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	TheShaderManager::Instance()->SetFragmentLightAndTextureOnly(core_program);

}
