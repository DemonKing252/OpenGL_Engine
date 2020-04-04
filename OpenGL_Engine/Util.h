#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <cassert>
#include <iostream>
#include "vec3.hpp"
#include "vec2.hpp"
#include "gtc/matrix_transform.hpp"
using namespace std;


#ifndef Util::Pi()
	#define cos_radians(x) cos(static_cast<float>(x * Util::Pi() / 180.0f))
	#define sin_radians(y) sin(static_cast<float>(y * Util::Pi() / 180.0f))
#else
	#define cos_radians(x) cos(static_cast<float>(x * 3.14159f / 180.0f))
	#define sin_radians(y) sin(static_cast<float>(y * 3.14159f / 180.0f))
#endif // !Util::Pi()

#define get_stride_of(count, DataType) sizeof(DataType) * count
#define random_float_in_range(LO, HI) LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)))

class Util
{
public:
	static GLenum wireType1, wireType2;
	
	static glm::mat4 m_4x4ProjMatrix;
	static glm::mat4 m_4x4ViewMatrix;

	static double Pi();
	static double DegToRad();
	static double RadToDeg();

	static void Transform(GLuint program, glm::vec3 translation, glm::vec3 scale, glm::vec3 rotAxis, float angle);
};

