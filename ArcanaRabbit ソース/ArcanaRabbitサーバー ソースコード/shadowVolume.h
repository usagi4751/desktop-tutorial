#pragma once
#include "gameObject.h"
#include "Component.h"
class ShadowVolume : public GameObject
{
private:

	Component* m_Component{};

	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};