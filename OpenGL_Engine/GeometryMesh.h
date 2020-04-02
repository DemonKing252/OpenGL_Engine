#pragma once
#include "Vertex.h"
#include <vector>
#include <iostream>
#include "Util.h"
using namespace std;


class GeometryMesh
{
public:

	GeometryMesh();
	~GeometryMesh();

	Vertex* verticies;
	GLuint* indicies;

	void generateBuffers();
	void bindVAO();
	void unBindVAO();

	void setNumVertices(const GLint verticies);
	void setNumIndicies(const GLint indicies);	
	void setPrimitiveType(const GLenum type);

	GLint getNumVertices() const;
	GLint getNumIndicies() const;
	GLenum getPrimitiveType() const;
private:
	GLenum primitiveType;
	GLuint mVAO;
	GLint numVerticies = 0;
	GLint numIndicies = 0;
};