#include "GeometryGenerator.h"
void GeometryGenerator::createMesh(Mesh mesh)
{
	const float toRad = 3.14159f / 180.0f;
	mGeometry.push_back(new GeometryMesh());
	
	if (mesh == SPHEAR)
	{
		const int sliceCount = 120;
		const int stackCount = 60;

		mGeometry.back()->setNumIndicies(sliceCount * stackCount);
		mGeometry.back()->setNumVertices(sliceCount * stackCount);
		mGeometry.back()->verticies = new Vertex[mGeometry.back()->getNumVertices()];

		double xz = 0.0f;
		double y = 90.0f;
		for (int i = 0; i < sliceCount * stackCount; i += 4)
		{
			// #1 
			float tempX = (0.5f * cos(y * toRad)) * cos(xz * toRad);
			float tempY = (0.5f * cos(y * toRad)) * sin(xz * toRad);
			float tempZ = 0.5f * sin(y * toRad);
			// first theta - y, second theta [x/z] -> cos(theta) * sin(theta)
			mGeometry.back()->verticies[i].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometry.back()->verticies[i].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometry.back()->verticies[i].setUV(glm::vec2((xz / 360.0f) + 0.5f, y / 180.0f));
			mGeometry.back()->verticies[i].setNormal(glm::vec3(tempX, tempY, tempZ));
			//cout << 0.5f + (tempX * 1.5f) << endl;

			// #2
			tempX = (0.5f * cos(y * toRad)) * cos((xz + 10.0f) * toRad);
			tempY = (0.5f * cos(y * toRad)) * sin((xz + 10.0f) * toRad);
			tempZ = 0.5f * sin(y * toRad);
			mGeometry.back()->verticies[i + 1].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometry.back()->verticies[i + 1].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometry.back()->verticies[i + 1].setUV(glm::vec2(((xz + 10.0f) / 360.0f) + 0.5f, y / 180.0f));
			mGeometry.back()->verticies[i + 1].setNormal(glm::vec3(tempX, tempY, tempZ));

			// #3
			tempX = (0.5f * cos((y - 10.0f) * toRad)) * cos((xz + 10.0f) * toRad);
			tempY = (0.5f * cos((y - 10.0f) * toRad)) * sin((xz + 10.0f) * toRad);
			tempZ = 0.5f * sin((y - 10.0f) * toRad);

			mGeometry.back()->verticies[i + 2].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometry.back()->verticies[i + 2].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometry.back()->verticies[i + 2].setUV(glm::vec2(((xz + 10.0f) / 360.0f) + 0.5f, (y - 10.0f) / 180.0f));
			mGeometry.back()->verticies[i + 2].setNormal(glm::vec3(tempX, tempY, tempZ));

			// #4
			tempX = (0.5f * cos((y - 10.0f) * toRad)) * cos((xz)* toRad);
			tempY = (0.5f * cos((y - 10.0f) * toRad)) * sin((xz)* toRad);
			tempZ = 0.5f * sin((y - 10.0f) * toRad);

			mGeometry.back()->verticies[i + 3].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometry.back()->verticies[i + 3].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometry.back()->verticies[i + 3].setUV(glm::vec2((xz / 360.0f) + 0.5f, (y - 10.0f) / 180.0f));
			mGeometry.back()->verticies[i + 3].setNormal(glm::vec3(tempX, tempY, tempZ));

			if (i > 0 && i % 360 == 0) { y -= 10.0f; }
			if (xz >= 360.0f) { xz -= 360; }

			xz += 10.0f;

		}


		//};
		mGeometry.back()->indicies = new GLuint[mGeometry.back()->getNumIndicies()];
		for (int i = 0; i < sliceCount * stackCount; i++)
		{
			mGeometry.back()->indicies[i] = i;
		}

	}
	else if (mesh == PYRAMID)
	{
		mGeometry.back()->setNumIndicies(18);
		mGeometry.back()->setNumVertices(9);
		mGeometry.back()->verticies = new Vertex[mGeometry.back()->getNumVertices()]
		{
			//					Positions				 Colours					Texture UVs		-> (Refer to the vertex shader)
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(-0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.5f, -0.5f, +0.5f)),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),  glm::vec3(-0.5f, -0.5f, +0.5f)),
																									 
			Vertex(glm::vec3(0.0f, +0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f),   glm::vec3(0.0f, +0.5f, 0.0f)),
																									 
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),   glm::vec3(-0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),  glm::vec3(0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),  glm::vec3(0.5f, -0.5f, +0.5f)),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),   glm::vec3(-0.5f, -0.5f, +0.5f)),
		};
		mGeometry.back()->indicies = new GLuint[mGeometry.back()->getNumIndicies()]
		{ 
			// Bottom
			5, 6, 7,
			7, 8, 5,
			
			// Sides
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4
			
		};
	}
}

void GeometryGenerator::draw(Mesh type)
{
	//glDrawArrays(GL_QUADS, 0, mGeometry[type]->getNumVertices());
	glDrawElements(type == SPHEAR ? GL_QUADS : GL_TRIANGLES, mGeometry[type]->getNumIndicies(), GL_UNSIGNED_INT, 0);
}