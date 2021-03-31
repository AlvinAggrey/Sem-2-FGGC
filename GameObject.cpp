#include "GameObject.h"

#include <iostream>


enum GameObjectType
{
	PLANE,
	DONUT,
	CUBE
};

GameObject::GameObject(string type, Geometry geometry, Material material) : _geometry(geometry), _type(type), _material(material)
{
	_parent = nullptr;
	_position = Vector3();
	_rotation = Vector3();
	_scale = Vector3(1.0f, 1.0f, 1.0f);
	_gObjectType = type;
	
	_textureRV = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);
	if (GetGameObjectType() == "Cube")
	{
		//char message = (t);
		debug.OutputLog(std::to_string(t));
			
	}
	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}

//Vector Computations
float Vector3::Normalize() 
{
	return 1.0f;
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
	return Vector3( (y*vector.z - vector.y * z), (z * vector.x - vector.z * x), (x * vector.y - vector.x * y));
}

//Vector operators
void Vector3::operator*=(float scalar)
{
	this->x* scalar;
	this->y* scalar;
	this->z* scalar;
}
void Vector3::operator+=(Vector3 vector)
{
	this->x + vector.x;
	this->y + vector.y;
	this->z + vector.z;
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