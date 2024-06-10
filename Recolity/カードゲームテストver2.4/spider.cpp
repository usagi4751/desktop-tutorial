//=============================================================================
//
// �G���� [spider.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "spider.h"
#include "base_attribute.h"
#include "material.h"
#include "sprite.h"
#include "sound.h"
#include "floor.h"
#include "Game.h"
#include "card.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_POINT	(300)							// �q�b�g�|�C���g
#define COLL_CIRCLE	(100.0f)						// �����蔻��̔��a
#define BULLET_DAMAGE	(10)							// �ʏ�e�̃_���[�W��
#define BULLET_SCALE	{30,30,30}						// �ړ���
#define BULLET_SPEED	(30.0f)						// �ړ���
#define BULLET_RANGE	(2500)						// �˒�����
#define SHOT_INTERVAL	(240)						// �ˌ��C���^�[�o��
#define DROPCHANSE			(0.75f)						//�h���b�v��
#define DROPRANK2			(0.5f)						//�����N�Q��
//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Spider::Spider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* pBif)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, spider_enemy), m_LegIndex(0),m_BulletIF(pBif),m_Itv_b(SHOT_INTERVAL)
{
	SetPos({ pos.x,pos.y + 45.0f,pos.z });
	SetOldPos();
	//�����Ƃ̏����p�x�e�[�u��
	float InitRotArray[] = { D3DXToRadian(5.0f),D3DXToRadian(22.0f),D3DXToRadian(30.0f),D3DXToRadian(18.0f),D3DXToRadian(0.0f),D3DXToRadian(40.0f) };
	//���̃C���X�^���X��
	for (int i = 0; i < SPIDER_LEG_NUM; i += 2)
	{
		//�{�̂̒��S�_���瑫�܂ł̋���
		float length = sqrtf((DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2)) * (DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2)));

		m_Leg[i] = new Spider_Leg(D3DXVECTOR3(RefPos().x , RefPos().y, RefPos().z - DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2) )
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i]), RefRot().y, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, length);

		m_Leg[i + 1] = new Spider_Leg(D3DXVECTOR3(RefPos().x , RefPos().y, RefPos().z - DISTANCE_DIFF * SPIDER_LEG_WIDHT * (i / 2))
			, D3DXVECTOR3(RefRot().x + (InitRotArray[i+1]), RefRot().y + D3DX_PI, RefRot().z)
			, RefScl(), RefVel(), RefColor(), true, -length);
	}

	//�����蔻��̋����̐ݒ�
	SetColl(new Collision(this, {0,0,0}, 100));
	SetColl(new Collision(this, {0,0,0}, 160));

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor() * 0.3f;	//���F
	GetMaterial()->Emission = RefColor() * 0.3f;	//���Ȕ����F
	GetMaterial()->noTexSampling = 0;

	SetFootSteps(LoadSound("spider"));
	PlaySound(RefFootSteps(), -1, 0.0f);

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Spider::~Spider()
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
HRESULT Spider::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Spider::Uninit(void)
{
	//�T�E���h�̉��
	StopSound(RefFootSteps());

	//���̉��
	for (int i = 0; i < SPIDER_LEG_NUM; i++)
	{
		delete m_Leg[i];
		m_Leg[i] = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Spider::Update(void)
{
	//�h�b�g�_���[�W�̍X�V
	Update_DotDamage();
	//�A�N�V����
	Action();
	//�T�[�`�A�N�V����
	SearchAction();
	DistanceVolume(GetCamera()->pos);
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
	GetColl(0)->SetCollPos();
	GetColl(1)->SetCollPos({
		RefPos().x + 2.0f * RefScl().x * DISTANCE_DIFF * sinf(-RefRot().y),
		RefPos().y,
		RefPos().z - 2.0f * RefScl().z * DISTANCE_DIFF * cosf(-RefRot().y) });
	SetOldPos();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Spider::Draw(void)
{
	// ���̃��f���̕`��
	Draw3DModel(*this, RefModelMaterial().m_Spider);

	//�����f���̕`��
	for (int i = 0; i < SPIDER_LEG_NUM; i++)
	{
		m_Leg[i]->Draw();
	}
	//HP�̕\��
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y + 130.0f,RefPos().z };
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
		sphere.m_Scl = { pColl->RefCollCircle() ,pColl->RefCollCircle() ,pColl->RefCollCircle() };
		sphere.m_Rot = RefRot();
		//Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	
#endif // _DEBUG
}
//=============================================================================
// �A�N�V����
//=============================================================================
void Spider::Action(void)
{

	//���̊p�x�A�|�W�V�����̐ݒ�
	for (int i = 0; i < SPIDER_LEG_NUM; i += 2)
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
void Spider::SearchAction(void)
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


		SetRot({ 0.0f,RefRot().y,RefRot().z });
		// �e�̔���
		m_Itv_b--;
		if (m_Itv_b >= 30 && m_Itv_b <= 50) {
			//�e�̔��ˈʒu
			D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 10.0f * DISTANCE_DIFF * sinf(RefRot().y),
				RefPos().y + (RefScl().y + 2.0f * DISTANCE_DIFF),
				RefPos().z + 10.0f * DISTANCE_DIFF * cosf(RefRot().y));
			Emitta(7, pos);
		}
		if (m_Itv_b <= 0)
		{
			//�e�̔��ˈʒu
			D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 10.0f * DISTANCE_DIFF * sinf(RefRot().y),
				RefPos().y + (RefScl().y +  80),
				RefPos().z + 10.0f * DISTANCE_DIFF * cosf(RefRot().y));
			//�e�̔��ˑ��x
			D3DXVECTOR3 vel = D3DXVECTOR3(BULLET_SPEED * sinf(RefRot().y), 0.0f, BULLET_SPEED * cosf(RefRot().y));

			Attribute_Element element;
			element.m_Frame = 120;
			element.m_Interval = 0;
			element.m_Value = 3.0f;

			m_BulletIF->SetNBullet(bullet, enemy, pos, RefRot(), BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE,
				BULLET_SPEED, NO_GVT, NO_DEC, BULLET_RANGE, water, element, &RefImageMaterial().m_Kumo_bullet,100);
			m_Itv_b = SHOT_INTERVAL;
		}
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
void Spider::IsDamage(float damage)
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
	if (RefHp() <= 0) IsDiscard();

	//�r�̃A�N�V����
	for (int i = 0; i < SPIDER_LEG_NUM; i++) m_Leg[i]->DamageAction(30);
}