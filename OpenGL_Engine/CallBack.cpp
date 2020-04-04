#include "CallBack.h"
#include "Application.h"

void CallBack::mouse_btn_callback(GLFWwindow* window, int button, int action, int mods)
{
	if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &Camera::mouseX, &Camera::mouseY);
	}
}
void CallBack::window_resize_callback(GLFWwindow* window, int x, int y)
{
	GLint _width;
	GLint _height;
	glfwGetWindowSize(window, &_width, &_height);

	Camera::frameBufferW = _width;
	Camera::frameBufferH = _height;

	// Change the view port size respective to the new window size.
	glViewport(0, 0, _width, _height);

	//cout << "Window: " << _width << " " << _height << endl;

}
void CallBack::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}