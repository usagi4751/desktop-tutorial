#pragma once
#include "Component.h"
#include "gameObject.h"
#include "draw2d_Manager.h"
#define DEFAULTHELTH (20)
#define DEFAULTDEF (0)
#define DEFAULTATTACKSPEED (100)
#define DEFAULTMOVESPEED (100)
#define DEFAULTDAMAGE (1)
class Floor;
class Enemy;
class Player :public GameObject
{
private:
	Component* m_Componentplayer{};
	Component* m_Component{};
	Component* m_audio;
	UI_Tex m_Reticl;//���e�B�N��

	Floor* m_floor;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	bool m_fly;//��s�ł��邩
	float m_NowHp;//���ݑ̗�
	float m_AttackCD;//�U���̃N�[���^�C��
	XMFLOAT3 m_oldpos;//1�t���[���O�̍��W
	XMFLOAT3 m_vel;//����
	int m_haveitem;//�����Ă�A�C�e���̃X���b�g
	float m_NomalAttackRange;//�ʏ�U���̎˒�

	//�t���O
	bool m_InventoryOpen;//�C���x���g�����J���Ă��邩
	bool clip = true;//�}�E�X�����߂�p
	bool m_IsGround;//�n�ʂɐڐG���Ă��邩

	//�f�o�b�N�p
	int size = 1;//���h��p

	//�ʏ함���@��
	void NomalOperation();
	//�n�ʂƂ̐ڐG����
	void IsGround();
	//�W�����v����
	void Jump();
	//�ړ�����
	void Move();
	//�J�����̍X�V����
	void CameraUpdate();
	//�v���C���[�̃A�N�V����
	void Action();
	//�X�e�[�^�X�̃A�b�v�f�[�g
	void StatusTimeUpdate();

	//===========================
	//�J���p�֐�
	//===========================
	//�J���p:�}�b�v�̃Z�[�u�ƃ��[�h
	void DevelopSaveAndLoad();
	//�J���p:���h��
	void DevelopNuru();
	//�J���p:��s
	void DevelopFreeFly();
	//�J���p:�f�o�b�N�R�}���h
	void DevelopDebugComand();
	//�J���p:�J���p��UI
	void DevelopDebugUI();
	//�J���p:��s�������@��
	void DevelopFlyOperation();
public:
	virtual void Init() ;
	virtual void Uninit() ;
	virtual void Update() ;
	virtual void Draw();



	XMFLOAT3 PlayerRay();//�v���C���[�̎���
	float GetNomalAttackRange() { return m_NomalAttackRange; };//�ʏ�U���̃����W
	XMFLOAT3 GetRot() { return m_Rotation; }//�v���C���[�̉�]���
	void AddDamage(float damage);//�v���C���[�Ƀ_���[�W��^���鎞�Ɏg��
	void Addheal(float heal);//�v���C���[�ɉ񕜂�^���鎞�Ɏg��


};

