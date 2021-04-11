#include "ParticleModel.h"



//get set
float ParticleModel::GetMass()
{
	return _mass;
}

void ParticleModel::SetMass(float mass)
{
	_mass = mass;
}
Vector3 ParticleModel::GetThrust()
{
	return _thrust;
}
//void ParticleModel::useThrust(bool useThrust)
//{
//	_useThrust = useThrust;
//}

void ParticleModel::SetThrust(Vector3 thrust)
{
	_thrust = thrust;
	_useThrust = true;
}
void ParticleModel::SetThrust(float x, float y, float z)
{
	_thrust = Vector3(x, y, z);
	_useThrust = true;
}
Vector3 ParticleModel::GetBrakeForces()
{
	return _brakeForces;
}
void ParticleModel::SetBrakeForces(Vector3 brakeForces)
{
	_brakeForces = brakeForces;
}
void ParticleModel::SetBrakeForces(float x, float y, float z)
{
	_brakeForces.x = x;
	_brakeForces.y = y;
	_brakeForces.z = z;
}
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

bool ParticleModel::GetUsingConstAccel()
{
	return _usingConstAccel;
}

void ParticleModel::SetUsingConstAccel(bool usingConstAccel)
{
	_usingConstAccel = usingConstAccel;
}

Vector3 ParticleModel::GetAcceleration()
{
	return _velocity;
}

void ParticleModel::SetAcceleration(Vector3 accelaration)
{
	_acceleration = accelaration;
}
void ParticleModel::SetAcceleration(float x, float y, float z)
{
	_acceleration.x = x;
	_acceleration.y = y;
	_acceleration.z = z;
}

void ParticleModel::UpdateNetForce()
{
	_netForce = Vector3(0,0,0);
	_drag = _velocity * 0.5 * -1;
	
	//apply thrust this frame?
	if (_useThrust)
	{
		_netForce += _thrust;
		_useThrust = false;
	}
	else if (!_useThrust)
	{
		_thrust = Vector3();
	}

	_netForce += _drag -_weight;


	debug.OutputLog("_netForce X: " + to_string(_netForce.x) + " Y: " + to_string(_netForce.y) + " Z: " + to_string(_netForce.z));
	debug.OutputLog("position X: " + to_string(_transform->GetPosition().x) + " Y: " + to_string(_transform->GetPosition().y) + " Z: " + to_string(_transform->GetPosition().z));
	debug.OutputLog("acceleration X: " + to_string(_acceleration.x) + " Y: " + to_string(_acceleration.y) + " Z: " + to_string(_acceleration.z));
	debug.OutputLog("velocity X: " + to_string(_velocity.x) + " Y: " + to_string(_velocity.y) + " Z: " + to_string(_velocity.z));
}
void ParticleModel::UpdateAccel()
{
	_acceleration.x = _netForce.x / _mass;
	_acceleration.y = _netForce.y / _mass;
	_acceleration.z = _netForce.z / _mass;

	//debug.OutputLog("_acceleration Z: " + to_string(_acceleration.z));
}

void ParticleModel::Update(float t)
{
	UpdateNetForce();
	UpdateAccel();
	if (_usingConstAccel == false)
	{
		moveConstVelocity(t);
	}
	else if (_usingConstAccel)
	{
		moveConstAcceleration(t);
	}
	if (/*_transform->GetPosition().x < 20 && _transform->GetPosition().x > -20  && _transform->GetPosition().z < -20
		&& _transform->GetPosition().z > -20 &&*/ _transform->GetPosition().y < 0)
	{
		Vector3 position = _transform->GetPosition();
		position.y = 0;
		_velocity.y = 0;
		_transform->SetPosition(position);
	}
}

void ParticleModel::moveConstVelocity(const float deltaTime)
{
	//Vector3 position = _transform->GetPosition() + _velocity * deltaTime;
	_transform->SetPosition(_transform->GetPosition() + (_velocity * deltaTime));
}

void ParticleModel::moveConstAcceleration(const float deltaTime)
{
	//changed code slightly because it made more sense to do it like this
	//Vector3 position = _transform->GetPosition() + (_velocity * deltaTime);

	_transform->SetPosition(_transform->GetPosition() + (_velocity * deltaTime));
	_velocity = _velocity + (_acceleration * deltaTime);
	//debug.OutputLog("_Velocity Z: " + to_string(_velocity.z));
}
