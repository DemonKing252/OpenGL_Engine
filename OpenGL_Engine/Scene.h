#pragma once
#include "Material.h"
#include "GeometryGenerator.h"
#include "GUI.h"
#include "MainHeaders.h"
#include <vector>
class Scene
{
private:
	
public:
	std::vector <PointLight*> m_vPointLights;
	std::unordered_map <std::string, Material> mMaterialMap;
	GeometryGenerator geoGen;

	Scene();
	~Scene();

	void Update();
	void Render();
	void Setup();
	void Clean();

};

