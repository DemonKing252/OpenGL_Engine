#pragma once
#include "vec3.hpp"
#include "vec2.hpp"
#include "gtc/matrix_transform.hpp"
#include "RenderItem.h"
#include "GeometryGenerator.h"
#include <vector>
#include <memory>


constexpr int MAX_PARTICLES = 500;
enum Axis { X, Y, Z };
struct Particle
{
	bool IsAlive = true;

	Axis axis;
	GeometryGenerator::Mesh m_meshType;

	float lifeSpawn = 8.0f;
	float timeNow = 0.0f;

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 color;
	glm::vec3 direction;
	float speed;
	float angle;
	float alpha = 1.0f;


	void Draw();

};
class ParticleSystem3D
{
private:
	
	std::vector<std::shared_ptr<Particle>> m_particles;
public:
	ParticleSystem3D();
	~ParticleSystem3D();

	void SpawnEmitter(glm::vec3 color, int count, float speed, glm::vec3 originPosition, Axis axis, GeometryGenerator::Mesh meshType);
	void UpdateParticles(float DeltaTime);
	void Clean();
};

