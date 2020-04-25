#include "Application.h"
Application* Application::p_sInstance = nullptr;
bool Application::init(const char * titleName, const char * vertShader, const char * fragShader, const GLint width, const GLint height)
{
	// Good seeds:
	// 8 and 9, 21, 26, 27, 36, 40, 41
	// Seed 5 for the noise algorithm for terrain generation.
	// Using 5 octaves

	srand(40);
	///* Initialize the library */
	// Initialize the library 

	if (glfwInit() == GLFW_FALSE) { return false; }

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, titleName, NULL, NULL);
	if (!window) return false; 

	// Make the window's context current 
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) return false;
	
	// Mouse events
	glfwSetMouseButtonCallback(window, CallBack::mouse_btn_callback);
	// Window buffer resize/minimize/maximize events
	glfwSetWindowSizeCallback(window, CallBack::window_resize_callback);
	// Keyboard events
	glfwSetKeyCallback(window, CallBack::key_callback);

	// Example of compiling a shader from a string, be sure to include a '\n' after each line!
	/*
	string vertexcore = 
	"#version 430 core													\n"
	"layout(location = 0) in vec3 vertex_position;						\n"
	"layout(location = 1) in vec3 vertex_color;							\n"
	"layout(location = 2) in vec2 vertex_texture;						\n"
	"layout(location = 3) in vec3 vertex_normal;						\n"
	"																	\n"
	"out vec3 vs_unadjustedfragPos;										\n"
	"out vec3 vs_normal;												\n"
	"out vec3 vs_color;													\n"
	"out vec2 vs_texture;												\n"
	"out vec3 vs_fragPos;												\n"
	"																	\n"
	"uniform mat4 M;													\n"
	"uniform mat4 V;													\n"
	"uniform mat4 P;													\n"
	"																	\n"
	"void main()														\n"
	"{																	\n"
	"	vs_unadjustedfragPos = vertex_position;							\n"
	"	vs_normal = mat3(M) * vertex_normal;							\n"
	"	vs_texture = vertex_texture;									\n"
	"	vs_color = vertex_color;										\n"
	"	vs_fragPos = (M * vec4(vertex_position, 1.0f)).xyz;				\n"
	"																	\n"
	"	// Convert 3D world space coordinates to 2D screen coordinates	\n"
	"	gl_Position = P * V * M * vec4(vertex_position, 1.0f);			\n"
	"}																	\n";
	m_shaderInfo["vertex_core"] = TheShaderManager::Instance()->compileShaderFromString(GL_VERTEX_SHADER, vertexcore);
	*/

	/*************************************************************************/


	// Read the instructions from each shader and link them to the core program.
	m_shaderInfo["vertex_core"] = TheShaderManager::Instance()->compileShaderFromString(GL_VERTEX_SHADER, vertShader);
	m_shaderInfo["fragment_core"] = TheShaderManager::Instance()->compileShaderFromFile(GL_FRAGMENT_SHADER, fragShader);

	core_program = TheShaderManager::Instance()->attachShaders
	(
		m_shaderInfo["vertex_core"], 
		m_shaderInfo["fragment_core"]
	);
	
	// Delete unused memory
	for (auto iter : m_shaderInfo)
	{
		glDeleteShader(m_shaderInfo[iter.first]);
	}
	// The core program is holding the info of the vertex and fragment cores, no longer need these:
	m_shaderInfo.clear();

	// Graphics pipeline is setup
	// From here on out we can get access to uniform variables with this variable:
	glUseProgram(core_program);

	// Initialize the player scene 
	m_playerScene = new Scene();
	m_playerScene->setup();

	// Initialize Dear ImGui
	m_userInterface = new GUI();
	m_userInterface->core_program = this->core_program;
	m_userInterface->setup(window);

	// GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Camera::frameBufferW = width;
	Camera::frameBufferH = height;

	Util::m_4x4ProjMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);
	TheShaderManager::Instance()->SetUniformMatrix4x4(core_program, "P", Util::m_4x4ProjMatrix);

	// Initialize the water uv position for animating
	TheShaderManager::Instance()->SetUVMapping(core_program, glm::vec2(0.0f, 0.0f), false);

	Camera::UpdateCameraFacing(window);
	Camera::CheckEvents(window);

	// Load all materials
	m_materialMap["ice"].load("Assets/Images/ice.png");
	m_materialMap["brick"].load("Assets/Images/Brick5.png");
	m_materialMap["theSims"].load("Assets/Images/TheSims.jfif");
	m_materialMap["fence"].load("Assets/Images/Fence.png");
	m_materialMap["grass"].load("Assets/Images/grass2.png");
	m_materialMap["stoneBrick"].load("Assets/Images/StoneBrick.jpg");
	m_materialMap["water"].load("Assets/Images/water.png");
}

void Application::pollEvents()const
{
	glfwPollEvents();
}
bool Application::tick()
{
	if (glfwGetTime() < lasttime + 1.0 / m_userInterface->fps)
		return false;

	lasttime += 1.0 / m_userInterface->fps;

	return true;
}

void Application::update()
{
	m_userInterface->clearColor();
	m_playerScene->update();
	
	if (m_userInterface->m_bLightShouldUpdate)
		angleDelta += 3.0f;

	if (Camera::EventMouseClick(window) && m_userInterface->allowCameraMovement)
	{
		Camera::UpdateCameraFacing(window);
		Camera::CheckEvents(window);
		// Update the camera facing vector 
	}

	glClear(GL_COLOR_BUFFER_BIT |			// Clear color buffers
			GL_DEPTH_BUFFER_BIT |			// Clear depth buffers (ie: Only whats in front is shown to the camera)
			GL_STENCIL_BUFFER_BIT);			// Clear stencil buffers (ie: mirroring and shadowing (not used yet))

	// Camera can see 45 degrees left/right, with a minimum vocal range of (0.1 - 300)
	// Any object within the range of 0.1-300 of the projection view can be seen on the viewport
}

void Application::draw()
{
	m_playerScene->draw();
	m_userInterface->draw(m_playerScene->m_vPointLights);
}

void Application::swapBuffers() const
{
	// Whats happening here?
	// 1. Clear the current buffer.
	// 2. Swap the front and back buffer.
	// 3. The next frame, everything will be drawn to to this buffer while the other buffer is being shown to the screen.
	// 4. This process repeats

	// In DirectX 11 we would use a swap chain to manage this process 

	glfwSwapBuffers(window);
}

void Application::clean() const
{
	m_userInterface->clean();
	m_playerScene->clean();

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

Application::Application()
{
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