#pragma once
class Appearance
{
public:
	Appearance(){}

	Geometry GetGeometryData() const { return _geometry; }
	void SetGeometryData(Geometry geometry) { _geometry = geometry; }
	Material GetMaterial() const { return _material; }
	void SetMaterial(Material material) { _material = material; }


	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

private:
	Geometry _geometry;
	Material _material;
	ID3D11ShaderResourceView* _textureRV = nullptr;
};