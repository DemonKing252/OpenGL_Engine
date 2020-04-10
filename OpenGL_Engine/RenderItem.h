#pragma once
#include "GeometryGenerator.h"
#include "Transform.h"
class Scene;
enum FragmentStyle
{
	NONE,
	TEXTURE_AND_COLOR_ONLY,
	COLOR_ONLY,
	TEXTURE_ONLY,
	TEXTURE_AND_LIGHT_ONLY,
	LIGHT_AND_COLOR_ONLY,
	LIGHT_ONLY,
	ALL_TYPES
};

class RenderItem
{
private:
	GeometryGenerator::Mesh mMeshType;
	FragmentStyle fragStyle;
public:
	glm::vec3 position;
	float m_fBobFactor = 0.10f;
	float m_fBobSpeed = 0.05f;
	float m_y = 0.0f;

	bool m_bApplyPhysics = false;

	Transform* transform;

	bool m_bShouldAnimate = false;
	float alphaTest;
	std::string material;

	RenderItem(GeometryGenerator::Mesh mMeshType, FragmentStyle style, std::string material, float alpha, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotAxis, float angle);
	~RenderItem();

	void draw(Scene * scene) const;
	void update(Scene * scene);
};
