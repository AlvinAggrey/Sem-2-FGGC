#include "AI.h"

AI::AI()
{
}

void AI::Seek(Vector3 targetPosition)
{
	//Vector3 targetPosition = targetObject.GetTransform()->GetPosition();
	Vector3 currentPosition = transform->GetPosition();

	Vector3 desiredVelocity = (targetPosition- currentPosition).Normalise() * maxVelocity;
	Vector3 steering = desiredVelocity- particleModel->GetVelocity();

	particleModel->SetVelocity(particleModel->GetVelocity() + steering);
	//particleModel->SetThrust(particleModel->GetThrust() + steering);
}

void AI::Flee(Vector3 avoidPosition)
{
	Vector3 currentPosition = transform->GetPosition();

	Vector3 desiredVelocity = -((avoidPosition - currentPosition).Normalise() * maxVelocity);
	Vector3 steering = desiredVelocity - particleModel->GetVelocity();

	particleModel->SetThrust(particleModel->GetThrust() + steering);
}
void AI::Arrival(Vector3 targetPosition)
{
	float slowingRadius = 3;

	//Vector3 targetPosition = targetObject.GetTransform()->GetPosition();
	Vector3 currentPosition = transform->GetPosition();
	float distance = (targetPosition - currentPosition).Magnitude();

	Vector3 desiredVelocity;

	if (distance < slowingRadius)
	{
		desiredVelocity = (targetPosition - currentPosition).Normalise() * maxVelocity * (distance/slowingRadius);
	}
	else
	{
		desiredVelocity = (targetPosition - currentPosition).Normalise() * maxVelocity;
	}

	Vector3 steering = desiredVelocity - particleModel->GetVelocity();

	particleModel->SetThrust(particleModel->GetThrust() + steering);
}

void AI::ResetThrust()
{
	particleModel->SetThrust(0,0,0);
}

void AI::SetParticleModel(ParticleModel* particleModel)
{
	this->particleModel = particleModel;
}

void AI::SetTransform(Transform* transform)
{
	this->transform = transform;
}

