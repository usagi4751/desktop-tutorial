#pragma once
#include "gameObject.h"
class Floor;
class Player;
class Field : public GameObject
{
private:
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture = nullptr;
	Floor* m_floor;//デバック用
	Player* m_player;//デバック用
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	bool on = false;//生成時にプレイヤーとかを取得する時につかてる
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};