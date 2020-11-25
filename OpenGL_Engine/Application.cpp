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

	if (glfwInit() == GLFW_FALSE) { cerr << "GLFW Init fail!" << endl; return false; }

	cout << "GLFW Init success!" << endl;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, titleName, NULL, NULL);
	if (!window) return false; 

	// Make the window's context current 
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { cerr << "GLEW Init fail!" << endl; return false; }
	
	cout << "GLEW Init success!" << endl;
	
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

	cout << "Compiling shaders..." << endl;
	m_shaderInfo["vertex_core"] = TheShaderManager::Instance()->compileShaderFromFile(GL_VERTEX_SHADER, vertShader);
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

	Util::m_4x4ProjMatrix = glm::perspective(glm::radians(90.f), 4.0f / 3.0f, 0.1f, 50.0f);
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

	Vertex vertices[24] =
	{
		
		Vertex(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 1.f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 1.f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 0.f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 0.f), glm::vec3(-0.5f, -0.5f, +0.5f)),
		

		
		Vertex(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 1.f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 1.f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 0.f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 0.f), glm::vec3(-0.5f, -0.5f, +0.5f)),


		
		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 1.f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 1.f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 0.f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 0.f), glm::vec3(-0.5f, -0.5f, +0.5f)),


		
		Vertex(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 1.f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 1.f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 0.f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 0.f), glm::vec3(-0.5f, -0.5f, +0.5f)),


		
		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 1.f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 1.f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 0.f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 0.f), glm::vec3(-0.5f, -0.5f, +0.5f)),

		Vertex(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 0.f), glm::vec3(-0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 0.f), glm::vec3(0.5f, -0.5f, -0.5f)),
		Vertex(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.f, 1.f), glm::vec3(0.5f, -0.5f, +0.5f)),
		Vertex(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.f, 1.f), glm::vec3(-0.5f, -0.5f, +0.5f)),

	};



	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 24, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)24);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)32);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	// texture 1
	// --------------------------------
	int w[6], h[6];
	unsigned char* image[6] = {
		SOIL_load_image("Assets/IceRiver/negx.bmp", &w[0], &h[0], 0, SOIL_LOAD_RGBA),
		SOIL_load_image("Assets/IceRiver/posx.bmp", &w[1], &h[1], 0, SOIL_LOAD_RGBA),
		SOIL_load_image("Assets/IceRiver/negz.bmp", &w[2], &h[2], 0, SOIL_LOAD_RGBA),
		SOIL_load_image("Assets/IceRiver/posz.bmp", &w[3], &h[3], 0, SOIL_LOAD_RGBA),
		SOIL_load_image("Assets/IceRiver/posy.bmp", &w[4], &h[4], 0, SOIL_LOAD_RGBA),
		SOIL_load_image("Assets/IceRiver/negy.bmp", &w[5], &h[5], 0, SOIL_LOAD_RGBA)
	};
	for (int i = 0; i < 6; i++)
	{
		// generate the texture
		glGenTextures(1, &tex[i]);

		// bind the texture (IMPORTANT):
		glBindTexture(GL_TEXTURE_2D, tex[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w[i], h[i], 0, GL_RGBA, GL_UNSIGNED_BYTE, image[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		//glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image[i]);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
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

void Application::update(float dt)
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
	glDisable(GL_DEPTH_TEST);
	Util::Transform(core_program, Camera::getPosition(), glm::vec3(.5f, .5f, .5f), glm::vec3(0.f, 1.f, 0.f), 0.0f);

	TheShaderManager::Instance()->SetUniformi(core_program, "fragStyle", FragmentStyle::TEXTURE_AND_DIFFALBEDO_ONLY);
	TheShaderManager::Instance()->SetDiffuseAlbedo(core_program, /*glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)*/m_userInterface->fogColour);
	
	// bind the vbo and ibo (vertices and indicies)
	glBindVertexArray(vao);
	
	// ----------------------------------------------------------------------------
	// bind the texture, set is as the active one, now we can draw it:
	
	int first = 0;
	for (int i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		glDrawArrays(GL_QUADS, first, 4);
		first += 4;
	}

	glEnable(GL_DEPTH_TEST);

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