#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "MainHeaders.h"
#include "PointLight.h"
#include "Util.h"
#include "ShaderManager.h"
#include <vector>
class GUI
{
public:
	GUI();
	~GUI();
	GLuint core_program;
	GLFWwindow* window;


	float fogFallOffStart = 0.1f;
	float fogFallOffEnd = 80.0f;

	glm::vec3 ambientStrength = glm::vec3(0.7f, 0.2f, 0.7f);
	glm::vec4 fogColour = glm::vec4(0.0, 0.0f, 1.0f, 1.0f);

	float lflickerRange = 0.7f;
	float lFactor = 3.0f;
	int fps = 60;
	bool wireFrameEnabled = false;
	bool m_bLightShouldUpdate = true;
	bool allowCameraMovement = true;

	int display_w, display_h;
	ImVec4 clear_color = ImVec4(102.0f/255, 102.0f/255, 183.0f/255, 1.0f);//ImVec4(135.0f/255.f, 206.0f/255.f, 235.0f/255.f, 1);


	void setup(GLFWwindow* window);
	
	void draw(std::vector <Light*> pLights);

	void clearColor();
	void clean();
private:
	
};
/*
Future Project:
	Add a Graphics User Interface command list with ImGui
*/

