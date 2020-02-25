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

class Application
{
public:
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);//ImVec4(135.0f/255.f, 206.0f/255.f, 235.0f/255.f, 1);
	GLfloat angleDelta = 0.0f;
	GLfloat strength = 0.0f;
	double lasttime = 0.0f;

	std::vector <PointLight*> pLights;
	std::unordered_map <string, Material> mMaterialMap;
	GeometryGenerator geoGen;

	GLFWwindow* window;
	GUI* mUserInterface;

	static Application* Instance();

	bool Init(const char* titleName, const char* vertShader, const char* fragShader, const GLint width, const GLint height);

	void Update();
	void PollEvents() const;
	void Draw();
	void SwapBuffers() const;

	void Clean() const;

	GLFWwindow* getWindow() const;
private:

	GLuint core_program;

	GLuint vert_shader;
	GLuint frag_shader;

	static Application* p_sInstance;
};
