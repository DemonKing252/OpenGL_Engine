#include "ParticleSystem.h"
#include "Application.h"
ParticleSystem3D::ParticleSystem3D()
{
}
ParticleSystem3D::~ParticleSystem3D()
{
}
void ParticleSystem3D::SpawnEmitter(glm::vec3 color, int count, float speed, glm::vec3 originPosition, Axis axis, GeometryGenerator::Mesh meshType)
{
	assert(count != 0);
	assert(speed != 0.0f);
	
	float angle = 0.0f;
	float slice_count = 360.0f / (float)count;

	m_particles.reserve(count);

	for (int i = 0; i < count; i++)
	{
		m_particles.push_back(std::make_shared<Particle>());
		m_particles.back()->color = color;
		m_particles.back()->angle = angle;
		m_particles.back()->speed = speed;
		m_particles.back()->scale = glm::vec3(0.1f);
		m_particles.back()->position = originPosition;
		m_particles.back()->axis = axis;

		//1, 0, 0
		switch (axis)
		{
		case Axis::X:
			m_particles.back()->direction = glm::vec3(0.0f, cos_radians(angle), sin_radians(angle));
			break;

		case Axis::Y:
			m_particles.back()->direction = glm::vec3(cos_radians(angle), 0.0f, sin_radians(angle));
			break;

		case Axis::Z:
			m_particles.back()->direction = glm::vec3(cos_radians(angle), sin_radians(angle), 0.0f);
			break;
		default:
			cerr << "Not a valid Axis given!" << endl;
			assert(0);
			break;

		}

		angle += slice_count;

	}
	
}

void ParticleSystem3D::UpdateParticles(float DeltaTime)
{
	cout << "PARTICLE SIZE: " << m_particles.size() << endl;
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->timeNow += DeltaTime;
		m_particles[i]->position += m_particles[i]->direction * (m_particles[i]->speed * DeltaTime );

		if (m_particles.size() < MAX_PARTICLES)
		{
			if (m_particles[i]->timeNow >= .05f)
			{

				m_particles.push_back(std::make_shared<Particle>());


				m_particles.back()->color = m_particles[i]->color;
				m_particles.back()->speed = m_particles[i]->speed;
				m_particles.back()->scale = glm::vec3(0.1f);
				m_particles.back()->position = m_particles[i]->position;
				m_particles.back()->angle = m_particles[i]->angle;
				m_particles.back()->axis = m_particles[i]->axis;

				m_particles.back()->angle = m_particles[i]->angle - 30.0f;

				switch (m_particles[i]->axis)
				{
				case Axis::X:
					m_particles.back()->direction = glm::vec3(0.0f, cos_radians(m_particles.back()->angle), sin_radians(m_particles.back()->angle));
					break;

				case Axis::Y:
					m_particles.back()->direction = glm::vec3(cos_radians(m_particles.back()->angle), 0.0f, sin_radians(m_particles.back()->angle));
					break;

				case Axis::Z:
					m_particles.back()->direction = glm::vec3(cos_radians(m_particles.back()->angle), sin_radians(m_particles.back()->angle), 0.0f);
					break;
				default:
					cerr << "Not a valid Axis given!" << endl;
					assert(0);
					break;

				}


				m_particles.push_back(std::make_shared<Particle>());

				m_particles.back()->color = m_particles[i]->color;
				m_particles.back()->speed = m_particles[i]->speed;
				m_particles.back()->scale = glm::vec3(0.1f);
				m_particles.back()->position = m_particles[i]->position;

				m_particles.back()->axis = m_particles[i]->axis;
				m_particles.back()->angle = m_particles[i]->angle + 30.0f;

				switch (m_particles[i]->axis)
				{
				case Axis::X:
					m_particles.back()->direction = glm::vec3(0.0f, cos_radians(m_particles.back()->angle), sin_radians(m_particles.back()->angle));
					break;

				case Axis::Y:
					m_particles.back()->direction = glm::vec3(cos_radians(m_particles.back()->angle), 0.0f, sin_radians(m_particles.back()->angle));
					break;

				case Axis::Z:
					m_particles.back()->direction = glm::vec3(cos_radians(m_particles.back()->angle), sin_radians(m_particles.back()->angle), 0.0f);
					break;
				default:
					cerr << "Not a valid Axis given!" << endl;
					assert(0);
					break;

				}

				m_particles.erase(m_particles.begin() + i);
				m_particles.shrink_to_fit();
			}
		}
		else
		{
			if (m_particles[i]->timeNow >= 2.0f)
			{
				m_particles[i]->alpha -= 3.0f * DeltaTime;	// .33 seconds 
				if (m_particles[i]->alpha <= -3.0f)
				{
					m_particles[i]->IsAlive = false;
				}
			}
		}

		m_particles[i]->Draw();
	}
	for (auto it : m_particles)
	{
		if (!it->IsAlive)
			this->Clean();
	}
}


void ParticleSystem3D::Clean()
{
	m_particles.clear();
	//for (int i = 0; i < m_particles.size(); i++)
	//{
	//	m_particles.erase(m_particles.begin() + i);
	//}
	//m_particles.shrink_to_fit();
}


void Particle::Draw()
{

	TheShaderManager::Instance()->SetFragmentColourOnly(TheApp::Instance()->getCoreProgram());
	TheShaderManager::Instance()->SetUniform3f(TheApp::Instance()->getCoreProgram(), "col", color);
	TheShaderManager::Instance()->SetUniformf(TheApp::Instance()->getCoreProgram(), "alpha", alpha);

	Util::Transform(TheApp::Instance()->getCoreProgram(), position, scale, glm::vec3(1.0f, 0.0f, 0.0f), 0.0f);

	TheApp::Instance()->m_playerScene->geoGen.mGeometryMesh[m_meshType]->bindVertexArrayObject();
	GLuint indexCount = TheApp::Instance()->m_playerScene->geoGen.mGeometryMesh[m_meshType]->getNumIndicies();

	glDrawElements(TheApp::Instance()->m_playerScene->geoGen.mGeometryMesh[m_meshType]->getPrimitiveType(), indexCount, GL_UNSIGNED_INT, 0);
}
