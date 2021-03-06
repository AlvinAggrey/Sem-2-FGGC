#include "Vector3.h"

//Vector Computations
Vector3 Vector3::Normalise()
{
	float magnitude = Magnitude();
	return Vector3(x / magnitude , y / magnitude, z / magnitude);
}

float Vector3::Magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::DotProduct(Vector3 vector)
{
	return Vector3(this->x * vector.x, this->y * vector.y, this->z * vector.z);
}

Vector3 Vector3::CrossProduct(Vector3 vector)
{
	return Vector3((y * vector.z - vector.y * z), (z * vector.x - vector.z * x), (x * vector.y - vector.x * y));
}

void Vector3::Clamp(float maxNumber)
{
	if (x > maxNumber)
	{
		x = maxNumber;
	}
	if (y > maxNumber)
	{
		y = maxNumber;
	}
	if (z > maxNumber)
	{
		z = maxNumber;
	}
}

//Vector operators
Vector3 Vector3::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}
Vector3 Vector3::operator*=(Vector3 vector)
{
	this->x *= vector.x;
	this->y *= vector.y;
	this->z *= vector.z;
	return *this;
}
Vector3 Vector3::operator+=(Vector3 vector)
{
	this->x += vector.x;
	this->y += vector.y;
	this->z += vector.z;

	return *this;
}
Vector3 Vector3::operator+(Vector3 vector)
{
	Vector3 sum;
	sum = Vector3(this->x + vector.x, this->y + vector.y, this->z + vector.z);

	return sum;
}
Vector3 Vector3::operator-(Vector3 vector)
{
	Vector3 sum;
	sum = Vector3(this->x - vector.x, this->y - vector.y, this->z - vector.z);

	return sum;
}
Vector3 Vector3::operator-()
{
	//return opposite of vector
	Vector3 opposite;
	opposite = Vector3(-x, -y, -z);

	return	opposite;
}

Vector3 Vector3::operator*(float scalar)
{
	Vector3 product;
	product = Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
	
	return product;
}
Vector3 Vector3::operator*(Vector3 vector)
{
	Vector3 product;
	product = Vector3(this->x * product.x, this->y * product.y, this->z * product.z);
	
	return product;
}
