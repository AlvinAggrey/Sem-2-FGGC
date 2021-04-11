#pragma once
#include "Vector3.h"
#include "Transform.h"
#include "Debug.h"

class ParticleModel
{
private:
	Transform* _transform;
	Vector3 _velocity;
	Vector3 _acceleration;
	Vector3 _netForce;

	//forces
	Vector3 _thrust;
	float _friction;
	Vector3 _drag;
	Vector3 _brakeForces;
	Vector3 _weight;
	Vector3 _upForce;
	float _gravity = 9.807;

	float _airFriction = 0.5;

	bool _usingConstAccel;
	bool _useThrust;
	float _mass;
	Debug debug;

public:

	ParticleModel(Transform* transform, float mass, bool useConstAccel, Vector3 initVelocity, Vector3 initAcceleration) 
	{
		_transform = transform;
		_usingConstAccel = useConstAccel;
		_velocity = initVelocity;
		_acceleration = initAcceleration;
		_mass = mass;
		_weight = Vector3(0, _mass * _gravity, 0);
		_upForce = _weight;
	};

	//Mass
	float GetMass();
	void SetMass(float mass);

	//Thrust
	Vector3 GetThrust();

	//void useThrust(bool useThrust);

	void SetThrust(Vector3 thrust);
	void SetThrust(float x, float y, float z);

	//Friction
	float GetFriction();
	void SetFriction();
	
	//Drag
	Vector3 GetDrag();
	void SetDrag();

	//Brake forces
	Vector3 GetBrakeForces();
	void SetBrakeForces(Vector3 brakeForces);
	void SetBrakeForces(float x, float y, float z);

	//Velocity
	Vector3 GetVelocity();
	void SetVelocity(Vector3 velocity);
	void SetVelocity(float x, float y, float z);

	//Acceleration
	bool GetUsingConstAccel();
	void SetUsingConstAccel(bool usingConstAccel);

	Vector3 GetAcceleration();
	void SetAcceleration(Vector3 accelaration);
	void SetAcceleration(float x, float y, float z);


	//calculate external forces
	void UpdateNetForce();
	void UpdateAccel();

	void Update(float t);
	void moveConstVelocity(const float deltaTime);
	void moveConstAcceleration(const float deltaTime);
};

