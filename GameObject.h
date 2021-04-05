#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Material.h"
#include "Geometry.h"


#include "Debug.h"
#include "Appearance.h"
#include "Transform.h"
#include "ParticleModel.h"

using namespace DirectX;
using namespace std;


class GameObject
{
public:
	GameObject(string type, Geometry geometry, Material material);
	~GameObject();

	string GetType() const { return _type; }
	string GetGameObjectType() { return _gObjectType; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	//get components
	Appearance* GetAppearance() const { return _appearance; };
	Transform* GetTransform () const { return _transform; };
	ParticleModel* GetParticleModel() const { return _particleModel; };

	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	Appearance * _appearance = new Appearance();
	Transform * _transform = new Transform();
	ParticleModel * _particleModel = new ParticleModel(_transform);

	string _type;
	string _gObjectType;

	XMFLOAT4X4 _world;

	Debug debug;

	GameObject * _parent;
};

