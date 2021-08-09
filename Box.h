#pragma once
class Box
{
public:
	Box();
	Box(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

	//get set
	void Set(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	void SetMinX(float minX);
	void SetMaxX(float minX);
	void SetMinY(float minY);
	void SeMaxY(float minY);
	void SetMinZ(float minZ);
	void SetMaxZ(float minZ);

	float GetMinX();
	float GetMaxX();
	float GetMinY();
	float GetMaxY();
	float GetMinZ();
	float GetMaxZ();

private:
	//Dimensions
	float minX = -1;
	float maxX = 1;

	float minY = -1;
	float maxY = 1;

	float minZ = -1;
	float maxZ = 1;
};
