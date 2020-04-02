#pragma once
#include "vec3.hpp"
#include "vec2.hpp"
#include "gtc/matrix_transform.hpp"
#include "Util.h"
class Transform
{
private:
	glm::mat4 World;
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotationAxis;

	float angle;

	// Default contructor
	Transform();
	~Transform();

	// Copy constructor
	Transform(Transform* other);
	Transform(glm::vec3 p, glm::vec3 s, glm::vec3 r, float a);


	void operator=(Transform* other);

	void updateUniformMatrix(const GLuint core_program);
};

