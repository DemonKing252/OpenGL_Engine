#include "GeometryMesh.h"
GeometryMesh::GeometryMesh()
{
}

GeometryMesh::~GeometryMesh()
{
	glBindVertexArray(0);
}

void GeometryMesh::generateBuffers()
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// index buffer
	GLuint indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndicies, indicies, GL_STATIC_DRAW);

	// Generate a vertex buffer
	GLuint vertexBuffer = 0;

	// Set the active buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// NOTE:
	// Our buffer is now bound, we can now write data to it.

	// Send our data to OpenGLs V-RAM
	// Note: If we want an index buffer then we would use GL_ELEMENT_ARRAY_BUFFER.
	// GL_STATIC_DRAW is a gl Hint that these verticies will not change, the alternative would be GL_DYNAMIC_DRAW
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVerticies * 11, verticies, GL_STATIC_DRAW);

	// Describe the data set -> Vec2 at layout location 0 in the vertex shader. 2 floats for vertex positions.
	// Note: sizeof() will return the size of an array in bytes (4 bytes per float -> 4 * 5 = 20 bytes, you could alternatively put 20)
	

	// Vertex Layout #0 --> Vertex positions -> Vec3()
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, get_stride_of(1, Vertex), 0);
	glEnableVertexAttribArray(0);

	// Vertex Layout #1 --> Color -> Vec3()
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, get_stride_of(1, Vertex), (void*)(static_cast<uint32_t>(FLOAT3_MEMORY_SIZE)));
	glEnableVertexAttribArray(1);

	// Vertex Layout #2 --> Texture coordinate -> Vec2()
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, get_stride_of(1, Vertex), (void*)(static_cast<uint32_t>(2 * FLOAT3_MEMORY_SIZE)));
	glEnableVertexAttribArray(2);

	// Vertex Layout #3 --> Normal (for diffuse/specular lighting) -> Vec3()
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, get_stride_of(1, Vertex), (void*)(static_cast<uint32_t>(2 * FLOAT3_MEMORY_SIZE + FLOAT2_MEMORY_SIZE)));
	glEnableVertexAttribArray(3);

	// Un-bind vertex array to prevent possible data corruption.
	glBindVertexArray(0);
}

void GeometryMesh::bindVAO()
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
