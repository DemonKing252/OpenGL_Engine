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
float s_fPitch = 0.0f;
float s_fYaw = -90.0f;

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
	deltaX = (mouseX - back_x) * 0.4f;
	deltaY = (mouseY - back_y) * 0.4f;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		s_fYaw += deltaX * 0.5f;
		
		if ( (deltaY < 0.0f && s_fPitch < 90.0f + (deltaY * 0.5f)) )
			s_fPitch -= deltaY * 0.5f;
		else if ( (deltaY > 0.0f && s_fPitch > -90.0f + (deltaY * 0.5f)) )
			s_fPitch -= deltaY * 0.5f;

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

	// What is s_f? 
	// - s stands for a static member, f is reprenting as a float variable (4 bytes of memory).
	forwardVector.x = cos_radians(s_fYaw) * cos_radians(s_fPitch);
	forwardVector.y = sin_radians(s_fPitch);
	forwardVector.z = sin_radians(s_fYaw) * cos_radians(s_fPitch);
	
	// Normalize forward Vector
	
	// The forward vector we can already use for keys [W] and [S] because its a vector facing infront of the camera!
	forwardVector = glm::normalize(forwardVector);
	
	// On the other hand, strafing left and right requires the cross product of the forward vector and up vector (up camera facing).
	rightVector = glm::normalize(glm::cross(forwardVector, worldUp));
	

	lookAt = position + forwardVector;

	outerCamera = glm::vec3(mRadius * forwardVector.x, mRadius * forwardVector.y, mRadius * forwardVector.z);
	
	// FPS Camera

	
	Util::m_4x4ViewMatrix = glm::lookAt(
		position, 
		lookAt, 
		glm::vec3(0,1,0));
	
	TheShaderManager::Instance()->SetUniform3f(TheApp::Instance()->getCoreProgram(), "mCameraFacing", position);

	// Spinner camera (similar to the D3D Box App)
	
	//Util::m_4x4ViewMatrix = glm::lookAt(
	//    outerCamera,
	//    glm::vec3(0, 0, 0),
	//    glm::vec3(0, 1, 0));

}
