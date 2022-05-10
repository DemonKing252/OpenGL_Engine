#pragma once
#include "Material.h"
#include "GeometryGenerator.h"
#include "GUI.h"
#include "MainHeaders.h"
#include <vector>
#include "RenderItem.h"
#include "ParticleSystem.h"
class Scene
{
public:
	// Component thats part of the scene. A different scene may have different animate effects.
	// For example, a lava land would have lava animating much slower.
	
	GLfloat uv = 0.0f;

	std::vector <Light*> m_vPointLights;
	std::vector <RenderItem*> m_vRenderItems;
	GeometryGenerator geoGen;

	GeometryMesh swingArm;

	float cntr1 = 0.0f, cntr2 = 0.0f;
	float angle = -90.0f;

	std::unique_ptr<ParticleSystem3D> ParticleSystem;

	Scene();
	~Scene();
	float t = 0.0f;

	void update(float DeltaTime);
	void draw(float DeltaTime);
	void setup();
	void clean();

};

