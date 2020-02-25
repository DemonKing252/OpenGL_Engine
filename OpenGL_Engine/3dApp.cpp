#include "Application.h"
#define WIDTH 1024
#define HEIGHT 768
using namespace std;
//***************************************************************************
// OpenGL_Engine::Application::3dApp.cpp by Liam Blake (C) 2020 All Rights Reserved.
//
// Created:  2020-02-10	
// Modified: 2020-02-21
//
// Description:
// A 3D graphics engine I developed with the knowlege I learned in semester 3.
// This project uses glfw with the glew extension library which means the game
// does not run on windows-64 bit call back functions but rather just a regular
// game loop. SOIL2 is also linked with this project which means you will see 
// texturing too! Press the left mouse button and drag the camera around to 
// see the diffuse and specular lighting effects calculated with each vertex
// normal facing of the 2 shapes I have placed. You can find out how these are
// calculated in the fragment shader -> "shader.frag"
//*****************************************************************************
int main(int argc, char** argv)
{
	assert(Application::Instance()->Init("3D Graphics Engine", "shader.vert", "shader.frag", WIDTH, HEIGHT));

	while (!glfwWindowShouldClose(Application::Instance()->getWindow()))
	{
		Application::Instance()->PollEvents();

		Application::Instance()->Update();
		Application::Instance()->Draw();

		Application::Instance()->SwapBuffers();
	}
	
	return 0;
}