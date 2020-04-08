#include "Material.h"

void Material::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, mtextureID);
}

void Material::load(const char * fileName)
{
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
	
	_STL_VERIFY(image != 0, "Could not load image");
	
	glGenTextures(1, &mtextureID);
	glBindTexture(GL_TEXTURE_2D, mtextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Material::clean()
{
	glDeleteTextures(1, &mtextureID);
}

