#pragma once
#include "Vector3.h"
#include "Transform.h"

class ParticleModel
{
private:
	Transform* _transform;
	Vector3 _velocity;
	Vector3 _accelaration;
	bool _usingConstAccel;

public:

	ParticleModel(Transform* transform, bool useConstAccel, Vector3 initVelocity, Vector3 initAcceleration) 
	{
		_transform = transform; _usingConstAccel = useConstAccel; _velocity = initVelocity, _accelaration = initAcceleration;
	};

	Vector3 GetVelocity();
	void SetVelocity(Vector3 velocity);
	void SetVelocity(float x, float y, float z);

	bool GetUsingConstAccel();
	void SetUsingConstAccel(bool usingConstAccel);

	Vector3 GetAccelaration();
	void SetAccelaration(Vector3 accelaration);
	void SetAccelaration(float x, float y, float z);

	void Update(float t);
	void moveConstVelocity(const float deltaTime);
	void moveConstAcceleration(const float deltaTime);
};

