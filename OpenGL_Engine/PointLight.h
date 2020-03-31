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
	Light(glm::vec3 position, glm::vec3 colour = glm::vec3(1, 1, 1), float strenth = 1.0f);

	// Copy Constructor
	Light(Light* otherLight);

	// De-structor
	~Light();
	
	// Why constant? Well we don't need a copy to that memory address because were not going to modify it. 
	// A little performance optimization! 

	// Getters
	glm::vec3 getPosition() const;
	glm::vec3 getColour() const;
	float getStrength() const;

	// Mutators
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

	void updateBuffers(const GLuint core_program);
	void clean(const GLuint core_program);
} PointLight;