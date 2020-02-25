#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vec2.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;
class Camera
{
private:
	static glm::vec3 position;
	static double mouseX, mouseY;
	static double back_x, back_y;
	static double mPhi, mTheta;
	static double mRadius;
public:
	static glm::vec3 getPosition();
	static double deltaX, deltaY;

	static bool EventMouseClick(GLFWwindow* window);
	static void UpdateCameraFacing(GLFWwindow* window);
	static void UpdateCameraPosition();

	

};

