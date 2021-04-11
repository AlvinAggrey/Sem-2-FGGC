#include "GameObject.h"

#include <iostream>

GameObject::GameObject(string type, Geometry geometry, Material material) : _type(type)
{
	_parent = nullptr;

	_transform->SetPosition(Vector3());
	_transform->SetRotation(Vector3());
	_transform->SetScale(1.0f, 1.0f, 1.0f);

	_gObjectType = type;
	
	//_textureRV = nullptr;
	_appearance->SetGeometryData(geometry);
	_appearance->SetMaterial(material);

	size_t found = _gObjectType.find("Cube");
	//if (found != string::npos)
		//_particleModel->SetVelocity(0, 0, 0.1);
		//_particleModel->SetAccelaration(0, 0, 5);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	//_particleModel->Update(t);

	Vector3 mScale = GetTransform()->GetScale();
	Vector3 mRotation = GetTransform()->GetRotation();
	Vector3 mPosition = GetTransform()->GetPosition();
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(/*_scale.x, _scale.y, _scale.z*/mScale.x, mScale.y, mScale.z);
	XMMATRIX rotation = XMMatrixRotationX(/*_rotation.x*/ mRotation.x) * XMMatrixRotationY(/*_rotation.y*/mRotation.y) * XMMatrixRotationZ(/*_rotation.z*/mRotation.z);
	XMMATRIX translation = XMMatrixTranslation(/*_position.x, _position.y, _position.z*/mPosition.x, mPosition.y, mPosition.z);

	_particleModel->Update(t);
	XMStoreFloat4x4(&_world, scale * rotation * translation);
	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place
	Geometry mAppearance = GetAppearance()->GetGeometryData();
	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &mAppearance.vertexBuffer, &mAppearance.vertexBufferStride, &mAppearance.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(mAppearance.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(mAppearance.numberOfIndices, 0, 0);
}