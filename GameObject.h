#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Debug.h"

using namespace DirectX;
using namespace std;

struct Geometry
{
	ID3D11Buffer * vertexBuffer;
	ID3D11Buffer * indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};

struct Vector3
{
private:
	float magnitude = 0;
public:
	float x;
	float y;
	float z;

	Vector3() = default;
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

class GameObject
{
public:
	GameObject(string type, Geometry geometry, Material material);
	~GameObject();

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

	string GetType() const { return _type; }
	string GetGameObjectType() { return _gObjectType; }

	Geometry GetGeometryData() const { return _geometry; }

	Material GetMaterial() const { return _material; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	void SetTextureRV(ID3D11ShaderResourceView * textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView * GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;

	string _type;
	string _gObjectType;

	XMFLOAT4X4 _world;

	Geometry _geometry;
	Material _material;

	Debug debug;

	ID3D11ShaderResourceView * _textureRV;

	GameObject * _parent;
};

