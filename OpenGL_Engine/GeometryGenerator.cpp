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
			
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, 0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, 0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f )),
			Vertex(glm::vec3(0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f )),
			Vertex(glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f)),
			Vertex(glm::vec3(0.5f, +0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, -1.0f)),
			Vertex(glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, -1.0f)),

			Vertex(glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f)),
			Vertex(glm::vec3(+0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
			Vertex(glm::vec3(+0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
			Vertex(glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(1.0f, 0.0f, 0.0f)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),  glm::vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, +0.5f, +0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),  glm::vec3(-1.0f, 0.0f, 0.0f)),
			

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
			// Vertex Layout --> [Position, Color, TextureCoordinate, Normal]
			// Size -> 44 bytes per vertex
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

		float xz = 0.0f;
		float y = 90.0f;

		float stepOver = 6.0f;
		float stepDown = 6.0f;

		for (int i = 0; i < sliceCount * stackCount; i += 4)
		{
			// 1 unit in length
			// ( <---------> )
			
			// 3D Cartesian coordinates (Calculus III)
			// Helpful link -> http://tutorial.math.lamar.edu/Classes/CalcIII/3DCoords.aspx
			float tempX = (0.5f * cos_radians(y)) * cos_radians(xz);
			float tempY = (0.5f * cos_radians(y)) * sin_radians(xz);
			float tempZ = 0.5f * sin_radians(y);

			// #1 - Top Left of quad

			// first theta - y, second theta [x/z] -> cos(theta) * sin(theta)
			mGeometryMesh.back()->verticies[i].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i].setUV(glm::vec2((xz / 360.0f) + 0.5f, y / 180.0f));
			mGeometryMesh.back()->verticies[i].setNormal(glm::vec3(tempX, tempY, tempZ));
			
			// #2 - Top Right of quad
			tempX = (0.5f * cos_radians(y)) * cos_radians((xz + stepOver));
			tempY = (0.5f * cos_radians(y)) * sin_radians((xz + stepOver));
			tempZ = 0.5f * sin_radians(y);
			mGeometryMesh.back()->verticies[i + 1].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i + 1].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 1].setUV(glm::vec2(((xz + stepOver) / 360.0f) + 0.5f, y / 180.0f));
			mGeometryMesh.back()->verticies[i + 1].setNormal(glm::vec3(tempX, tempY, tempZ));

			// #3 - Bottom Right of the quad
			tempX = (0.5f * cos_radians((y - stepDown))) * cos_radians((xz + stepOver));
			tempY = (0.5f * cos_radians((y - stepDown))) * sin_radians((xz + stepOver));
			tempZ = 0.5f * sin_radians((y - stepDown));

			mGeometryMesh.back()->verticies[i + 2].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i + 2].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 2].setUV(glm::vec2(((xz + stepOver) / 360.0f) + 0.5f, (y - stepDown) / 180.0f));
			mGeometryMesh.back()->verticies[i + 2].setNormal(glm::vec3(tempX, tempY, tempZ));

			// #4 - Bottom Left of the quad
			tempX = (0.5f * cos_radians((y - stepDown))) * cos_radians((xz));
			tempY = (0.5f * cos_radians((y - stepDown))) * sin_radians((xz));
			tempZ = 0.5f * sin_radians((y - stepDown));

			mGeometryMesh.back()->verticies[i + 3].setPosition(glm::vec3(tempX, tempY, tempZ));
			mGeometryMesh.back()->verticies[i + 3].setColour(glm::vec3(1.0f, 1.0f, 0.0f));
			mGeometryMesh.back()->verticies[i + 3].setUV(glm::vec2((xz / 360.0f) + 0.5f, (y - stepDown) / 180.0f));
			mGeometryMesh.back()->verticies[i + 3].setNormal(glm::vec3(tempX, tempY, tempZ));

			xz += stepOver;
			if (i > 0 && (int)xz % 360 == 0) { y -= stepDown; xz = 0.0f; }

		}

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

		const glm::vec3 mountainPos = glm::vec3(0.0f, 0.0f, 0.0f);
		
		mGeometryMesh.back()->setNumIndicies(rows * cols * 4);
		mGeometryMesh.back()->setNumVertices(rows * cols * 4);
		mGeometryMesh.back()->verticies = new Vertex[mGeometryMesh.back()->getNumVertices()];
		float x = 0.0f;
		float z = 0.0f;

		glm::vec3 tempVertex[4];	
		
		for (int i = 0; i < rows * cols * 4; i += 4)
		{
			tempVertex[0] = glm::vec3((0.5f * -cols) + x, 0.0f, (0.5f * -rows) + z);
			tempVertex[1] = glm::vec3((0.5f * -cols) + x + 1.0f, 0.0f, (0.5f * -rows) + z);
			tempVertex[2] = glm::vec3((0.5f * -cols) + x + 1.0f, 0.0f, (0.5f * -rows) + z + 1.0f);
			tempVertex[3] = glm::vec3(glm::vec3((0.5f * -cols) + x, 0.0f, (0.5f * -rows) + z + 1.0f));
			
			mGeometryMesh.back()->verticies[i].setPosition(tempVertex[0]);
			mGeometryMesh.back()->verticies[i + 1].setPosition(tempVertex[1]);
			mGeometryMesh.back()->verticies[i + 2].setPosition(tempVertex[2]);
			mGeometryMesh.back()->verticies[i + 3].setPosition(tempVertex[3]);
			x += 1.0f;
			if (x == cols)
			{
				z += 1.0f;
				x = 0.0f;
			}
		}
		

		// Start ---------------------------------------------->
		// 2D Perlin Noise Generator (Random Interpolation)
		// -------------------
		int nOutputWidth = rows * 2;
		int nOutputHeight = cols * 2;
		float *fNoiseSeed2D = nullptr;
		float *fPerlinNoise2D = nullptr;
		
		int nOctaveCount = 5;
		float fScalingBias = 2.0f;
		int nMode = 1;
		
		fNoiseSeed2D = new float[nOutputWidth * nOutputHeight];
		fPerlinNoise2D = new float[nOutputWidth * nOutputHeight];
		
		for (int i = 0; i < nOutputWidth * nOutputHeight; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
		
		// 2D Perlin noise generator
		PerlinNoise::GeneratePerlinNoise(nOutputWidth, nOutputHeight, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);
		
		float g_pixelBandWidth[4];
		for (int x = 0; x < nOutputWidth+82; x+=4)
		{
			for (int y = 0; y < nOutputHeight; y++)
			{
				
				//////////////////////////////////////////////////////////////////////
				g_pixelBandWidth[0] = ( (float)(fPerlinNoise2D[(y-1) * nOutputWidth + (x-2) > 0 ? (y-1) * nOutputWidth + (x-2) : 0] * 30.0f) - 6.0f);
				g_pixelBandWidth[1] = ( (float)(fPerlinNoise2D[(y-1) * nOutputWidth + (x+2) > 0 ? (y-1) * nOutputWidth + (x+2) : 1] * 30.0f) - 6.0f);
				g_pixelBandWidth[2] = ( (float)(fPerlinNoise2D[(y+1) * nOutputWidth + (x+2) > 0 ? (y+1) * nOutputWidth + (x+2) : 2] * 30.0f) - 6.0f);
				g_pixelBandWidth[3] = ( (float)(fPerlinNoise2D[(y+1) * nOutputWidth + (x-2) > 0 ? (y+1) * nOutputWidth + (x-2) : 3] * 30.0f) - 6.0f);
				//////////////////////////////////////////////////////////////////////

				mGeometryMesh.back()->verticies[y * (nOutputWidth) + x].setPosition(glm::vec3(
					mGeometryMesh.back()->verticies[y * (nOutputWidth)+x].getPosition().x,
					g_pixelBandWidth[0],
					mGeometryMesh.back()->verticies[y * (nOutputWidth)+x].getPosition().z
				));
				
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 1].setPosition(glm::vec3(
					mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 1].getPosition().x,
					g_pixelBandWidth[1],
					mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 1].getPosition().z
				));
				
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 2].setPosition(glm::vec3(
					mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x)+2].getPosition().x,
					g_pixelBandWidth[2],
					mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x)+2].getPosition().z
				));
				
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 3].setPosition(glm::vec3(
					mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x)+3].getPosition().x,
					g_pixelBandWidth[3],
					mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 3].getPosition().z
				));

				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 0].setNormal(mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 0].getPosition());
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 1].setNormal(mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 1].getPosition());
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 2].setNormal(mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 2].getPosition());
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 3].setNormal(mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 3].getPosition());

				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 0].setUV(glm::vec2(0.0f, 0.0f));
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 1].setUV(glm::vec2(1.0f, 0.0f));
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 2].setUV(glm::vec2(1.0f, 1.0f));
				mGeometryMesh.back()->verticies[(y * (nOutputWidth)+x) + 3].setUV(glm::vec2(0.0f, 1.0f));
			}
		}
		// Final check for un-defined vertex positions
		for (int i = 0; i < rows * cols * 4; i++)
		{
			glm::vec3 tempVertex = mGeometryMesh.back()->verticies[i].getPosition();
			
			//cout << tempVertex.y << endl;
			
			// Usually an undefined variable is filled with a garbage value like +infinity or -infinity
			if (tempVertex.y < -600.0f || tempVertex.y > 600.0f)
			{
				tempVertex.y = 0.0f;
			
				mGeometryMesh.back()->verticies[i].setPosition(tempVertex);
			}
		
		}
		mGeometryMesh.back()->indicies = new GLuint[mGeometryMesh.back()->getNumIndicies()];
		for (int i = 0; i < cols * rows * 4; i++)
		{
			mGeometryMesh.back()->indicies[i] = i;
		}
		mGeometryMesh.back()->setPrimitiveType(GL_QUADS);

		//  -> End
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
	else if (mesh == CAR)
	{
		const std::string fileName = "car.txt";
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
			mGeometryMesh.back()->verticies[i].setColour(glm::vec3(tempVertex.x, tempVertex.y, tempNormal.z));
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
	glDrawElements(TheApp::Instance()->m_userInterface->wireFrameEnabled ? GL_LINE_LOOP : mGeometryMesh[type]->getPrimitiveType(),
		mGeometryMesh[type]->getNumIndicies(),
		GL_UNSIGNED_INT,
		0);
}