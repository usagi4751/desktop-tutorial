//=============================================================================
//
// �G���� [boss.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "boss.h"
#include "material.h"
#include "sprite.h"
#include "fire_attribute.h"
#include "floor.h"
#include "Game.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_POINT	(350)							// �q�b�g�|�C���g
#define COLL_CIRCLE	(100.0f)						// �����蔻��̔��a
#define BULLET_DAMAGE	(4)							// �ʏ�e�̃_���[�W��
#define BULLET_SCALE	{30,30,30}						// �ʏ�e�̃T�C�Y
#define BULLET_SPEED	(25.0f)						// �ʏ�e�̈ړ���
#define BULLET_RANGE	(3000)						// �ʏ�e�̎˒�����
#define CANNON_DAMAGE	(10)						// ��C�̃_���[�W��
#define CANNON_SCALE	{150,150,150}				// ��C�̃T�C�Y
#define CANNON_SPEED	(15.0f)						// ��C�̈ړ���
#define CANNON_GVT		(1.0f)						// ��C�̏d��
#define CANNON_FALL_AMOUNT	(0.5f)					// ������
#define CANNON_RANGE	(10000)						// ��C�̎˒�����
#define NORMAL_SHOT_INTERVAL	(127)				// �ʏ�e�̎ˌ��C���^�[�o��
#define CANNON_SHOT_INTERVAL	(300)				// ��C�̎ˌ��C���^�[�o��

#define HEARING_DISTANCE (1300*1300)
//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Boss::Boss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, boss_enemy),
	m_Itv_b(NORMAL_SHOT_INTERVAL), m_Itv_c(CANNON_SHOT_INTERVAL),m_BulletIF(bif)
{
	
	//�����蔻��̐ݒ�
	SetColl(new Collision(this, {0.0f,100.0f,0.0f}, 150));
	SetColl(new Collision(this, { 0.0f,300.0f,0.0f }, 150));
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor() * 0.3f;	//���F
	GetMaterial()->Emission = RefColor() * 0.3f;	//���Ȕ���
	GetMaterial()->noTexSampling = 0;

	m_BulletSound = LoadSound("bossbullet1");
	m_CannonSound = LoadSound("bossbullet2");
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Boss::~Boss()
{
	Uninit();
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Boss::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Boss::Uninit(void)
{
	StopSound(m_BulletSound);
	StopSound(m_CannonSound);
	if (RefUse() == false)
	{
		SceneTransition(SCENE_RESULT);
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void Boss::Update(void)
{
	DistanceVolume(GetCamera()->pos);
	SetOldPos();
	//�A�N�V����
	SearchAction();
	Update_DotDamage();
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamageDot(3.0f / 60.0f);
	}
	//�J���[�̕ύX
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
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
	for (Collision* pColl:*GetColl())
	{
		pColl->SetCollPos();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void Boss::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Boss);
	Draw_DotDamage();
	//HP�̕\��
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y + 450.0f,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 200.0f ,20.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);
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
	
#endif // _DEBUG
}
//=============================================================================
// �A�N�V����
//=============================================================================
void Boss::Action(void)
{
	CAMERA* pCam = GetCamera();

	// �J����(�v���C���[)�̂�������փG�l�~�[���������鏈��
	D3DXVECTOR3 Vec = D3DXVECTOR3(pCam->pos.x - RefPos().x, pCam->pos.y - RefPos().y - 200.0f, pCam->pos.z - RefPos().z);
	float rot_y = -atan2f(Vec.z, Vec.x) + D3DX_PI / 2.0f;
	float rot_x = atan2f(Vec.y, Vec.z);
	SetRot(D3DXVECTOR3(0.0f, rot_y, 0.0f));

	// ��C�̔���
	m_Itv_c--;
	if (m_Itv_c <= 0)
	{
		PlaySound(m_CannonSound, 0, 1.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(
			RefPos().x,
			RefPos().y + (12.5f * DISTANCE_DIFF * BOSS_SCALE),
			RefPos().z
		);

		Attribute_Element element;
		element.m_Frame = 30;
		element.m_Interval = 10;
		element.m_Value = 1.0f;
		Emitta(2, { GetCamera()->pos.x,0,GetCamera()->pos.z });
		m_BulletIF->SetCBullet(cannon, enemy, pos, GetCamera()->pos, { 45.0f,RefRot().y,0.0f }, CANNON_SCALE, { 1.0f,1.0f,0.0f,1.0f }, CANNON_DAMAGE,
			CANNON_SPEED, CANNON_GVT, NO_DEC, CANNON_RANGE, none, element, &RefImageMaterial().m_Cannon_Bullet);
		m_Itv_c = CANNON_SHOT_INTERVAL;
	}

	// �ʏ�e�̔���
	m_Itv_b--;
	if (m_Itv_b <= 0 )
	{
		PlaySound(m_BulletSound, 0, 1.0f);
		float len = sqrtf((1.7f * DISTANCE_DIFF * BOSS_SCALE) * (1.7f * DISTANCE_DIFF * BOSS_SCALE) + (5.4f * DISTANCE_DIFF * BOSS_SCALE) * (5.4f * DISTANCE_DIFF * BOSS_SCALE));
		D3DXVECTOR3 pos = D3DXVECTOR3(
			RefPos().x + len * sinf(rot_y + D3DXToRadian(18.0f)),
			RefPos().y + (3.5f * DISTANCE_DIFF * BOSS_SCALE),
			RefPos().z + len * cosf(rot_y + D3DXToRadian(18.0f))
		);
		Attribute_Element element;
		element.m_Frame = 30;
		element.m_Interval = 10;
		element.m_Value = 0.5f;
		m_BulletIF->SetNBullet(bullet, enemy, pos, { 0.0f,RefRot().y - D3DXToRadian(5.0f),0.0f }, BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE,
			BULLET_SPEED, NO_GVT, NO_DEC, BULLET_RANGE, none, element, &RefImageMaterial().m_EnemyBulletCannon);

		m_Itv_b = NORMAL_SHOT_INTERVAL;
	}
}
//=============================================================================
// �v���C���[�Ƃ̃A�N�V����
//=============================================================================
void Boss::SearchAction(void)
{
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (length < 2000 * 2000)
	{
		Action();
	}
	if (length < 300 * 300)
	{
		GetPlayer()->IsDamage(0.5f);
	}
}
