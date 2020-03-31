#pragma once
#include "Material.h"
#include "GeometryGenerator.h"
#include "GUI.h"
#include "MainHeaders.h"
#include <vector>
#include "RenderItem.h"
class Scene
{
private:


public:
	// Component thats part of the scene. A different scene may have different animate effects.
	// For example, a lava land would have lava animating much slower.
	GLfloat uv = 0.0f;

	std::vector <Light*> m_vPointLights;
	std::vector <RenderItem*> m_vRenderItems;
	GeometryGenerator geoGen;

	Scene();
	~Scene();

	void Update();
	void draw();
	void Setup();
	void clean();

};

