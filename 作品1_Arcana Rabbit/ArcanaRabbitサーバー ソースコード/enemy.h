#pragma once
#include "Component.h"
#include "gameObject.h"
class Player;
class Floor;
class Enemy :public GameObject
{
private:
	//int m_AnimationFrame;
	Component* m_Component{};
	Component* m_Componenthitbox{};
	Component* m_audio;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	Player* m_pPlayer;//プレイヤーを追いかけるのに使う
	Floor* m_floor;//床
	XMFLOAT3 m_oldpos;//1フレーム前の床
	XMFLOAT4 m_quat = {0.0f,0.0f ,0.0f ,1.0f };
	int m_hit = 0;//当たった時赤くするのに使う
	bool swap;//くねくねさせるのに使う
	float hitbox;//当たり判定の大きさ
	float animatelot;//くねくねの角度

	int attackct = 0;
	int m_AnimationFrame;
	float hp;//現在体力
	float maxhp;//最大体力

	float m_hitbox = 0.5f;//ヒットボックスの大きさ
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void AddDamage(float damage);
	float GetHitboxrange() { return m_hitbox; };
};

