#pragma once
#include "vec3.hpp"
#include "vec2.hpp"
#include "gtc/matrix_transform.hpp"
#include "Util.h"
class Transform
{
private:
	glm::mat4 World;				// World-space matrix
public:
	glm::vec3 position;				// 3D Vector Position		(word space)
	glm::vec3 scale;				// 3D Vector Scale		
	glm::vec3 rotationAxis;			// 3D Vector Rotation Axis

	float angle;					// Angle (relative to the rotation axis)

	// Default contructor
	Transform();
	~Transform();

	// Copy constructor
	Transform(Transform* other);
	Transform(glm::vec3 p);
	Transform(glm::vec3 p, glm::vec3 s, glm::vec3 r, float a);

	// Arthemic operations
	void operator+=(Transform* addTo);
	void operator-=(Transform* subtractFrom);
	void operator*=(Transform* multiply);
	void operator/=(Transform* divide);

	Transform* operator+(Transform* other);
	Transform* operator-(Transform* other);
	Transform* operator*(Transform* other);
	Transform* operator/(Transform* other);

	// Assignment operations
	void operator=(Transform* other);

	// Control flow operations
	bool operator==(Transform* other);
	bool operator!=(Transform* other);

	void updateUniformMatrix(const GLuint core_program);
};

