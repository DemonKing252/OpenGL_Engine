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
	else if (mesh == PLANE)
	{
		const int rows = 64;
		const int cols = 64;

		const glm::vec3 mountainPos = glm::vec3(-15.0f, 0.0f, 0.0f);
		

		mGeometry.back()->setNumIndicies(rows * cols * 4);
		mGeometry.back()->setNumVertices(rows * cols * 4);
		mGeometry.back()->verticies = new Vertex[mGeometry.back()->getNumVertices()];
		float x = 0.0f;
		float z = 0.0f;
		float distance[4];
		glm::vec3 tempVertex[4];
		for (int i = 0; i < rows * cols * 4; i += 4)
		{
			tempVertex[0] = glm::vec3((0.5f * -cols) + x, 0.0f, (0.5f * -rows) + z);
			distance[0] = glm::length(tempVertex[0] - mountainPos);
			if (distance[0] <= 10.0f)
				tempVertex[0].y = 2.0f / 0.2f * sin(15.0f*distance[0] * Util::DegToRad());

			tempVertex[1] = glm::vec3((0.5f * -cols) + x + 1.0f, 0.0f, (0.5f * -rows) + z);
			distance[1] = glm::length(tempVertex[1] - mountainPos);
			if (distance[1] <= 10.0f)
				tempVertex[1].y = 2.0f / 0.2f * sin(15.0f * distance[1] * Util::DegToRad());

			tempVertex[2] = glm::vec3((0.5f * -cols) + x + 1.0f, 0.0f, (0.5f * -rows) + z + 1.0f);
			distance[2] = glm::length(tempVertex[2] - mountainPos);
			if (distance[2] <= 10.0f)
				tempVertex[2].y = 2.0f / 0.2f * sin(15.0f * distance[2] * Util::DegToRad());

			tempVertex[3] = glm::vec3(glm::vec3((0.5f * -cols) + x, 0.0f, (0.5f * -rows) + z + 1.0f));
			distance[3] = glm::length(tempVertex[3] - mountainPos);
			if (distance[3] <= 10.0f)
				tempVertex[3].y = 2.0f / 0.2f * sin(15.0f * distance[3] * Util::DegToRad());

			mGeometry.back()->verticies[i].setPosition(tempVertex[0]);
			mGeometry.back()->verticies[i + 1].setPosition(tempVertex[1]);
			mGeometry.back()->verticies[i + 2].setPosition(tempVertex[2]);
			mGeometry.back()->verticies[i + 3].setPosition(tempVertex[3]);

			for (int j = 0; j < 4; j++)
			{
				
				glm::vec3 finalColour;
				if (tempVertex[j].y > 7.5f)
					finalColour = glm::vec3(0.1f);
				else if (tempVertex[j].y > 5.0f)
					finalColour = glm::vec3(160 / 255.0f, 82 / 255.0f, 45/255.0f);
				else if (tempVertex[j].y > 2.5f || distance[j] < 15.0f)
					finalColour = glm::vec3(153 / 255.0f, 153 / 255.0f, 153 / 255.0f);
				else
					finalColour = glm::vec3(34/255.0f, 139/255.0f, 34/255.0f);


				mGeometry.back()->verticies[i + j].setColour(glm::vec3(finalColour));
			}

			
			
			mGeometry.back()->verticies[i].setNormal(    mGeometry.back()->verticies[i].getPosition());
			mGeometry.back()->verticies[i + 1].setNormal(mGeometry.back()->verticies[i+1].getPosition());
			mGeometry.back()->verticies[i + 2].setNormal(mGeometry.back()->verticies[i+2].getPosition());
			mGeometry.back()->verticies[i + 3].setNormal(mGeometry.back()->verticies[i+3].getPosition());
			//glm::vec3 height = glm::length()

			mGeometry.back()->verticies[i].setUV(    glm::vec2(0.0f, 0.0f));
			mGeometry.back()->verticies[i + 1].setUV(glm::vec2(1.0f, 0.0f));
			mGeometry.back()->verticies[i + 2].setUV(glm::vec2(1.0f, 1.0f));
			mGeometry.back()->verticies[i + 3].setUV(glm::vec2(0.0f, 1.0f));
			//glm::vec3 height = glm::length()

			x += 1.0f;
			if (x == cols)
			{
				z += 1.0f;
				x = 0.0f;
			}
			
		}
		mGeometry.back()->indicies = new GLuint[mGeometry.back()->getNumIndicies()];
		for (int i = 0; i < cols * rows * 4; i++)
		{
			mGeometry.back()->indicies[i] = i;
		}

	}
}

void GeometryGenerator::draw(Mesh type)
{
	//glDrawArrays(GL_QUADS, 0, mGeometry[type]->getNumVertices());
	glDrawElements(type == SPHEAR || type == PLANE ? Util::wireType1 : Util::wireType2, mGeometry[type]->getNumIndicies(), GL_UNSIGNED_INT, 0);
}