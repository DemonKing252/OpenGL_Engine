#pragma once
#include "GeometryMesh.h"
#include "Util.h"
#define MOUNTAINEQ1 20.0f / 3+1/8*pow(distance[0], 2)
#define MOUNTAINEQ2 20.0f / 3+1/8*pow(distance[1], 2)
#define MOUNTAINEQ3 20.0f / 3+1/8*pow(distance[2], 2)
#define MOUNTAINEQ4 20.0f / 3+1/8*pow(distance[3], 2)

class GeometryGenerator
{
public:

	std::vector <GeometryMesh*> mGeometry;

	enum Mesh { PYRAMID, SPHEAR, PLANE };

	GeometryGenerator()
	{
		
	}
	~GeometryGenerator()
	{
		
	}
	void createMesh(Mesh mesh);
	void draw(Mesh mesh);
};