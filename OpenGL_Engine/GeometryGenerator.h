#pragma once
#include "GeometryMesh.h"
#include "Util.h"
#define MOUNTAINEQ1 cos(4/6.f * distance[0]) + 1.0f
#define MOUNTAINEQ2 cos(4/6.f * distance[1]) + 1.0f
#define MOUNTAINEQ3 cos(4/6.f * distance[2]) + 1.0f
#define MOUNTAINEQ4 cos(4/6.f * distance[3]) + 1.0f

class GeometryGenerator
{
public:
	std::vector <GeometryMesh*> mGeometry;

	enum Mesh { CUBE, PYRAMID, SPHEAR, PLANE };

	GeometryGenerator()
	{
		
	}
	~GeometryGenerator()
	{
		
	}
	void createMesh(Mesh mesh);
	void draw(Mesh mesh);
};