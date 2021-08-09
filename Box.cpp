#include "Box.h"

Box::Box()
{
}

Box::Box(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	this->minX = minX;
	this->maxX = maxX;

	this->minY = minY;
	this->maxY = maxY;

	this->minZ = minZ;
	this->maxZ = maxZ;
}

void Box::Set(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	this->minX = minX;
	this->maxX = maxX;

	this->minY = minY;
	this->maxY = maxY;

	this->minZ = minZ;
	this->maxZ = maxZ;
}

void Box::SetMinX(float minX)
{
	this->minX = minX;
}

void Box::SetMaxX(float minX)
{
	this->maxX = maxX;
}

void Box::SetMinY(float minY)
{
	this->minY = minY;
}

void Box::SeMaxY(float minY)
{
	this->maxY = maxY;
}

void Box::SetMinZ(float minZ)
{
	this->minZ = minZ;
}

void Box::SetMaxZ(float minZ)
{
	this->maxZ = maxZ;
}

float Box::GetMinX()
{
	return minX;
}

float Box::GetMaxX()
{
	return maxX;
}

float Box::GetMinY()
{
	return minY;
}

float Box::GetMaxY()
{
	return maxY;
}

float Box::GetMinZ()
{
	return minZ;
}

float Box::GetMaxZ()
{
	return maxZ;
}

