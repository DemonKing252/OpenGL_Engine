#include "GeometryMesh.h"
GeometryMesh::GeometryMesh()
{
}

GeometryMesh::~GeometryMesh()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void GeometryMesh::deleteBuffers()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void GeometryMesh::generateBuffers()
{
	// Vertex array object buffer
	// This allows us to easily control different objects 
	// When you want to draw a specific shape, bind that vertex array
	
	// -----------------------------------------------------------------
	// As long as the buffer is active in V-RAM then this will work.
	// -----------------------------------------------------------------

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// Index buffer: size of an unsigned integer (4 bytes) * the number of indicies you have 
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndicies, indicies, GL_DYNAMIC_DRAW);

	// Vertex buffer: [vertex size (11 floats * size of float (4 bytes)) = 44 bytes] * total number of verticies 
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, stride_of(numVerticies, Vertex), verticies, GL_DYNAMIC_DRAW);

	// Vertex Layout #0 --> positions -> Vec3() --> Start of the vertex so offset will be 0 bytes.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride_of(1, Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex Layout #1 --> Color -> Vec3() --> Offset from previous vertex is 12 bytes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride_of(1, Vertex), (void*)(FLOAT3_MEMORY_SIZE));
	glEnableVertexAttribArray(1);

	// Vertex Layout #2 --> Texture coordinate -> Vec2() --> Offset from previous vertex is 24 bytes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride_of(1, Vertex), (void*)(2*FLOAT3_MEMORY_SIZE));
	glEnableVertexAttribArray(2);

	// Vertex Layout #3 --> Normal (for diffuse/specular lighting) -> Vec3() --> Offset from previous vertex is 32 bytes
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride_of(1, Vertex), (void*)(2*FLOAT3_MEMORY_SIZE+FLOAT2_MEMORY_SIZE));
	glEnableVertexAttribArray(3);

	// Un-bind vertex array to prevent possible data corruption.
	glBindVertexArray(0);

}

void GeometryMesh::bindVertexArrayObject()
{
	glBindVertexArray(mVAO);
}

void GeometryMesh::unBindVAO()
{
	glBindVertexArray(0);
}
 
void GeometryMesh::setNumVertices(const GLint verticies)
{
	this->numVerticies = verticies;
}

void GeometryMesh::setNumIndicies(const GLint indicies)
{
	this->numIndicies = indicies;
}

void GeometryMesh::setPrimitiveType(const GLenum type)
{
	this->primitiveType = type;
}

GLint GeometryMesh::getNumVertices()const
{
	return numVerticies;
}

GLint GeometryMesh::getNumIndicies()const
{
	return numIndicies;
}

GLenum GeometryMesh::getPrimitiveType() const
{
	return primitiveType;
}
