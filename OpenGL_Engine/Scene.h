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
	GLfloat uvX = 0.0f;
public:
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

