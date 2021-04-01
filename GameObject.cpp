#include "GameObject.h"

#include <iostream>

GameObject::GameObject(string type, Geometry geometry, Material material) : _geometry(geometry), _type(type), _material(material)
{
	_parent = nullptr;
	//_position = Vector3();
	//_rotation = Vector3();
	//_scale = Vector3(1.0f, 1.0f, 1.0f);

	GetTransform()->SetPosition(Vector3());
	GetTransform()->SetRotation(Vector3());
	GetTransform()->SetScale(1.0f, 1.0f, 1.0f);

	_gObjectType = type;
	
	_textureRV = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	Vector3 mScale = GetTransform()->GetScale();
	Vector3 mRotation = GetTransform()->GetRotation();
	Vector3 mPosition = GetTransform()->GetPosition();
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(/*_scale.x, _scale.y, _scale.z*/mScale.x, mScale.y, mScale.z);
	XMMATRIX rotation = XMMatrixRotationX(/*_rotation.x*/ mRotation.x) * XMMatrixRotationY(/*_rotation.y*/mRotation.y) * XMMatrixRotationZ(/*_rotation.z*/mRotation.z);
	XMMATRIX translation = XMMatrixTranslation(/*_position.x, _position.y, _position.z*/mPosition.x, mPosition.y, mPosition.z);

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