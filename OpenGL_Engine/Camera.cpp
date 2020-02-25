#include "Camera.h"
#include "ShaderManager.h"
double Camera::mRadius = 4.0f;
double Camera::mTheta = 0.0f;
double Camera::mPhi = 90.0f;
double Camera::deltaX = 0.0f;
double Camera::deltaY = 0.0f;
double Camera::mouseX = 0;
double Camera::mouseY = 0;
double Camera::back_x = 0;
double Camera::back_y = 0;
glm::vec3 Camera::position = glm::vec3(0, 0, 4);

glm::vec3 Camera::getPosition()
{
	return position;
}

bool Camera::EventMouseClick(GLFWwindow* window)
{
	int btnL = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int btnR = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	
	if (btnL == GLFW_PRESS || btnR == GLFW_PRESS)
	{
		return true;
	}
	return false;
}
void Camera::UpdateCameraFacing(GLFWwindow* window)
{
	int btnL = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int btnR = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	

	back_x = mouseX;
	back_y = mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);

	deltaX = mouseX - back_x;
	deltaY = mouseY - back_y;

	if (btnL == GLFW_PRESS)
	{
		if (deltaX > 0)
			mTheta += 4.0f;
		else if (deltaX < 0)
			mTheta -= 4.0f;

		if (deltaY > 0 && mPhi <= 176.0f)
			mPhi += 3.0f;
		else if (deltaY < 0 && mPhi >= 5.0f)
			mPhi -= 3.0f;
	}
	else if (btnR == GLFW_PRESS)
	{
		if (deltaY > 0 && mRadius <= 10.0f)
		{
			mRadius += 0.25f;
		}
		else if (deltaY < 0 && mRadius >= 1.0f)
		{
			mRadius -= 0.25f;
		}
	}
}


void Camera::UpdateCameraPosition()
{

	cout << deltaX << " " << deltaY << endl;

	position.x = mRadius * sin(mPhi * 3.141f / 180.0f) * cos(mTheta * 3.141f / 180.0f);
	position.z = mRadius * sin(mPhi * 3.141f / 180.0f) * sin(mTheta * 3.141f / 180.0f);
	position.y = mRadius * cos(mPhi * 3.141f / 180.0f);

}
