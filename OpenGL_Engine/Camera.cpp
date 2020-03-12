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
glm::vec3 Camera::position = glm::vec3(0, 0, 3);
glm::vec3 Camera::lookAt = glm::vec3(0, 0, 0);


glm::vec3 Camera::getPosition()
{
	return position;
}

glm::vec3 Camera::getLookAt()
{
	return lookAt;
}

bool Camera::EventMouseClick(GLFWwindow* window)
{
	int keyW = glfwGetKey(window, GLFW_KEY_W);
	int keyA = glfwGetKey(window, GLFW_KEY_A);
	int keyS = glfwGetKey(window, GLFW_KEY_S);
	int keyD = glfwGetKey(window, GLFW_KEY_D);
	int btnL = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int btnR = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	
	if ( (btnL | btnR | keyW | keyA | keyS | keyD) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}
float m_Roll = 0.0f;
float m_Pitch = 0.0f;
float m_Yaw = -90.0f;

glm::vec3 frontVec = glm::vec3(0, 0, -1);
glm::vec3 rightVec;
glm::vec3 worldUp = glm::vec3(0, 1, 0);

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
		m_Yaw += deltaX * 0.5f;
		m_Pitch -= deltaY * 0.5f;
	}
}

void Camera::CheckEvents(GLFWwindow * window)
{
	bool m_bMovement = false;

	int keyW = glfwGetKey(window, GLFW_KEY_W);
	int keyA = glfwGetKey(window, GLFW_KEY_A);
	int keyS = glfwGetKey(window, GLFW_KEY_S);
	int keyD = glfwGetKey(window, GLFW_KEY_D);

	if (keyW == GLFW_PRESS) {
		position += frontVec * 0.1f;
	}
	if (keyA == GLFW_PRESS) {
		position -= rightVec * 0.1f;
	}
	if (keyS == GLFW_PRESS) {
		position -= frontVec * 0.1f;
	}
	if (keyD == GLFW_PRESS) {
		position += rightVec * 0.1f;
	}

	frontVec.x = cos(m_Yaw * Util::DegToRad()) * cos(m_Pitch * Util::DegToRad());
	frontVec.y = sin(m_Pitch * Util::DegToRad());
	frontVec.z = sin(m_Yaw * Util::DegToRad()) * cos(m_Pitch * Util::DegToRad());
	frontVec = glm::normalize(frontVec);
	rightVec = glm::normalize(glm::cross(frontVec, worldUp));
	
	lookAt = position + frontVec;

	Util::m_4x4ViewMatrix = glm::lookAt(
		position, 
		lookAt, 
		glm::vec3(0,1,0));

}
