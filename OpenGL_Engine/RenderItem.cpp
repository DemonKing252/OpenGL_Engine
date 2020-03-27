#include "RenderItem.h"
#include "Application.h"
#include "Scene.h"
#include "Util.h"

RenderItem::RenderItem()
{
	translate = scale = rotAxis = glm::vec3(0.0f);
	angle = 0.0f;
}

RenderItem::RenderItem(GeometryGenerator::Mesh mMeshType, FragmentStyle style, std::string m, float alpha, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotAxis, float angle)
	: mMeshType(mMeshType), translate(translate), scale(scale), rotAxis(rotAxis), angle(angle)
{
	this->alphaTest = alpha;
	this->material = m;
	this->fragStyle = style;
	World = glm::mat4(0.0f);
	World = glm::mat4(1);
	World = glm::translate(World, translate);
	World = glm::rotate(World, glm::radians(angle), rotAxis);
	World = glm::scale(World, scale);

}

RenderItem::~RenderItem()
{
}

void RenderItem::setTranslate(glm::vec3 translate)
{
	this->translate = translate;
}

void RenderItem::setScaling(glm::vec3 scale)
{
	this->scale = scale;
}

void RenderItem::setRotation(glm::vec3 rotAxis)
{
	this->rotAxis = rotAxis;
}

void RenderItem::setAngle(float angle)
{
	this->angle = angle;
}

glm::vec3 RenderItem::getTranslate() const
{
	return translate;
}

glm::vec3 RenderItem::getScaling() const
{
	return scale;
}

glm::vec3 RenderItem::getRotation() const
{
	return rotAxis;
}

float RenderItem::getAngle() const
{
	return angle;
}

void RenderItem::draw(Scene * scene) const
{
	Util::Transform(TheApp::Instance()->getCoreProgram(), this->translate, this->scale, this->rotAxis, this->angle);
	

	TheShaderManager::Instance()->SetUniformi(TheApp::Instance()->getCoreProgram(), "fragStyle", fragStyle);
	TheShaderManager::Instance()->SetUniformf(TheApp::Instance()->getCoreProgram(), "alpha", alphaTest);

	scene->mMaterialMap[material].bindTexture();
	scene->geoGen.mGeometry[mMeshType]->bindVAO();
	scene->geoGen.draw(mMeshType);
}

