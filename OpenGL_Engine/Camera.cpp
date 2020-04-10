#include "Camera.h"
#include "ShaderManager.h"
#include "Application.h"
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
GLint Camera::frameBufferW = 0;
GLint Camera::frameBufferH = 0;

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

glm::vec3 outerCamera = glm::vec3(0);
glm::vec3 forwardVector = glm::vec3(0, 0, -1);
glm::vec3 rightVector;
glm::vec3 worldUp = glm::vec3(0, 1, 0);

void Camera::UpdateCameraFacing(GLFWwindow* window)
{
	back_x = mouseX;
	back_y = mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);

	//cout << mouseX << " " << mouseY << endl;
	// Sensitivity 60% could use a ImGui::SliderFloat for that?
	deltaX = (mouseX - back_x) * 0.6f;
	deltaY = (mouseY - back_y) * 0.6f;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		m_Yaw += deltaX * 0.5f;
		
		if ( (deltaY < 0.0f && m_Pitch < 90.0f + (deltaY * 0.5f)) )
			m_Pitch -= deltaY * 0.5f;
		else if ( (deltaY > 0.0f && m_Pitch > -90.0f + (deltaY * 0.5f)) )
			m_Pitch -= deltaY * 0.5f;

	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (deltaY < 0.0f && mRadius >= 2.0f - (deltaY * 0.25f))
			mRadius += deltaY * 0.25f;

		else if (deltaY > 0.0f && mRadius <= 40.0f - (deltaY * 0.25f))
			mRadius += deltaY * 0.25f;
	}
}

void Camera::CheckEvents(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		position += forwardVector * SPEED;
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		position -= rightVector * SPEED;
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
		position -= forwardVector * SPEED;
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		position += rightVector * SPEED;
	
	
	// Cylindrical Coordinates
	// Calculus III Link -> http://tutorial.math.lamar.edu/Classes/CalcIII/CylindricalCoords.aspx
	forwardVector.x = cos_radians(m_Yaw) * cos_radians(m_Pitch);
	forwardVector.y = sin_radians(m_Pitch);
	forwardVector.z = sin_radians(m_Yaw) * cos_radians(m_Pitch);
	
	// Normalize forward Vector
	forwardVector = glm::normalize(forwardVector);
	
	// Normalize forward Vector, then get the cross product of the camera world facing (0, -1, 0) for upside down.
	rightVector = glm::normalize(glm::cross(forwardVector, worldUp));
	
	lookAt = position + forwardVector;

	outerCamera = glm::vec3(mRadius * forwardVector.x, mRadius * forwardVector.y, mRadius * forwardVector.z);
	
	// FPS Camera

	/*
	Util::m_4x4ViewMatrix = glm::lookAt(
		position, 
		lookAt, 
		glm::vec3(0,1,0));
		TheShaderManager::Instance()->SetUniform3f(TheApp::Instance()->getCoreProgram(), "mCameraFacing", position);
	*/

	// Spinner camera (similar to hoomans template)
	
	
	Util::m_4x4ViewMatrix = glm::lookAt(
	    outerCamera,
	    glm::vec3(0, 0, 0),
	    glm::vec3(0, 1, 0));
	TheShaderManager::Instance()->SetUniform3f(TheApp::Instance()->getCoreProgram(), "mCameraFacing", outerCamera);
	
	
}
