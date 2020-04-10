#pragma once
#include "GeometryMesh.h"
#include "Util.h"
#include "PerlinNoise.h"
#include <fstream>
using namespace std;

#define MOUNTAINEQ1 cos(4/6.f * distance[0]) + 1.0f
#define MOUNTAINEQ2 cos(4/6.f * distance[1]) + 1.0f
#define MOUNTAINEQ3 cos(4/6.f * distance[2]) + 1.0f
#define MOUNTAINEQ4 cos(4/6.f * distance[3]) + 1.0f
class GeometryGenerator
{
public:
	std::vector <GeometryMesh*> mGeometryMesh;
	enum Mesh { CUBE, PYRAMID, SPHEAR, PLANE, SKULL, CAR };

	GeometryGenerator()
	{
		
	}
	~GeometryGenerator()
	{
		
	}
	void createMesh(Mesh mesh);
	void draw(Mesh mesh);
};