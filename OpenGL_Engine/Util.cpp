#include "Util.h"
#include "ShaderManager.h"


glm::mat4 Util::m_4x4ViewMatrix = glm::mat4(1);
glm::mat4 Util::m_4x4ProjMatrix = glm::mat4(1);
GLenum Util::wireType1 = GL_QUADS;
GLenum Util::wireType2 = GL_TRIANGLES;
glm::vec3 Util::waveCentre = glm::vec3(1.0f, 0.0f, 0.0f);

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

void Util::Transform(GLuint core_program, glm::vec3 translation, glm::vec3 scale, glm::vec3 rotAxis, float angle)
{
	glm::mat4 Model;

	Model = glm::mat4(1);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(angle), rotAxis);
	Model = glm::scale(Model, scale);

	// Update the uniform matricies that handle 3D rendering 
	
	TheShaderManager::Instance()->SetUniformMatrix4x4(core_program, "M", Model);
	TheShaderManager::Instance()->SetUniformMatrix4x4(core_program, "V", m_4x4ViewMatrix);
}
