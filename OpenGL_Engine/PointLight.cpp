#include "PointLight.h"

Light::Light()
{

}

Light::~Light()
{

}

Light::Light(glm::vec3 position, glm::vec3 colour, float strength)
{
	this->position = position;
	this->colour = colour;
	this->strength = strength;

}


glm::vec3 Light::getPosition() const
{
	return position;
}

glm::vec3 Light::getColour() const
{
	return colour;
}

float Light::getStrength() const
{
	return strength;
}

void Light::setPosition(const glm::vec3 position)
{
	this->position = position;
}

void Light::setColour(const glm::vec3 colour)
{
	this->colour = colour;
}
 
void Light::setStrength(const float strength)
{
	this->strength = strength;
}

PointLight::PointLight()
{
}

PointLight::PointLight(glm::vec3 position, glm::vec3 colour, float strength)
{
	this->position = position;
	this->colour = colour;
	this->strength = strength;
}

PointLight::~PointLight()
{
}

void PointLight::updateBuffers(const GLuint core_program)
{
	// Catch an index number not being initialized
		assert(index != -1);

	string front = "pLight[" + to_string(index) + "]";

	const char* buffer;

	string temp;

	temp = front + ".position";
	buffer = temp.c_str();

	//cout << buffer << endl;

	TheShaderManager::Instance()->SetUniform3f(core_program, buffer, position);

	temp = front + ".colour";
	buffer = temp.c_str();

	TheShaderManager::Instance()->SetUniform3f(core_program, buffer, colour);

	temp = front + ".strength";
	buffer = temp.c_str();

	TheShaderManager::Instance()->SetUniformf(core_program, buffer, strength);
}

void PointLight::clean(const GLuint core_program)
{
	// Catch an index number not being initialized
	assert(index != -1);

	string front = "pLight[" + to_string(index) + "]";

	const char* buffer;

	position = glm::vec3(0);
	colour = glm::vec3(0);
	strength = 0.0f;

	string temp;

	temp = front + ".position";
	buffer = temp.c_str();

	//cout << buffer << endl;

	TheShaderManager::Instance()->SetUniform3f(core_program, buffer, position);

	temp = front + ".colour";
	buffer = temp.c_str();

	TheShaderManager::Instance()->SetUniform3f(core_program, buffer, colour);

	temp = front + ".strength";
	buffer = temp.c_str();

	TheShaderManager::Instance()->SetUniformf(core_program, buffer, strength);
}
