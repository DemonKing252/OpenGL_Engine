#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>
class CallBack
{
public:
	static void mouse_btn_callback(GLFWwindow* window, int button, int action, int mods);
	static void window_resize_callback(GLFWwindow* window, int x, int y);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

