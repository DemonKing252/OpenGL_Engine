#include "Application.h"
#define SIZE_WIDTH 1280
#define SIZE_HEIGHT 768
using namespace std;
//***************************************************************************
// OpenGL_Engine::Application::3dApp.cpp by Liam Blake (C) 2020 All Rights Reserved.
// Created:  2020-02-10	
// Modified: 2020-11-22
//
// Description:
// A 3D graphics engine I developed with the knowlege I learned in semester 3.
// This project uses glfw with the glew extension library which means the game
// does not run on windows-64 bit call back functions but rather just a regular
// game loop. SOIL2 is also linked with this project which means you will see 
// texturing too! Press the left mouse button and drag the camera around to 
// see the diffuse and specular lighting effects calculated with each vertex
// normal facing of the 2 shapes I have placed. Additionally theres fog in this
// template too, which you can modify in the user interface I have.
// You can find out how these are calculated in the fragment shader -> "shader.frag"

// ------------------------------------- Alpha Release -------------------------------------
// New Features:
// 1. Added a sphere mesh
// 2. Added phong lighting (Ambient, Diffuse and Specular).
// 3. Geometry Generator: More efficient way of generating shapes.
// 4. Sub-dividing plane made out of grass.

// ------------------------------------- Beta Release -------------------------------------
// New Features:
// 1. Added ImGui
// 2. Added ambient fog that can be modified through the ImGui interface. 
// 3. Added transparent water and animation for it
// 4. Added a skull mesh that reads vertex data from a text file
// 5. Render item class allowing for different blending modes, and fragment styles (choice of: color, lighting, texturing)
// 6. Added a perlin noise algorithm to make the terrain generation random 
// 7. Phong lighting improvements: fragment color changes with the model matrix
// (randomly generated hills and valleys).

// ------------------------------------- Final Release -------------------------------------
// New Features:
// 1. Ambient strength can be modified through ImGui
// 2. Improved water animation
// 3. Active waves
// 4. Buoyancy physics that take account for the waves they are resting on
// 5. Added a car mesh
// 6. Added a skybox

//*****************************************************************************
// GL Returns an error as an unsigned integer.If there is an error, set a break point and check the hexadecimal value
// of the error, then use Ctrl+F to search for the error in glew.h.
int main(int argc, char* argv[])
{
	// Check for link errors in glfw or glew.
	_STL_VERIFY(TheApp::Instance()->init("OpenGL Physics Engine", "VertexCore.hlsl", "FragmentCore.hlsl", SIZE_WIDTH, SIZE_HEIGHT) != GLFW_FALSE,
	("Engine could not initialize due to: " + to_string(glGetError())).c_str());

	float deltaTime = 0.0f;
	float nextFrame = 0.0f;
	float previousTime = 0.0f;
	float gameTimer = 0.0f;
	while (!glfwWindowShouldClose(TheApp::Instance()->getWindow()))
	{
		previousTime = nextFrame;

		// Polling events will be respect to maximum refresh rate of the monitor
		TheApp::Instance()->pollEvents();
		
		// Updating, Drawing and swapping buffers will be under control of the FPS that the user sets
		if (TheApp::Instance()->tick())
		{
			TheApp::Instance()->update(deltaTime);
			TheApp::Instance()->draw();

			TheApp::Instance()->swapBuffers();
		}
		// Calculate the amount of time passed from the previous frame, and add that to the game timer.
		nextFrame = clock();
		deltaTime = (nextFrame - previousTime) / static_cast<float>(CLOCKS_PER_SEC);
		gameTimer += deltaTime;

	}
	TheApp::Instance()->clean();

	return 0;
}