#include "Camera.h"
#include "ShaderManager.h"
double Camera::mRadius = 7.0f;
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

	//cout << mouseX << " " << mouseY << endl;
	// Sensitivity 60% could use a ImGui::SliderFloat for that?
	deltaX = (mouseX - back_x) * 0.6f;
	deltaY = (mouseY - back_y) * 0.6f;

	if (btnL == GLFW_PRESS)
	{
		if (deltaX > 0)
			mTheta += deltaX;
		else if (deltaX < 0)
			mTheta -= -deltaX;
	
		if (deltaY > 0 && mPhi <= 180.0f - deltaY)
			mPhi += deltaY;
		else if (deltaY < 0 && mPhi >= deltaY)
			mPhi -= -deltaY;
	}
	else if (btnR == GLFW_PRESS)
	{
		if (deltaY > 0 && mRadius <= 50.0f)
		{
			mRadius += deltaY * 0.05f;
		}
		else if (deltaY < 0 && mRadius >= 1.0f)
		{
			mRadius -= -deltaY * 0.05f;
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
