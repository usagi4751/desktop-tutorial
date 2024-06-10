//=============================================================================
//
// �G���� [scorpion.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "scorpion.h"
#include "material.h"
#include "sprite.h"
#include "floor.h"
#include "Game.h"
#include "card.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_POINT	(300)							// �q�b�g�|�C���g
#define COLL_CIRCLE	(100.0f)						// �����蔻��̔��a
#define DROPCHANSE			(0.55f)						//�h���b�v��
#define DROPRANK2			(0.5f)						//�����N�Q��
#define HEARING_DISTANCE (1300*1300)
//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Scorpion::Scorpion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use,Bullet_Interface* pBif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, scorpion_enemy), m_LegIndex(0)
{
	SetPos({ pos.x,45.0f,pos.z });

	//�{�̂̒��S�_����K���܂ł̋���
	float length; 
	length = sqrtf((0.03f * DISTANCE_DIFF * SCORPION_SCALE) * (0.03f * DISTANCE_DIFF * SCORPION_SCALE) + (-0.44f * DISTANCE_DIFF * SCORPION_SCALE) * (-0.44f * DISTANCE_DIFF * SCORPION_SCALE));
	//�K���̃C���X�^���X��
	m_Tail = new Scorpion_Tail(D3DXVECTOR3(RefPos().x, RefPos().y + (0.03f * DISTANCE_DIFF * SCORPION_SCALE), RefPos().z + (-0.44f * DISTANCE_DIFF * SCORPION_SCALE))
		, RefRot(), RefScl(), RefVel(), RefColor(), true, length, pBif);

	//�����Ƃ̏����p�x�e�[�u��
	float InitRotArray[] = { D3DXToRadian(5.0f),D3DXToRadian(22.0f),D3DXToRadian(30.0f),D3DXToRadian(18.0f),D3DXToRadian(0.0f),D3DXToRadian(40.0f) };
	//�r�̃C���X�^���X��
	for (int i = 0; i < SCORPION_LEG_NUM; i += 2)
	{
		//�{�̂̒��S�_���瑫�܂ł̋���
		length = sqrtf(DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2) * DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2));

		m_Leg[i] = new Scorpion_Leg(D3DXVECTOR3(RefPos().x, RefPos().y, RefPos().z - DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2))
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i]), RefRot().y, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, length);

		m_Leg[i + 1] = new Scorpion_Leg(D3DXVECTOR3(RefPos().x, RefPos().y, RefPos().z - DISTANCE_DIFF * SCORPION_LEG_WIDHT * (i / 2))
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i+1]), RefRot().y + D3DX_PI, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, -length);
	}
	
	//�����蔻��̋����̐ݒ�
	SetColl(new Collision(this, {0,0,0}, 100));
	SetOldPos();
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor() * 0.3f;	//���F
	GetMaterial()->Emission = RefColor() * 0.3f;	//���Ȕ����F
	GetMaterial()->noTexSampling = 0;

	SetFootSteps(LoadSound("scorpion"));
	PlaySound(RefFootSteps(), -1, 0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Scorpion::~Scorpion()
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
HRESULT Scorpion::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Scorpion::Uninit(void)
{
	//�K���̉��
	delete m_Tail;
	m_Tail = nullptr;
	StopSound(RefFootSteps());
	//���̉��
	for (int i = 0; i < SCORPION_LEG_NUM; i++)
	{
		delete m_Leg[i];
		m_Leg[i] = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Scorpion::Update(void)
{
	DistanceVolume(GetCamera()->pos);
	//�h�b�g�_���[�W�̍X�V
	Update_DotDamage();
	//�A�N�V����
	Action();
	//�T�[�`�A�N�V����
	SearchAction();
	//�ߋ����U���̃N�[���^�C��
	if (m_Attackdirei > 0)
	{
		m_Attackdirei--;
	}
	//�J���[�ύX
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		SetColor({ 1.0f,1.0f,1.0f,1.0f });
		GetMaterial()->Diffuse = RefColor();	//�g�U�F
		GetMaterial()->Ambient = RefColor() * 0.3f;	//���F
		GetMaterial()->Emission = RefColor() * 0.3f;	//���Ȕ����F
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
void Scorpion::Draw(void)
{
	//�J�����O������
	SetCullingMode(CULL_MODE_NONE);
	// ���̃��f���̕`��
	Draw3DModel(*this, RefModelMaterial().m_Scorpion);
	//�������J�����O
	SetCullingMode(CULL_MODE_BACK);

	//�K�����f���̕`��
	m_Tail->Draw();

	//�r���f���̕`��
	for (int i = 0; i < SCORPION_LEG_NUM; i++)
	{
		m_Leg[i]->Draw();
	}
	//HP�̕\��
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y  + 130.0f,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 150.0f ,10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);
	Draw_DotDamage();
#if _DEBUG
	//�����蔻�苅�̐ݒ�
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
void Scorpion::Action(void)
{
	//�K���̊p�x�A�|�W�V�����̐ݒ�
	m_Tail->SetRot({ m_Tail->RefRot().x,RefRot().y,m_Tail->RefRot().z });
	m_Tail->SetPos({
		RefPos().x + m_Tail->RefLength() * sinf(RefRot().y + D3DX_PI),
		RefPos().y + (0.03f * DISTANCE_DIFF * SCORPION_SCALE),
		RefPos().z + m_Tail->RefLength() * cosf(RefRot().y + D3DX_PI) });
	//�K���̍X�V
	m_Tail->Update();

	//���̊p�x�A�|�W�V�����̐ݒ�
	for (int i = 0; i < SCORPION_LEG_NUM; i += 2)
	{
		m_Leg[i]->SetRot({ m_Leg[i]->RefRot().x,RefRot().y,m_Leg[i]->RefRot().z });
		m_Leg[i]->SetPos({
		RefPos().x + m_Leg[i]->RefLength() * sinf(RefRot().y + D3DX_PI),
		RefPos().y,
		RefPos().z + m_Leg[i]->RefLength() * cosf(RefRot().y + D3DX_PI) });

		m_Leg[i + 1]->SetRot({ m_Leg[i + 1]->RefRot().x,RefRot().y + D3DX_PI ,m_Leg[i + 1]->RefRot().z });
		m_Leg[i + 1]->SetPos({
		RefPos().x - m_Leg[i + 1]->RefLength() * sinf(RefRot().y + D3DX_PI),
		RefPos().y,
		RefPos().z - m_Leg[i + 1]->RefLength() * cosf(RefRot().y + D3DX_PI) });

		//���̍X�V
		m_Leg[i]->Update();
		m_Leg[i + 1]->Update();
	}
}
//=============================================================================
// �v���C���[�Ƃ̃A�N�V����
//=============================================================================
void Scorpion::SearchAction(void)
{
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (length < 1000 * 1000)
	{
		//�J����(�v���C���[)�̂�������փG�l�~�[���������鏈��
		D3DXVECTOR3 vec = D3DXVECTOR3(GetCamera()->pos.x - RefPos().x, GetCamera()->pos.y - RefPos().y, GetCamera()->pos.z - RefPos().z);
		float rot = -atan2f(vec.z, vec.x) + D3DX_PI / 2;
		SetRot(D3DXVECTOR3(0.0f, rot, 0.0f));
		//�ǐ�
		Chase(GetCamera()->pos);
		SetPos({ RefPos().x,RefPos().y,RefPos().z });

		m_Tail->SearchAction();
	}
	if (length < 300 * 300 && m_Attackdirei == 0)
	{
		m_Attackdirei = 90;
		GetPlayer()->IsDamage(15.0f);
	}
}
//=============================================================================
// �_���[�W���󂯂�
//=============================================================================
void Scorpion::IsDamage(float damage)
{
	//�_���[�W�A�N�V����(�F�ύX)
	DamageAction(30);

	D3DXVECTOR3 pos = RefPos();
	pos.y += 50 - 30.0f + frand() * 60.0f;
	pos.x += -30.0f + frand() * 60.0f;
	pos.z += -30.0f + frand() * 60.0f;
	SetDamageText((int)damage, pos, DIK_COLER_WHITE);

	//�_���[�W�̌v�Z
	SetHp(RefHp() - damage);
	if (RefHp() <= 0) IsDiscard();

	//�r�̃A�N�V����
	for (int i = 0; i < SCORPION_LEG_NUM; i++) m_Leg[i]->DamageAction(30);

	//�K���̃A�N�V����
	m_Tail->DamageAction(30);
}

//=============================================================================
// �����ɂ�鉹�ʂ̒���
//=============================================================================
void Scorpion::DistanceVolume(D3DXVECTOR3 pos)
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
		SetVolume(RefFootSteps(), 1.0f - rate);
	}
}