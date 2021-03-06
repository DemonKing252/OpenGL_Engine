#include "PointLight.h"

Light::Light()
{
	position = colour = glm::vec3(0.0f);
	strength = 0.0f;
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

Light::Light(Light * otherLight) : position(otherLight->position), colour(otherLight->colour), strength(otherLight->strength)
{
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
	_STL_VERIFY(index != -1, "Did you forget to set the light index?");

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
	_STL_VERIFY(index != -1, "Did you forget to set the light index?");

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
