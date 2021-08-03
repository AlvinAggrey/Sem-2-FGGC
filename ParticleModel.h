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

	//Collision Detection
	float _boundingSphereRadius = 1;

	//forces
	Vector3 _thrust;
	float _friction;
	float _dragFactor = 0.5;
	Vector3 _drag;
	Vector3 _brakeForces;
	Vector3 _weight;
	Vector3 _upForce;
	float _gravity = 9.807;

	float _airFriction = 0.5;

	bool _useConstAccel;
	bool _useLaminar;
	bool _useThrust;
	float _mass;
	Debug debug;

public:

	ParticleModel(Transform* transform, float mass, bool useConstAccel, Vector3 initVelocity, Vector3 initAcceleration) 
	{
		_transform = transform;
		_useConstAccel = useConstAccel;
		_velocity = initVelocity;
		_acceleration = initAcceleration;
		_mass = mass;
		_weight = Vector3(0, _mass * _gravity, 0);
		_upForce = _weight;
	};
	//Collision Detection
	void SetBoundingSphereRadius(float radius);
	void SetBoundingBox();

	float GetBoundingSphereRadius();
	void GetBoundingBox();

	void UseBoundingBox();
	void UseBoundingSphere(float radius);

	bool CollisionCheck(Vector3 position, float radius);
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

	void DragForce(Vector3 velocity, float dragFactor);
	void DragLamFlow(Vector3 velocity, float dragFactor);
	void DragTurbFlow(Vector3 velocity, float dragFactor);

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
	void SetUsingConstAccel(bool useConstAccel);

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

