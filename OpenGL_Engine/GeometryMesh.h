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

	void setNumVertices(GLint verticies);
	void setNumIndicies(GLint indicies);

	void generateText();


	GLint getNumVertices();
	GLint getNumIndicies();
private:
	GLuint mVAO;
	GLint numVerticies = 0;
	GLint numIndicies = 0;
};





