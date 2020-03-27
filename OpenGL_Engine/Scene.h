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

	std::vector <PointLight*> m_vPointLights;
	std::vector <RenderItem*> m_vRenderItems;
	std::unordered_map <std::string, Material> mMaterialMap;
	GeometryGenerator geoGen;

	Scene();
	~Scene();

	void Update();
	void Render();
	void Setup();
	void Clean();

};

