#include "Transform.h"

Transform::Transform()
{
	position = scale = rotationAxis = glm::vec3(0.0f);
	angle = 0.0f;
}

Transform::~Transform()
{
}

Transform::Transform(Transform * other)
{
	this->position = other->position;
	this->rotationAxis = other->rotationAxis;
	this->scale = other->scale;

	World = glm::mat4(1);
	World = glm::translate(World, other->position);
	World = glm::rotate(World, glm::radians(other->angle), other->rotationAxis);
	World = glm::scale(World, other->scale);
}

Transform::Transform(glm::vec3 p, glm::vec3 s, glm::vec3 r, float a)
{
	this->position = p;
	this->scale = s;
	this->rotationAxis = r;
	this->angle = a;

	World = glm::mat4(1);
	World = glm::translate(World, position);
	World = glm::rotate(World, glm::radians(angle), rotationAxis);
	World = glm::scale(World, scale);
}

void Transform::operator=(Transform * other)
{
	this->position = other->position;
	this->rotationAxis = other->rotationAxis;
	this->scale = other->scale;
}

void Transform::updateUniformMatrix(const GLuint core_program)
{
	Util::Transform(core_program, position, scale, rotationAxis, angle);
}
