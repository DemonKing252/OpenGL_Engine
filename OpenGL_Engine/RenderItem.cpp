#include "RenderItem.h"
#include "Application.h"
#include "Scene.h"
#include "Util.h"

RenderItem::RenderItem(GeometryGenerator::Mesh mMeshType, FragmentStyle style, std::string m, float alpha, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotAxis, float angle)
	: meshType(mMeshType)
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
	// step 1: update the model matrix
	transform->updateUniformMatrix(TheApp::Instance()->getCoreProgram());

	// step 2: change the fragment style [Options are: color, lighting, texturing ]
	TheShaderManager::Instance()->SetUniformi(TheApp::Instance()->getCoreProgram(), "fragStyle", fragStyle);
	
	// step 3: change the alpha test (if blending is applicable)
	TheShaderManager::Instance()->SetUniformf(TheApp::Instance()->getCoreProgram(), "alpha", alphaTest);
	
	// step 4: does the height affect the fragment strength?
	TheShaderManager::Instance()->SetUniformi(TheApp::Instance()->getCoreProgram(), "changeHeight", static_cast<int>(m_bHeightEffects));

	// step 4: bind the texture object
	TheApp::Instance()->m_materialMap[material].bindTexture();

	// step 5: bind the vertex array object
	currScene->geoGen.mGeometryMesh[meshType]->bindVertexArrayObject();

	// step 6: draw
	currScene->geoGen.draw(meshType);

	// step 7: reset the animation and height mapping, don't need it
	TheShaderManager::Instance()->SetUniform2f(TheApp::Instance()->getCoreProgram(), "uvMapping", glm::vec2(0.0f));
	TheShaderManager::Instance()->SetUniformi(TheApp::Instance()->getCoreProgram(), "changeHeight", 0);

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
