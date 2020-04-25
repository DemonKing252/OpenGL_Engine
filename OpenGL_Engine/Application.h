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
#include "CallBack.h"
typedef class Application
{
public:
	// Ensure that this class instance cannot be copied elsewhere (it is a singleton after all).
	// To do this we can delete the copy constructor
	Application(Application*) = delete;

	GLfloat angleDelta = 0.0f;
	GLfloat strength = 0.0f;
	double lasttime = 0.0f;

	static Application* Instance();

	bool init(const char* titleName, const char* vertShader, const char* fragShader, const GLint width, const GLint height);
	bool tick();

	void update();
	void pollEvents() const;
	void draw();
	void swapBuffers() const;

	void clean() const;

	GLFWwindow* getWindow() const;
	GLuint getCoreProgram() const;
	
	Scene* m_playerScene;
	GUI* m_userInterface;

	std::unordered_map <std::string, Material> m_materialMap;

private:
	Application();

	GLFWwindow* window;
	GLuint core_program;

	std::unordered_map <std::string, GLuint> m_shaderInfo;

	static Application* p_sInstance;
} Application, TheApp;
