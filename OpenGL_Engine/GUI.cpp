#include "GUI.h"

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::Init(GLFWwindow* window)
{
	const char* glsl_version = "#version 130";
	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	this->window = window;

}

void GUI::Render(std::vector <PointLight*> pLights)
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	float lightPos1[3] = { pLights[0]->getPosition().x, pLights[0]->getPosition().y, pLights[0]->getPosition().z };
	float lightPos2[3] = { pLights[1]->getPosition().x, pLights[1]->getPosition().y, pLights[1]->getPosition().z };

	float lightColour1[3] = { pLights[0]->getColour().x, pLights[0]->getColour().y, pLights[0]->getColour().z };
	float lightColour2[3] = { pLights[1]->getColour().x, pLights[1]->getColour().y, pLights[1]->getColour().z };

	float lStrength1 = pLights[0]->getStrength();
	float lStrength2 = pLights[1]->getStrength();

	ImGui::Begin("3D Graphics Engine");                          // Create a window called "Hello, world!" and append into it.

	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), 0);
	ImGui::ColorEdit3("Background Colour", (float*)&clear_color); // Edit 3 floats representing a color

	ImGui::PushItemWidth(150.0f);
	ImGui::SliderInt("Max FPS", &fps, 1.0f, 60.0f);
	ImGui::PopItemWidth();
	ImGui::Separator();

	char format[30];
	sprintf_s(format, "Set camera %s", (allowCameraMovement ? "static" : "dynamic"));

	if (ImGui::Button(format))
	{
		allowCameraMovement = (allowCameraMovement ? false : true);
	}
	ImGui::Checkbox("Lights should altername", &updateLight);

	ImGui::SliderFloat3("Light #1 colour", lightColour1, 0.0f, 1.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	ImGui::SliderFloat3("Light #2 colour", lightColour2, 0.0f, 1.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	ImGui::NewLine();

	ImGui::PushItemWidth(165.0f);
	ImGui::SliderFloat("Light #1 strength", &lStrength1, 0, 20.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat("Light #2 strength", &lStrength2, 0, 20.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	ImGui::Separator();

	ImGui::SliderFloat("Light factor", &lFactor, 0, 20.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	ImGui::SliderFloat("Light factor range", &lflickerRange, 0.0f, 5.0f, "%.1f");
	ImGui::PopItemWidth();

	ImGui::NewLine();
	int display_w, display_h;

	glfwGetFramebufferSize(window, &display_w, &display_h);
	ImGui::Separator();

	ImGui::Text("OpenGL v4.3 Window (%dx%d)", display_w, display_h);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("By: Liam Blake (C) 2020 All Rights Reserved.");
	ImGui::End();

	for (int i = 0; i < 2; i++)
	{
		pLights[i]->setColour(glm::vec3((i == 0 ? lightColour1[0] : lightColour2[0]), (i == 0 ? lightColour1[1] : lightColour2[1]), (i == 0 ? lightColour1[2] : lightColour2[2])));
		pLights[i]->setStrength(i == 0 ? lStrength1 : lStrength2);
		pLights[i]->updateBuffers(core_program);
	}

	ImGui::Begin("Light information");
	ImGui::SetWindowPos(ImVec2(display_w - ImGui::GetWindowWidth(), 0.0f));
	for (int i = 0; i < pLights.size(); i++)
	{
		ImGui::PushStyleColor(0, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
		ImGui::Text("Light #%d", i + 1);
		ImGui::PopStyleColor();

		ImGui::Separator();
		ImGui::Text("position [%.1f, %.1f, %.1f]", pLights[i]->getPosition().x, pLights[i]->getPosition().y, pLights[i]->getPosition().z);               // Display some text (you can use a format strings too)
		ImGui::Text("colour   [%.1f, %.1f, %.1f]", pLights[i]->getColour().x, pLights[i]->getColour().y, pLights[i]->getColour().z);               // Display some text (you can use a format strings too)
		ImGui::Text("strength [%.1f]", pLights[i]->getStrength());               // Display some text (you can use a format strings too)

	}
	ImGui::End();


	// Rendering
	ImGui::Render();

	glViewport(0, 0, display_w, display_h);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}
void GUI::ClearColour()
{
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
}

void GUI::Clean()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
