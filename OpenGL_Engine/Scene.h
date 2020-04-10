#pragma once
#include "Material.h"
#include "GeometryGenerator.h"
#include "GUI.h"
#include "MainHeaders.h"
#include <vector>
#include "RenderItem.h"
class Scene
{
public:
	glm::vec3 oceanTranslatation = glm::vec3(0.0f, -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f, 0.0f);	// For floaters.

	// Component thats part of the scene. A different scene may have different animate effects.
	// For example, a lava land would have lava animating much slower.
	GLfloat uv = 0.0f;

	std::vector <Light*> m_vPointLights;
	std::vector <RenderItem*> m_vRenderItems;
	GeometryGenerator geoGen;

	Scene();
	~Scene();

	void update();
	void draw();
	void setup();
	void clean();

};

