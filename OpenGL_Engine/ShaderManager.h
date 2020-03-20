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
class ShaderManager
{
private:
	/*
	I went through the SDL text book in semester 2 and found something unique called the singleton design pattern
	which is what I'm using here in this OpenGL Engine.
	It should only be used if you know your going have only ONE instance of a specific class
	Static members instances are preferable for this because every instance is shared across 
	every other instances of the class
	*/
	static ShaderManager* s_pInstance;
	ShaderManager();
public:
	~ShaderManager();
	static ShaderManager* Instance();
	
	GLuint CompileShader(const GLenum type, const char* file) const;
	GLuint AttachShader(const GLuint vertShader, const GLuint fragShader) const;
	
	void SetUniformMat4x4(const GLuint core_program, const string name, const glm::mat4 value) const;
	
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
	void SetFragmentBlend(const GLuint core_program, const GLfloat alpha) const;



};
typedef ShaderManager TheShaderManager;