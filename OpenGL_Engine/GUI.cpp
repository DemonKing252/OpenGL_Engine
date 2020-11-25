#include "GUI.h"

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::setup(GLFWwindow* window)
{
	const char* glsl_version = "#version 130";
	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	
	TheShaderManager::Instance()->SetUniformf(core_program, "fog_fallOffStart", fogFallOffStart);
	TheShaderManager::Instance()->SetUniformf(core_program, "fog_fallOffEnd", fogFallOffEnd);
	TheShaderManager::Instance()->SetUniform4f(core_program, "fog_colour", fogColour);
	TheShaderManager::Instance()->SetUniform3f(core_program, "ambient", ambientStrength);

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	this->window = window;

}

void GUI::draw(std::vector <Light*> l)
{
	fogColour.x = (cos_radians(a)) + 0.5f;
	fogColour.y = (cos_radians(a)) + 0.5f;
	fogColour.z = (cos_radians(a)) + 0.5f;

	if (fogColour.x > 1.0f) fogColour.x = 1.0f;
	else if (fogColour.x < 0.1f) fogColour.x = 0.1f;


	if (fogColour.y > 1.0f) fogColour.y = 1.0f;
	else if (fogColour.y < 0.1f) fogColour.y = 0.1f;


	if (fogColour.z > 1.0f) fogColour.z = 1.0f;
	else if (fogColour.z < 0.1f) fogColour.z = 0.1f;

	ambientStrength = glm::vec3(fogColour.x, fogColour.y, fogColour.z);

	cout << fogColour.x << " " << fogColour.y << " " << fogColour.z << endl;

	a += 60.0f * Util::Pi() / 180.0f;   

	TheShaderManager::Instance()->SetUniform4f(core_program, "fog_colour", glm::vec4(fogColour.x, fogColour.y, fogColour.z, 1.0f));
	TheShaderManager::Instance()->SetUniform3f(core_program, "ambient", ambientStrength);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	float lightPos1[3] = { l[0]->getPosition().x, l[0]->getPosition().y, l[0]->getPosition().z };
	float lightPos2[3] = { l[1]->getPosition().x, l[1]->getPosition().y, l[1]->getPosition().z };

	float lightColour1[3] = { l[0]->getColour().x, l[0]->getColour().y, l[0]->getColour().z };
	float lightColour2[3] = { l[1]->getColour().x, l[1]->getColour().y, l[1]->getColour().z };

	float lStrength1 = l[0]->getStrength();
	float lStrength2 = l[1]->getStrength();

	ImGui::Begin("Enviorment Settings");                          // Create a window called "Hello, world!" and append into it.


	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), 0);
	ImGui::ColorEdit3("Background colour", (float*)&clear_color); // Edit 3 floats representing a color
	float ambient[3] = { ambientStrength.x, ambientStrength.y, ambientStrength.z };
	//if (ImGui::SliderFloat3("Ambient Lighting", ambient, 0.0f, 1.0f, "%.1f"))
	//{
	//	ambientStrength = glm::vec3(ambient[0], ambient[1], ambient[2]);
	//	TheShaderManager::Instance()->SetUniform3f(core_program, "ambient", ambientStrength);
	//}

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
	ImGui::Checkbox("Lights should alternate", &m_bLightShouldUpdate);
	if (ImGui::Checkbox("Wire frame enabled", &wireFrameEnabled))
	{
		if (wireFrameEnabled)
		{
			Util::wireType1 = GL_LINE_LOOP;
			Util::wireType2 = GL_LINE_LOOP;
		}
		else
		{
			Util::wireType1 = GL_QUADS;
			Util::wireType2 = GL_TRIANGLES;
		}
	}
	ImVec4 light = { lightColour1[0], lightColour2[1], lightColour1[2], lightColour1[3] };


	ImGui::SliderFloat3("Light #1 color", lightColour1, 0.0f, 1.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	ImGui::SliderFloat3("Light #2 color", lightColour2, 0.0f, 1.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	ImGui::NewLine();

	ImGui::PushItemWidth(165.0f);
	ImGui::SliderFloat("Light #1 strength", &lStrength1, 0, 100.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat("Light #2 strength", &lStrength2, 0, 100.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	//ImGui::Separator();

	ImGui::SliderFloat("Light factor", &lFactor, 0, 100.0f, "%.1f");            // Edit 1 float using a slider from 0.0f to 1.0f

	ImGui::SliderFloat("Light factor range", &lflickerRange, 0.0f, 5.0f, "%.1f");
	ImGui::PopItemWidth();

	ImGui::Separator();
	ImGui::NewLine();

	float fog[3] = { fogColour.x, fogColour.y, fogColour.z };
	
	ImGui::Text("Sun Light: %.1f%%", fogColour.x * 100.0f);
	//if (ImGui::SliderFloat3("Fog colour", fog, 0.0f, 1.0f, "%.1f"))
	//{
	//	fogColour = glm::vec4(
	//		fog[0],
	//		fog[1],
	//		fog[2],
	//		1.0f
	//	);
	//	TheShaderManager::Instance()->SetUniform4f(core_program, "fog_colour", glm::vec4(fogColour.x, fogColour.y, fogColour.z, 1.0f));
	//}
	
	ImGui::PushItemWidth(165.0f);

	if (ImGui::SliderFloat("Fog fall off start", &fogFallOffStart, 0.0f, 100.0f, "%.1f"))
		TheShaderManager::Instance()->SetUniformf(core_program, "fog_fallOffStart", fogFallOffStart);

	if (ImGui::SliderFloat("Fog fall off end", &fogFallOffEnd, 0.0f, 100.0f, "%.1f"))
		TheShaderManager::Instance()->SetUniformf(core_program, "fog_fallOffEnd", fogFallOffEnd);

	ImGui::PopItemWidth();

	ImGui::NewLine();
	
	glfwGetFramebufferSize(window, &display_w, &display_h);
	ImGui::Separator();

	ImGui::Text("OpenGL v4.3 Window (%dx%d)", display_w, display_h);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("By: Liam Blake (C) 2020 All Rights Reserved.");
	ImGui::End();

	for (int i = 0; i < 2; i++)
	{
		l[i]->setColour(glm::vec3((i == 0 ? lightColour1[0] : lightColour2[0]), (i == 0 ? lightColour1[1] : lightColour2[1]), (i == 0 ? lightColour1[2] : lightColour2[2])));
		l[i]->setStrength(i == 0 ? lStrength1 : lStrength2);
		l[i]->updateBuffers(core_program);
	}

	ImGui::Begin("Light information");
	ImGui::SetWindowPos(ImVec2(display_w - ImGui::GetWindowWidth(), 0.0f));
	for (int i = 0; i < l.size(); i++)
	{
		ImGui::PushStyleColor(0, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
		ImGui::Text("Light #%d", i + 1);
		ImGui::PopStyleColor();

		ImGui::Separator();
		ImGui::Text("position [%.1f, %.1f, %.1f]", l[i]->getPosition().x, l[i]->getPosition().y, l[i]->getPosition().z);               // Display some text (you can use a format strings too)
		ImGui::Text("color    [%.1f, %.1f, %.1f]", l[i]->getColour().x, l[i]->getColour().y, l[i]->getColour().z);               // Display some text (you can use a format strings too)
		ImGui::Text("strength [%.1f]", l[i]->getStrength());               // Display some text (you can use a format strings too)

	}
	ImGui::End();


	// Rendering
	ImGui::Render();


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}
void GUI::clearColor()
{
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
}

void GUI::clean()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

}
