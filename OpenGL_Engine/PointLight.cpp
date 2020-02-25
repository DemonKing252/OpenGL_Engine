#include "PointLight.h"

PointLight::PointLight()
{
	index++;
}

PointLight::~PointLight()
{

}

PointLight::PointLight(glm::vec3 position, glm::vec3 colour, float strength)
{
	this->position = position;
	this->colour = colour;
	this->strength = strength;

}

void PointLight::updateBuffers(GLuint core_program)
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

glm::vec3 PointLight::getPosition() const
{
	return position;
}

glm::vec3 PointLight::getColour() const
{
	return colour;
}

float PointLight::getStrength() const
{
	return strength;
}

void PointLight::setPosition(glm::vec3 position)
{
	this->position = position;
}

void PointLight::setColour(glm::vec3 colour)
{
	this->colour = colour;
}

void PointLight::setStrength(float strength)
{
	this->strength = strength;
}
