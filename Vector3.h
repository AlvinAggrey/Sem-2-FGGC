#pragma once
#include <corecrt_math.h>

class Vector3
{
private:


public:
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3() { x = 0; y = 0; z = 0; }
	Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	//Copy constructor
	Vector3(const Vector3& vector) { x = vector.x; y = vector.y; z = vector.z; }

	//computations
	Vector3 Normalise();
	float Magnitude();
	Vector3 DotProduct(Vector3 vector);
	Vector3 CrossProduct(Vector3 vector);
	void Clamp(float maxNumber);

	//operator overloads
	Vector3 operator*= (float);

	Vector3 operator*=(Vector3 vector);

	Vector3 operator+= (Vector3);
	Vector3 operator+ (Vector3);
	Vector3 operator- (Vector3);
	Vector3 operator-();
	Vector3 operator* (float);
	Vector3 operator* (Vector3);
};