#include "ParticleModel.h"


//Get Set
void ParticleModel::SetBSphereRadius(float radius)
{
	_boundingSphereRadius = radius;
}

void ParticleModel::SetBBox(float bMinX, float bMaxX, float bMinY, float bMaxY, float bMinZ, float bMaxZ)
{
	_bBox.Set(bMinX, bMaxX, bMinY, bMaxY, bMinZ, bMaxZ);
}

float ParticleModel::GetBSphereRadius()
{
	return _boundingSphereRadius;
}

Box& ParticleModel::GetBBox()
{
	return _bBox;
}


void ParticleModel::UseBBox(float bMinX, float bMaxX, float bMinY, float bMaxY, float bMinZ, float bMaxZ)
{
	_bBox.Set(bMinX, bMaxX, bMinY, bMaxY, bMinZ, bMaxZ);
	
	_useBBox = true;
	_useBSphere = false;
}
void ParticleModel::UseBBox()
{
	_useBBox = true;
	_useBSphere = false;
}

void ParticleModel::UseBSphere(float radius)
{
	_boundingSphereRadius = radius;
	_useBSphere = true;
	_useBBox = false;
}

void ParticleModel::UseBSphere()
{
	_useBSphere = true;
	_useBBox = false;
}


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

bool ParticleModel::CollisionCheckSpheres(Vector3 sphere1Position, float sphere1Radius, Vector3 sphere2Position, float sphere2Radius)
{
	Vector3 diff = sphere2Position - sphere1Position;
	float distance = sqrtf((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z));
	if (distance <= sphere1Radius + sphere2Radius)
	{
		return true;
	}

	return false;
}

bool ParticleModel::CollisionCheckBoxes(Vector3 box1Position, Box box1, Vector3 box2Position, Box box2)
{
	Vector3 box2vertexes[8] = {
		//vertices clockwise, top to bottom
		//away from camera 
		Vector3(box2Position.x + box2.GetMinX(), box2Position.y + box2.GetMaxY(), box2Position.z + box2.GetMaxZ()),
		Vector3(box2Position.x + box2.GetMaxX(), box2Position.y + box2.GetMaxY(), box2Position.z + box2.GetMaxZ()),

		Vector3(box2Position.x + box2.GetMinX(), box2Position.y + box2.GetMinY(), box2Position.z + box2.GetMaxZ()),
		Vector3(box2Position.x + box2.GetMaxX(), box2Position.y + box2.GetMinY(), box2Position.z + box2.GetMaxZ()),


		//toward camera
		Vector3(box2Position.x + box2.GetMinX(), box2Position.y + box2.GetMaxY(), box2Position.z + box2.GetMinZ()),
		Vector3(box2Position.x + box2.GetMaxX(), box2Position.y + box2.GetMaxY(), box2Position.z + box2.GetMinZ()),

		Vector3(box2Position.x + box2.GetMinX(), box2Position.y + box2.GetMinY(), box2Position.z + box2.GetMinZ()),
		Vector3(box2Position.x + box2.GetMaxX(), box2Position.y + box2.GetMinY(), box2Position.z + box2.GetMinZ())
	};

	Vector3 closestPoint = Vector3(ClosestNumInNumRange(box2Position.x + box2.GetMinX(), box2Position.x + box2.GetMaxX(), box1Position.x),
		ClosestNumInNumRange(box2Position.y + box2.GetMinX(), box2Position.y + box2.GetMaxX(), box1Position.y),
		ClosestNumInNumRange(box2Position.z + box2.GetMinX(), box2Position.z + box2.GetMaxX(), box1Position.z));

	//check if any corners are in the box
	for (Vector3 vertex : box2vertexes)
	{
		if (vertex.x >= box1Position.x + box1.GetMinX() && vertex.x <= box1Position.x + box1.GetMaxX() &&
			vertex.y >= box1Position.y + box1.GetMinY() && vertex.y <= box1Position.y + box1.GetMaxY() &&
			vertex.z >= box1Position.z + box1.GetMinZ() && vertex.z <= box1Position.z +  box1.GetMaxZ())
		{
			return true;
		}
	}
	if ((closestPoint.x >= box1Position.x + box1.GetMinX() && closestPoint.x <= box1Position.x + box1.GetMaxX() &&
		closestPoint.y >= box1Position.y + box1.GetMinY() && closestPoint.y <= box1Position.y + box1.GetMaxY() &&
		closestPoint.z >= box1Position.z + box1.GetMinZ() && closestPoint.z <= box1Position.z + box1.GetMaxZ()))
	{
		return true;
	}

	return false;
}

bool ParticleModel::CollisionCheckSphereAndBox(Vector3 spherePosition, float sphereRadius, Vector3 boxPosition, Box box)
{
	Vector3 closestPoint = Vector3(ClosestNumInNumRange(boxPosition.x + box.GetMinX(), boxPosition.x + box.GetMaxX(), spherePosition.x),
									ClosestNumInNumRange(boxPosition.y + box.GetMinX(), boxPosition.y + box.GetMaxX(), spherePosition.y),
									ClosestNumInNumRange(boxPosition.z + box.GetMinX(), boxPosition.z + box.GetMaxX(), spherePosition.z));

	Vector3 diff = boxPosition - spherePosition;
	float distance = sqrtf((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z));
	if (distance <= sphereRadius)
	{
		return true;
	}

	return false;
}

bool ParticleModel::CollisionCheck(Vector3 position, float radius)
{
	if (_useBSphere)
	{
		return CollisionCheckSpheres(_transform->GetPosition(), _boundingSphereRadius, position, radius);
	}
	else if (_useBBox)
	{
		return CollisionCheckSphereAndBox(position, radius, _transform->GetPosition(), _bBox);
	}

	return false;
}
bool ParticleModel::CollisionCheck(Vector3 position, Box box)
{
	if (_useBSphere)
	{
		return CollisionCheckSphereAndBox(_transform->GetPosition(), _boundingSphereRadius, position, box);
	}
	else if (_useBBox)
	{
		return CollisionCheckBoxes(_transform->GetPosition(), _bBox, position, box);
	}

	return false;
}

float ParticleModel::ClosestNumInNumRange(float rangeMin, float rangeMax, float targetNum)
{
	//bigger than numbers in the range then the smallest number is closest, and vice versa
	if (targetNum >= rangeMax)
	{
		return rangeMax;
	}
	else if (targetNum <= rangeMin)
	{
		return rangeMin;
	}
	//if not then the targetNum if within range
	else
	{
		return targetNum;
	}
}

void ParticleModel::DragForce(Vector3 velocity, float dragFactor)
{
	if (_useLaminar)
	{
		// calculate drag force for laminar flow
		DragLamFlow(velocity, dragFactor);
	}

	else
	{
		// calculate drag force for turbulent flow
		DragTurbFlow(velocity, dragFactor);
	}
}
void ParticleModel::DragLamFlow(Vector3 velocity, float dragFactor)
{
	_drag = velocity * -dragFactor;
}
void ParticleModel::DragTurbFlow(Vector3 velocity, float dragFactor)
{
	// calculate magnitude of velocity
	float velMag = velocity.Magnitude();
	// calculate unit vector of velocity
	Vector3 unitVel = velocity.Normalise();

	// calculate magnitude of drag force
	float dragMag = dragFactor * velMag * velMag;

	// calculate of x- and y-components of drag force
	_drag = unitVel * -dragMag;
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
void ParticleModel::SetIsStatic(bool isStatic)
{
	_isStatic = isStatic;
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
	return _useConstAccel;
}

bool ParticleModel::GetIsStatic()
{
	return _isStatic;
}

void ParticleModel::SetUsingConstAccel(bool usingConstAccel)
{
	_useConstAccel = usingConstAccel;
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
	//_drag = _velocity * _dragFactor * -1;
	
	DragForce(_velocity, _dragFactor);
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


	//debug.OutputLog("Magnitude: " + to_string(_transform->GetPosition().Magnitude()));
	//debug.OutputLog("_netForce X: " + to_string(_netForce.x) + " Y: " + to_string(_netForce.y) + " Z: " + to_string(_netForce.z));
	//debug.OutputLog("position X: " + to_string(_transform->GetPosition().x) + " Y: " + to_string(_transform->GetPosition().y) + " Z: " + to_string(_transform->GetPosition().z));
	//debug.OutputLog("acceleration X: " + to_string(_acceleration.x) + " Y: " + to_string(_acceleration.y) + " Z: " + to_string(_acceleration.z));
	//debug.OutputLog("velocity X: " + to_string(_velocity.x) + " Y: " + to_string(_velocity.y) + " Z: " + to_string(_velocity.z));
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
	if (!_isStatic)
	{
		UpdateNetForce();
		UpdateAccel();
		if (_useConstAccel == false)
		{
			moveConstVelocity(t);
		}
		else if (_useConstAccel)
		{
			moveConstAcceleration(t);
		}
		//floor logic
		if (/*_transform->GetPosition().x < 20 && _transform->GetPosition().x > -20  && _transform->GetPosition().z < -20
			&& _transform->GetPosition().z > -20 &&*/ _transform->GetPosition().y <0)
		{
			Vector3 position = _transform->GetPosition();
			position.y = 0;
			_velocity.y = 0;
			_transform->SetPosition(position);
		}
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