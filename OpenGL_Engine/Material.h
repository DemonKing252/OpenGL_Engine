#pragma once
#include "MainHeaders.h"
#include <SOIL.h>
#include <unordered_map>
class Material
{
public:
	void bindTexture();
	void load(const char* fileName);
private:
	GLuint mtextureID;
	int width;
	int height;
	unsigned char* fileName;
};

