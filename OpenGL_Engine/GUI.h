#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "MainHeaders.h"
#include "PointLight.h"
#include "Util.h"
#include <vector>
class GUI
{
public:
	GUI();
	~GUI();
	GLuint core_program;
	GLFWwindow* window;


	float lflickerRange = 0.7f;
	float lFactor = 3.0f;
	int fps = 60;
	bool wireFrameEnabled = false;
	bool updateLight = true;
	bool allowCameraMovement = true;

	int display_w, display_h;
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);//ImVec4(135.0f/255.f, 206.0f/255.f, 235.0f/255.f, 1);


	void Init(GLFWwindow* window);
	
	void Render(std::vector <PointLight*> pLights);

	void ClearColour();
	void Clean();
private:
	
};
/*
Future Project:
	Add a Graphics User Interface command list with ImGui
*/

