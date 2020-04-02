#include "GeometryGenerator.h"
#include "Application.h"
void GeometryGenerator::createMesh(Mesh mesh)
{
	mGeometryMesh.push_back(new GeometryMesh());
	if (mesh == CUBE)
	{
		mGeometryMesh.back()->setNumIndicies(24);
		mGeometryMesh.back()->setNumVertices(24);
		mGeometryMesh.back()->verticies = new Vertex[mGeometryMesh.back()->getNumVertices()]
		{
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f )),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.5f, -0.5f, +0.5f )),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-0.5f, -0.5f, +0.5f)),

			Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(-0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),  glm::vec3(0.5f, -0.5f, -0.5f )),
			Vertex(glm::vec3(0.5f, 0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),  glm::vec3(0.5f, -0.5f, +0.5f )),
			Vertex(glm::vec3(-0.5f, 0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(-0.5f, -0.5f, +0.5f)),

			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-0.5f, -0.5f, +0.5f)),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),glm::vec3(0.5f, -0.5f, +0.5f  )),
			Vertex(glm::vec3(0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),glm::vec3(0.5f, +0.5f, +0.5f  )),
			Vertex(glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-0.5f, +0.5f, +0.5f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(-0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.5f, -0.5f, -0.5f  )),
			Vertex(glm::vec3(0.5f, +0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.5f, +0.5f, -0.5f)  ),
			Vertex(glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(-0.5f, +0.5f, -0.5f)),

			Vertex(glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(+0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(+0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(+0.5f, -0.5f, +0.5f)),
			Vertex(glm::vec3(+0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(+0.5f, +0.5f, +0.5f)),
			Vertex(glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(+0.5f, +0.5f, -0.5f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(-0.5f, -0.5f, -0.5f)),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-0.5f, -0.5f, +0.5f)),
			Vertex(glm::vec3(-0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-0.5f, +0.5f, +0.5f)),
			Vertex(glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(-0.5f, +0.5f, -0.5f)),


		};
		mGeometryMesh.back()->indicies = new GLuint[mGeometryMesh.back()->getNumIndicies()];

		for (int i = 0; i < mGeometryMesh.back()->getNumIndicies(); i++)
		{
			mGeometryMesh.back()->indicies[i] = i;
		}

		mGeometryMesh.back()->setPrimitiveType(GL_QUADS);
	}
	else if (mesh == PYRAMID)
	{
		mGeometryMesh.back()->setNumIndicies(18);
		mGeometryMesh.back()->setNumVertices(9);
		mGeometryMesh.back()->verticies = new Vertex[mGeometryMesh.back()->getNumVertices()]
		{
			//					Positions				 Colours					Texture UVs		-> (Refer to the vertex shader)
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),   glm::vec3(-0.5f, -0.5f, -0.5f )),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),   glm::vec3(0.5f, -0.5f, -0.5f  )),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),   glm::vec3(0.5f, -0.5f, +0.5f  )),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),   glm::vec3(-0.5f, -0.5f, +0.5f )),

			Vertex(glm::vec3(0.0f, +0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f),    glm::vec3(0.0f, +0.5f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),   glm::vec3(-0.5f, -0.5f, -0.5f )),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),   glm::vec3(0.5f, -0.5f, -0.5f  )),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),   glm::vec3(0.5f, -0.5f, +0.5f  )),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),   glm::vec3(-0.5f, -0.5f, +0.5f )),
		};
		mGeometryMesh.back()->indicies = new GLuint[mGeometryMesh.back()->getNumIndicies()]
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

		mGeometryMesh.back()->setPrimitiveType(GL_TRIANGLES);
	}
	else if (mesh == SPHEAR)
	{
		const int sliceCount = 120;
		const int stackCount = 60;

		mGeometryMesh.back()->setNumIndicies(sliceCount * stackCount);
		mGeometryMesh.back()->setNumVertices(sliceCount * stackCount);
		mGeometryMesh.back()->verticies = new Vertex[mGeometryMesh.back()->getNumVertices()];

		double xz = 0.0f;
		double y = 90.0f;
		for (int i = 0; i < sliceCount * stackCount; i += 4)
		{
			// #1 
			
			// 3D Cartesian coordinates (Calculus III)
			// Helpful link -> http://tutorial.math.lamar.edu/Classes/CalcIII/3DCoords.aspx
			float tempX = (0.5f * cos(y * Util::DegToRad())) * cos(xz * Util::DegToRad());
			float tempY = (0.5f * cos(y * Util::DegToRad())) * sin(xz * Util::DegToRad());
			float tempZ = 0.5f * sin(y * Util::DegToRad());

			// first theta - y, second theta [x/z] -> cos(theta) * sin(theta)
			mGeometryMesh.back()->verticies[i].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i].setUV(glm::vec2((xz / 360.0f) + 0.5f, y / 180.0f));
			mGeometryMesh.back()->verticies[i].setNormal(glm::vec3(tempX, tempY, tempZ));
			//cout << 0.5f + (tempX * 1.5f) << endl;

			// #2
			tempX = (0.5f * cos(y * Util::DegToRad())) * cos((xz + 10.0f) * Util::DegToRad());
			tempY = (0.5f * cos(y * Util::DegToRad())) * sin((xz + 10.0f) * Util::DegToRad());
			tempZ = 0.5f * sin(y * Util::DegToRad());
			mGeometryMesh.back()->verticies[i + 1].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i + 1].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 1].setUV(glm::vec2(((xz + 10.0f) / 360.0f) + 0.5f, y / 180.0f));
			mGeometryMesh.back()->verticies[i + 1].setNormal(glm::vec3(tempX, tempY, tempZ));

			// #3
			tempX = (0.5f * cos((y - 10.0f) * Util::DegToRad())) * cos((xz + 10.0f) * Util::DegToRad());
			tempY = (0.5f * cos((y - 10.0f) * Util::DegToRad())) * sin((xz + 10.0f) * Util::DegToRad());
			tempZ = 0.5f * sin((y - 10.0f) * Util::DegToRad());

			mGeometryMesh.back()->verticies[i + 2].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i + 2].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 2].setUV(glm::vec2(((xz + 10.0f) / 360.0f) + 0.5f, (y - 10.0f) / 180.0f));
			mGeometryMesh.back()->verticies[i + 2].setNormal(glm::vec3(tempX, tempY, tempZ));

			// #4
			tempX = (0.5f * cos((y - 10.0f) * Util::DegToRad())) * cos((xz)* Util::DegToRad());
			tempY = (0.5f * cos((y - 10.0f) * Util::DegToRad())) * sin((xz)* Util::DegToRad());
			tempZ = 0.5f * sin((y - 10.0f) * Util::DegToRad());

			mGeometryMesh.back()->verticies[i + 3].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i + 3].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 3].setUV(glm::vec2((xz / 360.0f) + 0.5f, (y - 10.0f) / 180.0f));
			mGeometryMesh.back()->verticies[i + 3].setNormal(glm::vec3(tempX, tempY, tempZ));

			if (i > 0 && i % 360 == 0) { y -= 10.0f; }
			if (xz >= 360.0f) { xz -= 360; }

			xz += 10.0f;

		}


		//};
		mGeometryMesh.back()->indicies = new GLuint[mGeometryMesh.back()->getNumIndicies()];
		for (int i = 0; i < mGeometryMesh.back()->getNumIndicies(); i++)
		{
			mGeometryMesh.back()->indicies[i] = i;
		}

		mGeometryMesh.back()->setPrimitiveType(GL_QUADS);
	}
	
	else if (mesh == PLANE)
	{
		const int rows = 64;
		const int cols = 64;

		// If we want a random location for the mountain:
		//const glm::vec3 mountainPos = glm::vec3(random_float_in_range(-20.0f, +20.0f), 
		//										0.0f, 
		//										random_float_in_range(-20.0f, +20.0f));

		const glm::vec3 mountainPos = glm::vec3(0.0f, 0.0f, 0.0f);
		
		mGeometryMesh.back()->setNumIndicies(rows * cols * 4);
		mGeometryMesh.back()->setNumVertices(rows * cols * 4);
		mGeometryMesh.back()->verticies = new Vertex[mGeometryMesh.back()->getNumVertices()];
		float x = 0.0f;
		float z = 0.0f;

		float distance[4];
		glm::vec3 tempVertex[4];	
		
		for (int i = 0; i < rows * cols * 4; i += 4)
		{
			tempVertex[0] = glm::vec3((0.5f * -cols) + x, 0.0f, (0.5f * -rows) + z);
			distance[0] = glm::length(tempVertex[0] - mountainPos);
			//if (distance[0] <= 10.0f)
			tempVertex[0].y = MOUNTAINEQ1;

			tempVertex[1] = glm::vec3((0.5f * -cols) + x + 1.0f, 0.0f, (0.5f * -rows) + z);
			distance[1] = glm::length(tempVertex[1] - mountainPos);
			//if (distance[1] <= 10.0f)
			tempVertex[1].y = MOUNTAINEQ2;

			tempVertex[2] = glm::vec3((0.5f * -cols) + x + 1.0f, 0.0f, (0.5f * -rows) + z + 1.0f);
			distance[2] = glm::length(tempVertex[2] - mountainPos);
			//if (distance[2] <= 10.0f)
			tempVertex[2].y = MOUNTAINEQ3;

			tempVertex[3] = glm::vec3(glm::vec3((0.5f * -cols) + x, 0.0f, (0.5f * -rows) + z + 1.0f));
			distance[3] = glm::length(tempVertex[3] - mountainPos);
			//if (distance[3] <= 10.0f)
			tempVertex[3].y = MOUNTAINEQ4;

			mGeometryMesh.back()->verticies[i].setPosition(tempVertex[0]);
			mGeometryMesh.back()->verticies[i + 1].setPosition(tempVertex[1]);
			mGeometryMesh.back()->verticies[i + 2].setPosition(tempVertex[2]);
			mGeometryMesh.back()->verticies[i + 3].setPosition(tempVertex[3]);

			for (int j = 0; j < 4; j++)
			{

				glm::vec3 finalColour;
				if (tempVertex[j].y > 7.5f)
					finalColour = glm::vec3(0.1f);
				else if (tempVertex[j].y > 1.5f)
					finalColour = glm::vec3(160 / 255.0f, 82 / 255.0f, 45 / 255.0f);
				else if (tempVertex[j].y > 0.9f)
					finalColour = glm::vec3(153 / 255.0f, 153 / 255.0f, 153 / 255.0f);
				else
					finalColour = glm::vec3(34 / 255.0f, 139 / 255.0f, 34 / 255.0f);

				mGeometryMesh.back()->verticies[i + j].setColour(glm::vec3(finalColour));
			}

			mGeometryMesh.back()->verticies[i].setNormal(mGeometryMesh.back()->verticies[i].getPosition());
			mGeometryMesh.back()->verticies[i + 1].setNormal(mGeometryMesh.back()->verticies[i + 1].getPosition());
			mGeometryMesh.back()->verticies[i + 2].setNormal(mGeometryMesh.back()->verticies[i + 2].getPosition());
			mGeometryMesh.back()->verticies[i + 3].setNormal(mGeometryMesh.back()->verticies[i + 3].getPosition());
			
			mGeometryMesh.back()->verticies[i].setUV(glm::vec2(0.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 1].setUV(glm::vec2(1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 2].setUV(glm::vec2(1.0f, 1.0f));
			mGeometryMesh.back()->verticies[i + 3].setUV(glm::vec2(0.0f, 1.0f));
			
			x += 1.0f;
			if (x == cols)
			{
				z += 1.0f;
				x = 0.0f;
			}
		}
		mGeometryMesh.back()->indicies = new GLuint[mGeometryMesh.back()->getNumIndicies()];
		for (int i = 0; i < cols * rows * 4; i++)
		{
			mGeometryMesh.back()->indicies[i] = i;
		}

		mGeometryMesh.back()->setPrimitiveType(GL_QUADS);
	}
	else if (mesh == SKULL)
	{
		const std::string fileName = "skull.txt";
		fstream inFile;
		inFile.open(fileName);

		_STL_VERIFY(inFile.is_open(), "Could not open file: " + fileName);

		int vertexCount, triangleCount;
		string ignoreThis;

		inFile >> ignoreThis >> vertexCount;
		inFile >> ignoreThis >> triangleCount;
		inFile >> ignoreThis >> ignoreThis >> ignoreThis >> ignoreThis;
		
		mGeometryMesh.back()->setNumIndicies(3 * triangleCount);
		mGeometryMesh.back()->setNumVertices(vertexCount);

		mGeometryMesh.back()->verticies = new Vertex[mGeometryMesh.back()->getNumVertices()];
		mGeometryMesh.back()->indicies = new GLuint[mGeometryMesh.back()->getNumIndicies()];

		glm::vec3 tempVertex;
		glm::vec3 tempNormal;

		for (int i = 0; i < vertexCount; i++)
		{
			inFile >> tempVertex.x >> tempVertex.y >> tempVertex.z;
			inFile >> tempNormal.x >> tempNormal.y >> tempNormal.z;

			mGeometryMesh.back()->verticies[i].setPosition(glm::vec3(tempVertex));
			mGeometryMesh.back()->verticies[i].setNormal(glm::vec3(tempNormal));
			mGeometryMesh.back()->verticies[i].setColour(glm::vec3(0.6f, 0.6f, 0.6f));

			mGeometryMesh.back()->verticies[i].setUV(glm::vec2(0.0f, 0.0f));
		}

		inFile >> ignoreThis;
		inFile >> ignoreThis;
		inFile >> ignoreThis;

		for (int i = 0; i < triangleCount; i++)
		{
			inFile >> mGeometryMesh.back()->indicies[i * 3 + 0];
			inFile >> mGeometryMesh.back()->indicies[i * 3 + 1];
			inFile >> mGeometryMesh.back()->indicies[i * 3 + 2];
		}

		inFile.close();
		mGeometryMesh.back()->setPrimitiveType(GL_TRIANGLES);
	}
}

void GeometryGenerator::draw(Mesh type)
{
	glDrawElements(TheApp::Instance()->mUserInterface->wireFrameEnabled ? GL_LINE_LOOP : mGeometryMesh[type]->getPrimitiveType(),
		mGeometryMesh[type]->getNumIndicies(),
		GL_UNSIGNED_INT,
		0);
}