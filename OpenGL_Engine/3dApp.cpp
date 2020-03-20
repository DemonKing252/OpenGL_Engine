#include "Application.h"
#define SIZE_WIDTH 1024
#define SIZE_HEIGHT 768
using namespace std;
//***************************************************************************
// OpenGL_Engine::Application::3dApp.cpp by Liam Blake (C) 2020 All Rights Reserved.
// Created:  2020-02-10	
// Modified: 2020-03-12
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
//*****************************************************************************
// GL Returns an error as an unsigned integer.If there is an error, set a break point and check the hexadecimal value
// of the error, then use Ctrl+F to search for the error in glew.h.
int main(int argc, char** argv)
{
	_STL_VERIFY(TheApp::GetInstance()->Initialize("3D Graphics Engine",
		"shader.vert", "shader.frag",
		SIZE_WIDTH, SIZE_HEIGHT) != false,
	("Engine could not initialize due to: " + to_string(glGetError())).c_str());
	
	while (!glfwWindowShouldClose(TheApp::GetInstance()->getWindow()))
	{
		TheApp::GetInstance()->PollEvents();

		TheApp::GetInstance()->Update();
		TheApp::GetInstance()->Draw();
		
		TheApp::GetInstance()->SwapBuffers();	
	}

	return 0;
}