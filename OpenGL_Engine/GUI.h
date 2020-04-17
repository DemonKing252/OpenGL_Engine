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

	// Allow shader access from this instance
	GLuint core_program;
	GLFWwindow* window;

	// Enviroment variables
	float fogFallOffStart = 0.1f;
	float fogFallOffEnd = 30.0f;

	// Lighting & Shading variables 	
	glm::vec3 ambientStrength = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec4 fogColour = glm::vec4(0.6, 0.6f, 0.6f, 1.0f);

	ImVec4 clear_color = ImVec4(154.0f / 255, 154.0f / 255, 154.0f / 255, 1.0f);//ImVec4(135.0f/255.f, 206.0f/255.f, 235.0f/255.f, 1);

	bool wireFrameEnabled = false;
	bool m_bLightShouldUpdate = true;
	float lflickerRange = 0.7f;
	float lFactor = 3.0f;

	// Frame resource variables
	bool allowCameraMovement = true;	// Allow strafing and walking back and fourth (W/A/S/D)

	int display_w, display_h;
	int fps = 60;

	// Methods
	void setup(GLFWwindow* window);
	void draw(std::vector <Light*> pLights);
	void clearColor();
	void clean();
private:
	
};