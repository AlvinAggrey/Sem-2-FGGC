#pragma once
#include <directxmath.h>
#include <d3d11_1.h>

using namespace DirectX;
using namespace std;

struct Vector3
{
private:
	float magnitude = 0;


public:
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3() { x = 0; y = 0; z = 0; }
	Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	//Copy constructor
	Vector3(const Vector3& vector) { x = vector.x; y = vector.y; z = vector.z; }

	//computations
	float Normalize();
	float Magnitude();
	Vector3 DotProduct(Vector3 vector);
	Vector3 CrossProduct(Vector3 vector);

	//operator overloads
	void operator*= (float);
	void operator+= (Vector3);
	Vector3 operator+ (Vector3);
	Vector3 operator- (Vector3);
};

class Transform 
{
public:
	// Setters and Getters for position/rotation/scale
	void SetPosition(Vector3 position) { _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	Vector3 GetPosition() const { return _position; }

	void SetScale(Vector3 scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	Vector3 GetScale() const { return _scale; }

	void SetRotation(Vector3 rotation) { _rotation = rotation; }
	void SetRotation(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	Vector3 GetRotation() const { return _rotation; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

private:
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;
	XMFLOAT4X4 _world;
};