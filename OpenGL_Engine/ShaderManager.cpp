#include "ShaderManager.h"
ShaderManager* ShaderManager::s_pInstance = nullptr;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

ShaderManager * ShaderManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new ShaderManager();
		return s_pInstance;
	}
	return s_pInstance;
}
GLuint ShaderManager::CompileShader(GLenum type, const char * file) const
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;
	string temp;
	string src;
	fstream inFile;

	// Vertex Shader
	inFile.open(file);

	assert(inFile.is_open());

	while (getline(inFile, temp))
	{
		src += temp + "\n";
	}
	GLuint shader = glCreateShader(type);

	const GLchar* vertSrc = src.c_str();
	glShaderSource(shader, 1, &vertSrc, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << infoLog << endl;
	}
	inFile.close();
	// Fragment Shader
	temp.clear();
	src.clear();

	return shader;
}

GLuint ShaderManager::AttachShader(GLuint vertShader, GLuint fragShader) const
{
	char infoLog[512];
	GLuint core_program;
	GLint success;

	core_program = glCreateProgram();

	glAttachShader(core_program, vertShader);
	glAttachShader(core_program, fragShader);

	glLinkProgram(core_program);

	glGetProgramiv(core_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(core_program, 512, NULL, infoLog);

		cout << infoLog << endl;
	}

	glUseProgram(0);

	return core_program;
}

void ShaderManager::SetUniformMat4x4(const GLuint core_program, const string name, const glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(core_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderManager::SetUniform2f(const GLuint core_program, const string name, const glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(core_program, name.c_str()), value.x, value.y);
}

void ShaderManager::SetUniform3f(const GLuint core_program, const string name, const glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(core_program, name.c_str()), value.x, value.y, value.z);
}

void ShaderManager::SetUniform4f(const GLuint core_program, const string name, const glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(core_program, name.c_str()), value.x, value.y, value.z, value.w);
}

void ShaderManager::SetUniformf(const GLuint core_program, const string name, const float value) const
{
	glUniform1f(glGetUniformLocation(core_program, name.c_str()), value);
}

void ShaderManager::SetUniformi(const GLuint core_program, const string name, const int value) const
{
	glUniform1i(glGetUniformLocation(core_program, name.c_str()), value);
}

void ShaderManager::SetFragmentTextureOnly(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 3);
}

void ShaderManager::SetFragmentColourOnly(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 2);
}

void ShaderManager::SetFragmentTextureAndColourOnly(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 1);
}

void ShaderManager::SetFragmentNone(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 0);
}

void ShaderManager::SetFragmentAllTypes(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 7);
}

void ShaderManager::SetFragmentLightAndTextureOnly(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 4);
}

void ShaderManager::SetFragmentLightAndColourOnly(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 5);
}

void ShaderManager::SetFragmentLightOnly(const GLuint core_program) const
{
	SetUniformi(core_program, "fragStyle", 6);
}

