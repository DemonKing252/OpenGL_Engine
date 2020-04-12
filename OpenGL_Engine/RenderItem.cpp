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

	this->position = transform->position;
}

RenderItem::~RenderItem()
{
}

void RenderItem::draw(Scene * currScene) const
{
	transform->updateUniformMatrix(TheApp::Instance()->getCoreProgram());
	

	TheShaderManager::Instance()->SetUniformi(TheApp::Instance()->getCoreProgram(), "fragStyle", fragStyle);
	TheShaderManager::Instance()->SetUniformf(TheApp::Instance()->getCoreProgram(), "alpha", alphaTest);

	TheApp::Instance()->m_materialMap[material].bindTexture();
	currScene->geoGen.mGeometryMesh[mMeshType]->bindVAO();
	currScene->geoGen.draw(mMeshType);

	TheShaderManager::Instance()->SetUniform2f(TheApp::Instance()->getCoreProgram(), "uvMapping", glm::vec2(0.0f));
}

void RenderItem::update(Scene * currScene)
{
	if (m_bShouldAnimate)
	{
		// Water animation
		// fix this later
		currScene->uv += 0.01f;

		if (currScene->uv >= 1.0f)
		{
			currScene->uv = 0.0f;
		}
		TheShaderManager::Instance()->SetUniform2f(TheApp::Instance()->getCoreProgram(), "uvMapping", glm::vec2(currScene->uv, 1.0f));
	}
	
	if (m_bApplyPhysics)
	{
		m_desiredFactor += 0.0625f;

		currY = 0.5f * sin(0.5f * m_desiredFactor);

		transform->position.y = -0.65f*1.2 - (0.9f / 2.0f) - 0.2f - 1.0f + currY;// + (m_fBobFactor * sin(m_y * 3.141f / Util::Pi()));

		m_y += m_fBobSpeed;
	}
}
