#pragma once
#include "Vector3.h"
#include "Transform.h"
#include "Debug.h"
#include "Box.h"

class ParticleModel
{
private:
	Transform* _transform;
	Vector3 _velocity;
	Vector3 _acceleration;
	Vector3 _netForce;

	//Collision Detection
	bool _useBBox, _useBSphere;
	float _boundingSphereRadius = 1;
	Box _bBox = Box();

	//forces
	bool _isStatic = false;
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
	float _mass = 1;
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

	//Set
	void SetBSphereRadius(float radius);
	void SetBBox(float bMinX, float bMaxX, float bMinY, float bMaxY, float bMinZ, float bMaxZ);
	void SetThrust(Vector3 thrust);
	void SetThrust(float x, float y, float z);
	void SetAcceleration(Vector3 accelaration);
	void SetAcceleration(float x, float y, float z);
	void SetMass(float mass);
	void SetFriction();
	void SetUsingConstAccel(bool useConstAccel);
	void SetVelocity(Vector3 velocity);
	void SetVelocity(float x, float y, float z);
	void SetBrakeForces(Vector3 brakeForces);
	void SetBrakeForces(float x, float y, float z);
	void SetDrag();
	void SetIsStatic(bool isStatic);

	//Get
	Box& GetBBox();

	float GetBSphereRadius();
	float GetMass();
	float GetFriction();

	Vector3 GetThrust();
	Vector3 GetDrag();
	Vector3 GetBrakeForces();
	Vector3 GetVelocity();
	Vector3 GetAcceleration();

	bool GetUsingConstAccel();
	bool GetIsStatic();

	//Collision Detection
	void UseBBox(float bMinX, float bMaxX, float bMinY, float bMaxY, float bMinZ, float bMaxZ);
	void UseBBox();

	void UseBSphere(float radius);
	void UseBSphere();

	bool CollisionCheckSpheres(Vector3 sphere1Position, float sphere1Radius, Vector3 sphere2Position, float sphere2Radius);
	bool CollisionCheckBoxes(Vector3 box1Position, Box box1, Vector3 box2Position, Box box2);
	bool CollisionCheckSphereAndBox(Vector3 spherePosition, float sphereRadius, Vector3 boxPosition, Box box);

	bool CollisionCheck(Vector3 position, float radius);
	bool CollisionCheck(Vector3 position, Box box);

	float ClosestNumInNumRange(float rangeMin, float rangeMax, float targetNum);
	
	//Physics
	//void useThrust(bool useThrust);
	void DragForce(Vector3 velocity, float dragFactor);
	void DragLamFlow(Vector3 velocity, float dragFactor);
	void DragTurbFlow(Vector3 velocity, float dragFactor);

	void UpdateNetForce();
	void UpdateAccel();

	void Update(float t);
	void moveConstVelocity(const float deltaTime);
	void moveConstAcceleration(const float deltaTime);
};
