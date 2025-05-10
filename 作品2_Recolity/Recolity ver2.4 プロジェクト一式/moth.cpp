//=============================================================================
//
// �G���� [moth.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "moth.h"
#include "moth_wing.h"
#include "material.h"
#include "sprite.h"
#include "sound.h"
#include "floor.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_POINT	(100)							// �q�b�g�|�C���g
#define COLL_CIRCLE	(100.0f)						// �����蔻��̔��a

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Moth::Moth(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, moth_enemy)
{
	//���̃C���X�^���X��
	m_Wing[w_left] = new Moth_Wing({ RefPos().x, RefPos().y ,RefPos().z },
		RefRot(), RefScl(), RefVel(), RefColor(),
		true, w_left, 0.0f);
	m_Wing[w_right] = new Moth_Wing({ RefPos().x, RefPos().y ,RefPos().z },
		RefRot(), RefScl(), RefVel(), RefColor(),
		true, w_right, 0.0f);

	//�����蔻��̐ݒ�
	SetColl(new Collision(this, {}, 100));

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor();	//���F
	GetMaterial()->Emission = RefColor();	//���Ȕ����F
	GetMaterial()->noTexSampling = 0;

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Moth::~Moth()
{
	Uninit();
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Moth::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Moth::Uninit(void)
{
	//StopSound(m_SoundIndex);

	//���̉��
	for (int i = 0; i < MOTH_WING_NUM; i++)
	{
		delete m_Wing[i];
		m_Wing[i] = nullptr;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void Moth::Update(void)
{
	//�A�N�V����
	Action();
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamage(1);
	}
	//�����蔻��̍Đݒ�
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Moth::Draw(void)
{
	// ���̃��f���̕`��
	Draw3DModel(*this, RefModelMaterial().m_Moth);

	// �����f���̕`��
	for (int i = 0; i < MOTH_WING_NUM; i++)
	{
		m_Wing[i]->Draw();
	}

#if _DEBUG
	//�����蔻��̕`��
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
		sphere.m_Rot = RefRot();
		Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	//HP�̕\��
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y + 0.3f * RefScl().y * DISTANCE_DIFF,RefPos().z };
	hp.m_Scl = { 1.0f * RefHp(),10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBill(hp, RefImageMaterial().m_White_Square);
#endif // _DEBUG
}
//=============================================================================
// �A�N�V����
//=============================================================================
void Moth::Action(void)
{
	CAMERA* pCam = GetCamera();

	////�J����(�v���C���[)�̂�������փG�l�~�[���������鏈��
	//D3DXVECTOR3 vec = D3DXVECTOR3(pCam->pos.x - RefPos().x, pCam->pos.y - RefPos().y, pCam->pos.z - RefPos().z);
	//float rot = -atan2f(vec.z, vec.x) + D3DX_PI / 2;
	//SetRot(D3DXVECTOR3(MOTH_ANGLE, rot, 0.0f));
	////�ǐ�
	//Chase(pCam->pos);
	//SetPos({ RefPos().x,RefPos().y + 100.0f,RefPos().z });

	//���̍X�V
	for (int i = 0; i < MOTH_WING_NUM; i++)
	{
		m_Wing[i]->SetPos({ RefPos().x,RefPos().y,RefPos().z });
		m_Wing[i]->SetRot({ { RefRot().x,m_Wing[i]->RefRot().y,RefRot().z } });
		m_Wing[i]->Update();
	}
}
