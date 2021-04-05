#pragma once
#include "Vector3.h"
#include "Transform.h"

class ParticleModel
{
private:
	Transform* _transform;
	Vector3 _velocity;
	Vector3 _accelaration;
public:
	ParticleModel(Transform * transform) { _transform = transform;};

	Vector3 GetVelocity();
	void SetVelocity(Vector3 velocity);
	void SetVelocity(float x, float y, float z);

	Vector3 GetAccelaration();

	void SetAccelaration(Vector3 accelaration);

	void SetAccelaration(float x, float y, float z);

	void Update(float t);
	void moveConstVelocity(const float deltaTime);
	void moveConstAcceleration(const float deltaTime);
};

