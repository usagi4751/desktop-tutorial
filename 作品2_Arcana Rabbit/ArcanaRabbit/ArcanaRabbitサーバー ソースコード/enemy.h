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
	Player* m_pPlayer;//�v���C���[��ǂ�������̂Ɏg��
	Floor* m_floor;//��
	XMFLOAT3 m_oldpos;//1�t���[���O�̏�
	XMFLOAT4 m_quat = {0.0f,0.0f ,0.0f ,1.0f };
	int m_hit = 0;//�����������Ԃ�����̂Ɏg��
	bool swap;//���˂��˂�����̂Ɏg��
	float hitbox;//�����蔻��̑傫��
	float animatelot;//���˂��˂̊p�x

	int attackct = 0;
	int m_AnimationFrame;
	float hp;//���ݑ̗�
	float maxhp;//�ő�̗�

	float m_hitbox = 0.5f;//�q�b�g�{�b�N�X�̑傫��
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void AddDamage(float damage);
	float GetHitboxrange() { return m_hitbox; };
};

