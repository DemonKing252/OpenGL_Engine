#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vec2.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include "Util.h"
#define SPEED 0.1f
using namespace std;
class Camera
{
private:
	static glm::vec3 position;
	static glm::vec3 lookAt;

	static double mPhi, mTheta;
	static double m_dRadius;
public:
	static double mouseX, mouseY;
	static double back_x, back_y;

	static glm::vec3 getPosition();
	static glm::vec3 getLookAt();
	static GLint frameBufferW, frameBufferH;

	static double deltaX, deltaY;

	static bool EventMouseClick(GLFWwindow* window);
	static void UpdateCameraFacing(GLFWwindow* window);
	static void CheckEvents(GLFWwindow* window);
};

