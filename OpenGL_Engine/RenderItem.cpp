#include "RenderItem.h"
#include "Application.h"
#include "Scene.h"
#include "Util.h"

RenderItem::RenderItem(GeometryGenerator::Mesh mMeshType, FragmentStyle style, std::string m, float alpha, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotAxis, float angle)
	: mMeshType(mMeshType)
{
	transform = new Transform(translate, scale, rotAxis, angle);

	this->alphaTest = alpha;
	this->material = m;
	this->fragStyle = style;
	
}

RenderItem::~RenderItem()
{
}

void RenderItem::draw(Scene * scene) const
{
	transform->updateUniformMatrix(TheApp::Instance()->getCoreProgram());
	

	TheShaderManager::Instance()->SetUniformi(TheApp::Instance()->getCoreProgram(), "fragStyle", fragStyle);
	TheShaderManager::Instance()->SetUniformf(TheApp::Instance()->getCoreProgram(), "alpha", alphaTest);

	TheApp::Instance()->mMaterialMap[material].bindTexture();
	scene->geoGen.mGeometryMesh[mMeshType]->bindVAO();
	scene->geoGen.draw(mMeshType);

	TheShaderManager::Instance()->SetUniform2f(TheApp::Instance()->getCoreProgram(), "uvMapping", glm::vec2(0.0f));
}

void RenderItem::update(Scene * scene) const
{
	scene->uv += 0.0002f;

	if (scene->uv >= 1.0f)
	{
		scene->uv = 0.0f;
	}
	TheShaderManager::Instance()->SetUniform2f(TheApp::Instance()->getCoreProgram(), "uvMapping", glm::vec2(scene->uv, scene->uv * 0.5f));
}
