#pragma once
#include "GeometryGenerator.h"

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
	glm::mat4 World;

	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotAxis;

	float angle;

	GeometryGenerator::Mesh mMeshType;
	FragmentStyle fragStyle;

public:
	bool m_bShouldAnimate = false;
	float alphaTest;
	std::string material;

	RenderItem();
	RenderItem(GeometryGenerator::Mesh mMeshType, FragmentStyle style, std::string material, float alpha, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotAxis, float angle);
	~RenderItem();

	void setTranslate(glm::vec3 translate);
	void setScaling(glm::vec3 scale);
	void setRotation(glm::vec3 rotAxis);
	void setAngle(float angle);

	glm::vec3 getTranslate() const;
	glm::vec3 getScaling() const;
	glm::vec3 getRotation() const;
	float getAngle() const;

	void draw(Scene * scene) const;
	void update(Scene * scene) const;
};
