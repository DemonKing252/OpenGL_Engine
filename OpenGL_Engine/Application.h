#pragma once
#include "MainHeaders.h"
#include "PointLight.h"
#include "GUI.h"
#include "Material.h"
#include "GeometryGenerator.h"
#include "Camera.h"
#include "Util.h"
#include <unordered_map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Scene.h"
typedef class Application
{
public:
	GLfloat angleDelta = 0.0f;
	GLfloat strength = 0.0f;
	double lasttime = 0.0f;

	// Multiplayer System
	Scene* mPlayerScene;

	GUI* mUserInterface;

	static Application* Instance();

	bool Init(const char* titleName, const char* vertShader, const char* fragShader, const GLint width, const GLint height);

	void Update();
	void PollEvents() const;
	void Draw();
	void SwapBuffers() const;

	void Clean() const;

	GLFWwindow* getWindow() const;
	GLuint getCoreProgram() const;
	
	GLint frameBufferW, frameBufferH;

private:
	GLFWwindow* window;
	GLuint core_program;

	GLuint vert_shader;
	GLuint frag_shader;

	static Application* p_sInstance;
} Application, TheApp;
