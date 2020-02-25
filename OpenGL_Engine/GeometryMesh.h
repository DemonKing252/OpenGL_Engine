#pragma once
#include "Vertex.h"
#include <vector>
#include <iostream>
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


	GLint getNumVertices() const;
	GLint getNumIndicies() const;
private:
	GLuint mVAO;
	GLint numVerticies = 0;
	GLint numIndicies = 0;
};





