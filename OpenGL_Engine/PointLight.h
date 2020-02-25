#pragma once
#include "MainHeaders.h"
#include "ShaderManager.h"
#include <cstdio>
class PointLight
{
private:
	glm::vec3 position;
	glm::vec3 colour;
	float strength;
public:
	int index = -1;
	PointLight();
	~PointLight();
	PointLight(glm::vec3 position, glm::vec3 colour = glm::vec3(1, 1, 1), float strenth = 1.0f);
	
	void updateBuffers(GLuint core_program);

	glm::vec3 getPosition() const;
	glm::vec3 getColour() const;
	float getStrength() const;

	void setPosition(glm::vec3 position);
	void setColour(glm::vec3 colour);
	void setStrength(float strength);
};

