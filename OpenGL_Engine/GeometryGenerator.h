#pragma once
#include "GeometryMesh.h"
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