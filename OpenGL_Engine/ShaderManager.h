#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <iosfwd>
#include <vector>
using namespace std;
typedef class ShaderManager
{
private:
	/*
	I went through the SDL text book in semester 2 and found something unique called the singleton design pattern
	which is what I'm using here in this OpenGL Engine.
	It should only be used if you know your going have only ONE instance of a specific class
	Static members instances are preferable for this because every instance is shared across 
	every other instances of the class
	*/
	// To ensure that this instance is only created statically through our static instance getter.
	ShaderManager();	
	
	static ShaderManager* s_pInstance;
public:
	// Ensure that this class instance cannot be copied elsewhere (it is a singleton after all).
	// To do this we can delete the copy constructor
	ShaderManager(ShaderManager*) = delete;


	~ShaderManager();
	static ShaderManager* Instance();
	
	GLuint compileShaderFromFile(const GLenum type, const char* file) const;
	GLuint compileShaderFromString(const GLenum type, string src) const;

	GLuint attachShaders(const GLuint vertShader, const GLuint fragShader) const;
	//void linkProgram(const GLuint core_program);

	void SetUniformMatrix4x4(const GLuint core_program, const string name, const glm::mat4 value) const;
	
	void SetUniform2f(const GLuint core_program, const string name, const glm::vec2 value) const;
	void SetUniform3f(const GLuint core_program, const string name, const glm::vec3 value) const;
	void SetUniform4f(const GLuint core_program, const string name, const glm::vec4 value) const;

	void SetUniformf(const GLuint core_program, const string name, const float value) const;
	void SetUniformi(const GLuint core_program, const string name, const int value) const;

	// General Fragment
	void SetFragmentTextureOnly(const GLuint core_program) const;
	void SetFragmentColourOnly(const GLuint core_program) const;
	void SetFragmentTextureAndColourOnly(const GLuint core_program) const;
	void SetFragmentNone(const GLuint core_program) const;
	
	// Lighting Fragment
	void SetFragmentAllTypes(const GLuint core_program) const;
	void SetFragmentLightAndTextureOnly(const GLuint core_program) const;
	void SetFragmentLightAndColourOnly(const GLuint core_program) const;
	void SetFragmentLightOnly(const GLuint core_program) const;

	// Blending
	void SetFragmentAlphaBlend(const GLuint core_program, const GLfloat alpha) const;

	// Animating Textures.
	void SetUVMapping(const GLint core_program, const glm::vec2 map, const bool shouldAnimate) const;
} ShaderManager, TheShaderManager;