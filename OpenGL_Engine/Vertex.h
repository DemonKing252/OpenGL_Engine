#pragma once
#include "MainHeaders.h"
class Vertex
{
private:
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec2 UV;			
	glm::vec3 normal;		
public:

	Vertex();
	Vertex(glm::vec3 position, glm::vec3 colour = glm::vec3(1), glm::vec2 UV = glm::vec2(0), glm::vec3 normal = glm::vec3(0));
	~Vertex();

	glm::vec3 getPosition() const;
	glm::vec3 getColour() const;
	glm::vec2 getUV() const;
	glm::vec3 getNormal() const;

	void setUV(glm::vec2 UV);
	void setPosition(glm::vec3 position);
	void setColour(glm::vec3 colour);
	void setNormal(glm::vec3 normal);
	

	float m_xDist = 0.0f;
};

