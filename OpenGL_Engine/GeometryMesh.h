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

	GLuint indexBuffer = 0;
	GLuint vertexBuffer = 0;
	Vertex* verticies;
	GLuint* indicies;

	void deleteBuffers();
	void generateBuffers();
	void bindVertexArrayObject();
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