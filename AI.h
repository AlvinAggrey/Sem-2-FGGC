#pragma once
#include "Transform.h"
#include "Vector3.h"
#include "GameObject.h"

class AI
{
private:
	Transform* transform;
	ParticleModel* particleModel;
	float maxVelocity = 1;

public:
	AI();
	
	void Seek(Vector3 targetPosition);
	void Flee(Vector3 avoidPosition);
	void Arrival(Vector3 targetPosition);
	void Wander();
	
	void ResetThrust();

	//get set
	void SetParticleModel(ParticleModel* particleModel);
	void SetTransform(Transform* transform);
};

