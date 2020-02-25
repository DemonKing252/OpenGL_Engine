#include "Util.h"
#include "ShaderManager.h"


glm::mat4 Util::viewMatrix = glm::mat4(1);
glm::mat4 Util::projMatrix = glm::mat4(1);

double Util::Pi()
{
	return 3.1415926535f;
}

double Util::DegToRad()
{
	return 3.1415926535f / 180.0f;
}

double Util::RadToDeg()
{
	return 180.0f / 3.1415926535f;
}

void Util::Transform(GLuint program, glm::vec3 translation, glm::vec3 scale, glm::vec3 rotAxis, float angle)
{
	glm::mat4 Model;

	Model = glm::mat4(1);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(angle), rotAxis);
	Model = glm::scale(Model, scale);

	// Communicate with the fragment shader to update the models position (relative to the camera) and translation
	TheShaderManager::Instance()->SetUniformMat4x4(program, "M", Model);
	TheShaderManager::Instance()->SetUniformMat4x4(program, "V", viewMatrix);
	TheShaderManager::Instance()->SetUniformMat4x4(program, "P", projMatrix);
	
}
