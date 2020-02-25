#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(glm::vec3 position, glm::vec3 colour, glm::vec2 UV, glm::vec3 normal)
{
	this->position = position;
	this->colour = colour;
	this->UV = UV;
	this->normal = normal;
}

Vertex::~Vertex()
{
}

glm::vec3 Vertex::getPosition() const
{
	return position;
}

glm::vec3 Vertex::getColour() const
{
	return colour;
}

void Vertex::setUV(glm::vec2 UV)
{
	this->UV = UV;
}

void Vertex::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Vertex::setColour(glm::vec3 colour)
{
	this->colour = colour;
}

void Vertex::setNormal(glm::vec3 normal)
{
	this->normal = normal;
}

glm::vec2 Vertex::getUV() const
{
	return UV;
}

glm::vec3 Vertex::getNormal() const
{
	return normal;
}
