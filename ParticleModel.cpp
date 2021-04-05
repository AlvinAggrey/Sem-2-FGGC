#include "ParticleModel.h"

//get set
Vector3 ParticleModel::GetVelocity()
{
	return _velocity;
}

void ParticleModel::SetVelocity(Vector3 velocity)
{
	_velocity = velocity;
}
void ParticleModel::SetVelocity(float x, float y, float z)
{
	_velocity.x = x;
	_velocity.y = y;
	_velocity.z = z;
}

Vector3 ParticleModel::GetAccelaration()
{
	return _velocity;
}

void ParticleModel::SetAccelaration(Vector3 accelaration)
{
	_accelaration = accelaration;
}
void ParticleModel::SetAccelaration(float x, float y, float z)
{
	_accelaration.x = x;
	_accelaration.y = y;
	_accelaration.z = z;
}

void ParticleModel::Update(float t)
{
	moveConstVelocity(t);
}

void ParticleModel::moveConstVelocity(const float deltaTime)
{
	Vector3 position = _transform->GetPosition() + _velocity * deltaTime;
	_transform->SetPosition(position);
}

void ParticleModel::moveConstAcceleration(const float deltaTime)
{
	//changed code slightly because it made more sense to do it like this
	Vector3 position = _transform->GetPosition() + (_velocity * deltaTime);

	_transform->SetPosition(position);
	_velocity = _velocity + (_accelaration * deltaTime);
}
