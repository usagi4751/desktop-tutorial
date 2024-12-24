//=============================================================================
//
// �G���� [bullet_enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "patrol_enemy.h"
#include "base_attribute.h"
#include "material.h"
#include "sprite.h"
#include "sound.h"
#include "floor.h"
#include "camera.h"
#include "Game.h"
#include "DrawDamageDot.h"
#include "card.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_POINT	(100)								// �q�b�g�|�C���g
#define COLL_CIRCLE			(100.0f)					// �����蔻��̔��a
#define VALUE_MOVE			(5.0f)						// �ړ���
#define MOVE_FRAME			(60)						// �G�̈ړ��t���[��
#define PATTERN				(5)							// �G�̈ړ��p�^�[��
#define DROPCHANSE			(0.25f)						//�h���b�v��
#define DROPRANK2			(0.75f)						//�����N�Q��

#define HEARING_DISTANCE (1300*1300)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************



//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Patrol_Enemy::Patrol_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, patrol_enemy), m_Index(0),m_Arrival(false)
{
	//�����蔻��̐ݒ�
	SetColl(new Collision(this, { 0.0f,100.0f,0.0f }, 100));

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor();	//���F
	GetMaterial()->Emission = RefColor() ;	//���Ȕ����F
	GetMaterial()->noTexSampling = 0;

	m_Destination.push_back(D3DXVECTOR3(pos.x + 500.0f, pos.y, pos.z));
	m_Destination.push_back(D3DXVECTOR3(pos.x - 500.0f, pos.y, pos.z));

	//�J����(�v���C���[)�̂�������փG�l�~�[���������鏈��
	D3DXVECTOR3 vec = m_Destination.front() - pos;
	SetRot(D3DXVECTOR3(0.0f, -atan2f(vec.z, vec.x) + D3DX_PI * 0.5f, 0.0f));
	SetOldPos();

	SetFootSteps(LoadSound("patrolenemy"));
	PlaySound(RefFootSteps(), -1, 0.0f);

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Patrol_Enemy::~Patrol_Enemy()
{
	if (RefUse() == false)
	{

		if (frand() < DROPCHANSE)
		{
			CardDropChance(RefPos(), DROPRANK2);
		}

	}
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Patrol_Enemy::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Patrol_Enemy::Uninit(void)
{
	StopSound(RefFootSteps());
}

//=============================================================================
// �X�V����
//=============================================================================
void Patrol_Enemy::Update(void)
{
	DistanceVolume(GetCamera()->pos);
	//�h�b�g�_���[�W�̍X�V
	Update_DotDamage();
	//�A�N�V����
	SearchAction();
	//�A�j���[�V�����ƍU���Ԋu�X�V�̏���
	m_animetion += 0.09f;
	if (m_heit > 0)
	{
		m_heit--;
	}
	if (m_Attackdirei > 0)
	{
		m_Attackdirei--;
	}
	//�J���[�̕ύX
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		GetMaterial()->Diffuse = RefColor();	//�g�U�F
		GetMaterial()->Ambient = RefColor();	//���F
		GetMaterial()->Emission = RefColor();	//���Ȕ����F
	}
	//���_���[�W
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamageDot(3.0f / 60.0f);
	}
	//�󂯂������̏���
	for (int index = 0; index < ATTRIBUTE_NUM; index++)
	{
		if (GetAttribute(index) != nullptr)
			GetAttribute(index)->AttributeByType(this);
	}
	//�t���A���ʂ̓K��
	GetFloorPos();
	//�����蔻��̍Đݒ�
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
	SetOldPos();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Patrol_Enemy::Draw()
{
	Object aa;
	Object bb;
	Object cc;
	ZeroMemory(&aa.m_Material, sizeof(&aa.m_Material));
	D3DXCOLOR co = GetMaterial()->Diffuse;
	aa.m_Material.Diffuse = co ;
	aa.m_Material.Ambient = co * 0.3f;
	aa.m_Material.Emission = co * 0.3f;
	float scl = 3.4f;
	float plus = 0.0f;
	
	if (m_Attackdirei > 60)
	{
		scl = 3.4f + sinf((90.0f - (float)m_Attackdirei) * 0.04f * D3DX_PI + 0.3f) * 0.8f;
		plus = (90.0f - (float)m_Attackdirei) * 0.1f;
	}

	aa.m_Scl = { scl,scl,scl };
	aa.m_Pos = RefPos();
	aa.m_Pos.y += 120.0f;
	aa.m_Rot.x = 1.23f;
	aa.m_Rot.y = RefRot().y + D3DXToRadian(90);
	aa.m_Rot.z = m_animetion + plus;
	bb = aa;
	bb.m_Scl = { scl,scl,scl };
	bb.m_Pos = RefPos();
	bb.m_Pos.y += 120.0f;
	bb.m_Rot.y = RefRot().y + D3DXToRadian(180);
	bb.m_Rot.x = 0.0f;

	cc = bb;
	cc.m_Scl *= 0.65f;
	cc.m_Pos.y -= 70.0f;
	cc.m_Pos.x += sinf(cc.m_Rot.y - 0.4f) * 40.0f;
	cc.m_Pos.z += cosf(cc.m_Rot.y - 0.4f) * 40.0f;
	cc.m_Rot.z = m_animetion;
	Draw3DModel(aa, RefModelMaterial().m_Haguruma);
	Draw3DModel(bb, RefModelMaterial().m_Haguruma_Hontai);
	Draw3DModel(cc, RefModelMaterial().m_Haguruma_Hontai);
	//HP�̕\��
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y - 20.0f + 8.7f * RefScl().y * DISTANCE_DIFF,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 150.0f ,10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);

	Draw_DotDamage();


#if _DEBUG
	//�����蔻��̕`��
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
		sphere.m_Rot = RefRot();
		//Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	
#endif // _DEBUG
}
//=============================================================================
// �A�N�V����
//=============================================================================
void Patrol_Enemy::Action(void)
{
	if (!RefStuck())
	{
		//�ǐ�
		D3DXVECTOR3 vec = D3DXVECTOR3(GetCamera()->pos.x - RefPos().x, GetCamera()->pos.y - RefPos().y, GetCamera()->pos.z - RefPos().z);
		float rot = -atan2f(vec.z, vec.x) + D3DX_PI / 2;
		SetRot(D3DXVECTOR3(0.0f, rot, 0.0f));
		Chase(GetCamera()->pos);
	}
}

//=============================================================================
// �������Ă��邩�ǂ���
//=============================================================================
void Patrol_Enemy::Arrival(void)
{
	D3DXVECTOR3 Vec = m_Destination[m_Index] - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (length <= 100)
	{
		m_Index++;
		if (m_Index >= m_Destination.size())
			m_Index = 0;

		//�J����(�v���C���[)�̂�������փG�l�~�[���������鏈��
		D3DXVECTOR3 vec = m_Destination[m_Index] - RefPos();
		SetRot(D3DXVECTOR3(0.0f, -atan2f(vec.z, vec.x) + D3DX_PI * 0.5f, 0.0f));
	}
}
//=============================================================================
// �v���C���[�Ƃ̃A�N�V����
//=============================================================================
void Patrol_Enemy::SearchAction(void)
{
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (length < 600 * 600)
	{
		if (m_heit < 180)
		{
			m_heit = 180;
		}
	}
	if (m_heit > 0)
	{
		Action();
	}
	if (length < 300 * 300 && m_Attackdirei == 0)
	{
		m_Attackdirei = 90;
		GetPlayer()->IsDamage(15.0f);
	}
}

void Patrol_Enemy::IsDamage(float damage)
{
	//�_���[�W�A�N�V����(�F�ύX)
	DamageAction(30);
	D3DXVECTOR3 pos = RefPos();
	pos.y += 150 - 30.0f + frand() * 60.0f;
	pos.x += -30.0f + frand() * 60.0f;
	pos.z += -30.0f + frand() * 60.0f;
	SetDamageText((int)damage, pos, DIK_COLER_WHITE);
	//�_���[�W�̌v�Z
	SetHp(RefHp() - damage);
	if (RefHp() <= 0)
		IsDiscard();
	m_heit = 480;
}

//=============================================================================
// �����ɂ�鉹�ʂ̒���
//=============================================================================
void Patrol_Enemy::DistanceVolume(D3DXVECTOR3 pos)
{
	//2�_�Ԃ̋�����2��l�̎擾
	D3DXVECTOR3 vec = RefPos() - pos;
	float length = D3DXVec3LengthSq(&vec);

	//�����ɂ�鉹�ʂ̒���
	if (length > HEARING_DISTANCE) {
		SetVolume(RefFootSteps(), 0);
	}
	else {
		float rate = length / HEARING_DISTANCE;
		SetVolume(RefFootSteps(), (1.0f - rate) * 0.4f);
	}
}

