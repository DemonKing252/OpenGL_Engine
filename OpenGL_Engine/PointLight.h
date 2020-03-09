#pragma once
#include "MainHeaders.h"
#include "ShaderManager.h"
#include <cstdio>
typedef class Light
{
protected:
	glm::vec3 position;
	glm::vec3 colour;
	float strength;
public:
	int index = -1;
	Light();
	~Light();
	Light(glm::vec3 position, glm::vec3 colour = glm::vec3(1, 1, 1), float strenth = 1.0f);
	
	virtual void updateBuffers(const GLuint core_program) = 0;
	virtual void clean(const GLuint core_program) = 0;

	glm::vec3 getPosition() const;
	glm::vec3 getColour() const;
	float getStrength() const;

	void setPosition(const glm::vec3 position);
	void setColour(const glm::vec3 colour);
	void setStrength(const float strength);
} Light;
typedef class PointLight : public Light
{
private:

public:
	PointLight();
	PointLight(glm::vec3 position, glm::vec3 colour = glm::vec3(1, 1, 1), float strenth = 1.0f);
	~PointLight();

	void updateBuffers(const GLuint core_program)override;
	void clean(const GLuint core_program)override;
} PointLight;