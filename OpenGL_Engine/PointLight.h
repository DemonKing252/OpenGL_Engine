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

	// Default Constructor
	Light();
	// Constructor
	Light(glm::vec3 position, glm::vec3 color = glm::vec3(1, 1, 1), float strenth = 1.0f);
	// Copy Constructor
	Light(Light* otherLight);
	// De-structor
	~Light();
	// Getters
	glm::vec3 getPosition() const;
	glm::vec3 getColour() const;
	float getStrength() const;

	// Mutators
	void setPosition(const glm::vec3 position);
	void setColour(const glm::vec3 colour);
	void setStrength(const float strength);

	// Abstract functions
	virtual void updateBuffers(const GLuint core_program) = 0;
	virtual void clean(const GLuint core_program) = 0;
	// Why constant? Well we don't need a copy to that memory address because were not going to modify it. 
	// Just a little performance optimization.
} Light;
typedef class PointLight : public Light
{
public:
	PointLight();
	PointLight(glm::vec3 position, glm::vec3 colour = glm::vec3(1, 1, 1), float strenth = 1.0f);
	~PointLight();

	void updateBuffers(const GLuint core_program);
	void clean(const GLuint core_program);
} PointLight;