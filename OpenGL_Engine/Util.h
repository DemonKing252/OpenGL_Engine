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

class Util
{
public:
	static glm::mat4 projMatrix, viewMatrix;

	static double Pi();
	static double DegToRad();
	static double RadToDeg();

	static void Transform(GLuint program, glm::vec3 translation, glm::vec3 scale, glm::vec3 rotAxis, float angle, glm::vec3 offSet = glm::vec3(1));
};

