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

Transform::Transform(glm::vec3 p)
{
	this->position = p;
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

void Transform::operator+=(Transform * addTo)
{
	this->position.x += addTo->position.x;
	this->position.y += addTo->position.y;
	this->position.z += addTo->position.z;
}

void Transform::operator-=(Transform * subtractFrom)
{
	this->position.x -= subtractFrom->position.x;
	this->position.y -= subtractFrom->position.y;
	this->position.z -= subtractFrom->position.z;
}

void Transform::operator*=(Transform * multiply)
{
	this->position.x *= multiply->position.x;
	this->position.y *= multiply->position.y;
	this->position.z *= multiply->position.z;
}

void Transform::operator/=(Transform * divide)
{
	this->position.x /= divide->position.x;
	this->position.y /= divide->position.y;
	this->position.z /= divide->position.z;
}

Transform* Transform::operator+(Transform * other)
{
	return new Transform(
		glm::vec3(this->position.x + other->position.x, 
				  this->position.y + other->position.y, 
				  this->position.z + other->position.z));
}

Transform* Transform::operator-(Transform * other)
{
	return new Transform(
		glm::vec3(this->position.x - other->position.x,
				  this->position.y - other->position.y,
				  this->position.z - other->position.z));
}

Transform* Transform::operator*(Transform * other)
{
	return new Transform(
		glm::vec3(this->position.x * other->position.x,
				  this->position.y * other->position.y,
				  this->position.z * other->position.z));
}

Transform* Transform::operator/(Transform * other)
{

	return new Transform(
		glm::vec3(this->position.x / other->position.x,
			      this->position.y / other->position.y,
			      this->position.z / other->position.z));
}

void Transform::operator=(Transform * other)
{
	this->position = other->position;
	this->rotationAxis = other->rotationAxis;
	this->scale = other->scale;
}

bool Transform::operator==(Transform * other)
{
	return 
	(
		this->position.x == other->position.x &&
		this->position.y == other->position.y &&
		this->position.z == other->position.z
	);
}

bool Transform::operator!=(Transform * other)
{
	return
	(
		this->position.x != other->position.x &&
		this->position.y != other->position.y &&
		this->position.z != other->position.z
	);
}

void Transform::updateUniformMatrix(const GLuint core_program)
{
	Util::Transform(core_program, position, scale, rotationAxis, angle);
}
