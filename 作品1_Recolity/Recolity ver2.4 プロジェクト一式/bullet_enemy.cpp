//=============================================================================
//
// �G���� [bullet_enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "bullet_enemy.h"
#include "material.h"
#include "sprite.h"
#include "fire_attribute.h"
#include "floor.h"
#include "card.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_POINT	(100)							// �q�b�g�|�C���g
#define COLL_CIRCLE	(100.0f)						// �����蔻��̔��a
#define BULLET_DAMAGE	(10)						// �ʏ�e�̃_���[�W��
#define BULLET_SCALE	{35,35,35}					// �e�̃T�C�Y
#define BULLET_SPEED	(30.0f)						// �e�̈ړ���
#define BULLET_RANGE	(2500)						// �˒�����
#define SHOT_INTERVAL	(240)						// �ˌ��C���^�[�o��
#define SHOT_MOTIONTIME	90							//���˃��[�V�����̎���
#define DROPCHANSE			(0.35f)						//�h���b�v��
#define DROPRANK2			(0.75f)						//�����N�Q��
#define HEARING_DISTANCE (1800*1800)
//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Bullet_Enemy::Bullet_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, bullet_enemy), m_BulletIF(bif), m_Itv_b(0)
{
	//�����蔻��̐ݒ�
	SetColl(new Collision(this, { 0.0f,100.0f,0.0f }, 100));
	
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor();	//���F
	GetMaterial()->Emission = RefColor() * 0.5f;	//���F
	GetMaterial()->noTexSampling = 0;
	m_BulletSound = LoadSound("enemybullet1");
	m_ChargeSound = LoadSound("enemybullet2");
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Bullet_Enemy::~Bullet_Enemy()
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
HRESULT Bullet_Enemy::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Bullet_Enemy::Uninit(void)
{
	StopSound(m_ChargeSound);
	StopSound(m_BulletSound);
}
//=============================================================================
// �X�V����
//=============================================================================
void Bullet_Enemy::Update(void)
{
	DistanceVolume(GetCamera()->pos);
	//�A�N�V����
	Action();
	//�T�[�`�A�N�V����
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
void Bullet_Enemy::Draw(void)
{
	Object model1;

	ZeroMemory(&model1.m_Material, sizeof(&model1.m_Material));
	D3DXCOLOR co = GetMaterial()->Diffuse;
	model1.m_Material.Diffuse = co;	//�g�U�F
	model1.m_Material.Ambient = co * 0.3f;	//���F
	model1.m_Material.Emission = co * 0.3f;	//���F
	model1.m_Pos = RefPos();
	model1.m_Pos.y += 100.0f;
	model1.m_Scl = { 10.0f, 10.0f, 10.0f };
	model1.m_Rot = { m_animationtimer,m_animationtimer + RefRot().y,0 };
	if (m_trigger == true)
	{
		model1.m_Rot = { 0,RefRot().y,sinf((float)m_bullet_motion/ (float)SHOT_MOTIONTIME * 1.4f)*25.0f };
	}
	Draw3DModel(model1, RefModelMaterial().m_Bullet_Enemy_01);
	model1.m_Scl = { 70.0f,70.0f,70.0f };
	if (m_trigger == true)
	{
		float mina = (float)m_bullet_motion / (float)SHOT_MOTIONTIME * 0.3f;
		model1.m_Material.Diffuse = { 1.0f,mina,0.0f,1.0f };
		model1.m_Material.Ambient = { 1.0f,mina,0.0f,1.0f };
		model1.m_Material.Emission = { 1.0f,mina,0.0f,1.0f };
	}

	DrawPolygonBillCR(model1, RefImageMaterial().m_Eye);
	Draw_DotDamage();
	//HP�̕\��
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y - 20.0f + 8.7f * RefScl().y * DISTANCE_DIFF,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 150.0f ,10.0f,0.0f };
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
	}
	
#endif // _DEBUG
}

void Bullet_Enemy::Action(void)
{
	m_animationtimer += 0.03f;
}
//=============================================================================
// �v���C���[�Ƃ̃A�N�V����
//=============================================================================
void Bullet_Enemy::SearchAction(void)
{
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (length < 1600 * 1600)
	{
		// �J����(�v���C���[)�̂�������փG�l�~�[���������鏈��
		float rot = -atan2f(Vec.z, Vec.x) + D3DX_PI / 2;
		SetRot(D3DXVECTOR3(0.0f, rot, 0.0f));

		// �e�̔���
		m_Itv_b--;
		if (m_bullet_motion > 0)
		{
			m_bullet_motion--;
		}
		if (m_Itv_b <= 0)
		{
			m_bullet_motion = SHOT_MOTIONTIME;
			m_Itv_b = SHOT_INTERVAL;
			m_trigger = true;
			
			PlaySound(m_ChargeSound, 0, 0.0f);
		}
		if (m_trigger == true && m_bullet_motion == 0)
		{
			PlaySound(m_BulletSound, 0, 0.0f);
			m_trigger = false;
			//�e�̔��ˈʒu�̐ݒ�
			D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x, -100 + (7.0f * RefScl().y * DISTANCE_DIFF), RefPos().z);
			D3DXVECTOR3 vel = D3DXVECTOR3(BULLET_SPEED * sinf(rot), 0.0f, BULLET_SPEED * cosf(rot));

			Attribute_Element element;

			m_BulletIF->SetNBullet(bullet, enemy, pos, RefRot(), BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE,
				BULLET_SPEED, NO_GVT, NO_DEC, BULLET_RANGE, none, element, &RefImageMaterial().m_EnemyBulletTriangle);
		}
	}
	else {
		m_bullet_motion = 0;
		m_trigger = false;
	}
}

//=============================================================================
// �����ɂ�鉹�ʂ̒���
//=============================================================================
void Bullet_Enemy::DistanceVolume(D3DXVECTOR3 pos)
{
	//2�_�Ԃ̋�����2��l�̎擾
	D3DXVECTOR3 vec = RefPos() - pos;
	float length = D3DXVec3LengthSq(&vec);

	//�����ɂ�鉹�ʂ̒���
	if (length > HEARING_DISTANCE) {
		SetVolume(m_ChargeSound, 0);
		SetVolume(m_BulletSound, 0);
	}
	else {
		float rate = length / HEARING_DISTANCE;
		SetVolume(m_ChargeSound, 1.0f - rate);
		SetVolume(m_BulletSound, 1.0f - rate);
	}
}
