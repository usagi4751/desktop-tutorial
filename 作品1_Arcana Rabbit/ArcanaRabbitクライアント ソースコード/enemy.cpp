#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "bullet.h"
#include "audio.h"
#include "input.h"
#include "animationModel.h"
#include "player.h"
#include "particleInterface.h"
#include "Emitterbrast.h"
#include "dropitem.h"
#include "floor.h"
void Enemy::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
	m_Component = new AnimationModel(this);
	((AnimationModel*)m_Component)->Load("asset\\model\\enemy2.obj");
	//((AnimationModel*)m_Component)->Load("asset\\model\\Akai.fbx");
	//((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Run.fbx","Run");
	//((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Idle.fbx", "idle");

	//m_Component = new ModelRenderer(this);
	//((ModelRenderer*)m_Component)->Load("asset\\model\\enemy2.obj");
	m_Componenthitbox = new ModelRenderer(this);
	((ModelRenderer*)m_Componenthitbox)->Load("asset\\model\\hitbox_maru.obj");

	hp = 10;
	m_floor = Manager::GetScene()->GetGameObject<Floor>();

}

void Enemy::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_Component->UnInit();
	delete m_Component;
	m_Componenthitbox->UnInit();
	delete m_Componenthitbox;

}

void Enemy::Update()
{
	m_pPlayer = Manager::GetScene()->GetGameObject<Player>();
	m_oldpos = m_Position;
	if (attackct > 0)
	{
		attackct--;
	}
	if (m_hit >0)
	{
		m_hit--;
	}
	//float size = 0.3f;
	//SetScale({ size,size,size });
	m_Position.y = 0.0f;
	//くねくねさせる
	if (animatelot > 0.15)
	{
		swap = false;
	}	
	if (animatelot < -0.15)
	{
		swap = true;
	}
	animatelot += (float)(-1 + swap * 2) * 0.05f;
	animatelot = 0;
	animatelot = 0;
	//プレイヤーのほうに向く
	XMFLOAT3 playerpos = *m_pPlayer->GetPosition();
	XMFLOAT3 playerlen = { m_Position.x - playerpos.x,m_Position.y - playerpos.y ,m_Position.z - playerpos.z };
	if (D3DXVec3LengthSq(&playerlen) < 1.0f && attackct <= 0)
	{
		attackct = 60;
		m_pPlayer->AddDamage(1.0f);
	}
	XMFLOAT2 a = { (playerpos.x - m_Position.x),(playerpos.z - m_Position.z) };
	float l2 = atan2(a.x,a.y);
	m_Rotation.y = l2;
	XMVECTOR quat =  XMQuaternionRotationRollPitchYaw(XM_PIDIV2, m_Rotation.y + animatelot + XM_PI, 0.0f);
	XMStoreFloat4(&m_quat, quat);
	//m_Position.x = m_Position.x + sinf(m_Rotation.y) * 0.03f;
	//m_Position.z = m_Position.z + cosf(m_Rotation.y) * 0.03f;



	if (m_floor != nullptr  && !m_floor->GetFloor({ m_Position.x , m_oldpos.z }))
	{
		//m_Position.x = m_oldpos.x;
	}
	if (m_floor != nullptr && !m_floor->GetFloor({ m_oldpos.x , m_Position.z }))
	{
	//	m_Position.z = m_oldpos.z;
	}
	if (hp <= 0)
	{
		int dropitem = (int)rand() % 3;
		if (dropitem == 0)
		{
			Item dropitemdata;
			dropitemdata.m_ItemNo = 2 + (int)rand() % 4;
			dropitemdata.m_ItemNum = 1;
			dropitemdata.m_maxhelth = 10 + (int)rand() % 5;
			dropitemdata.m_def = 3 + (int)rand() % 2;
			dropitemdata.m_damage = (int)rand() % 2;
			Dropitem* item = Manager::GetScene()->AddObject<Dropitem>(1);
			item->Setitem(dropitemdata);
			item->SetPosition(m_Position);
		}
		if (dropitem == 1)
		{
			Item dropitemdata;
			dropitemdata.m_ItemNo = 2 + (int)rand() % 4;
			dropitemdata.m_ItemNum = 1;
			dropitemdata.m_maxhelth = 10 + (int)rand() % 5;
			dropitemdata.m_damage = (int)rand() % 2;
			dropitemdata.m_def = 3 + (int)rand() % 2;
			Dropitem* item = Manager::GetScene()->AddObject<Dropitem>(1);
			item->Setitem(dropitemdata);
			item->SetPosition(m_Position);
		}
		if (dropitem == 2)
		{
			Item dropitemdata;
			dropitemdata.m_skillNo = -1;
			dropitemdata.m_ItemNo = 6;
			dropitemdata.m_ItemNum = 1;
			dropitemdata.m_damage = 3 + (int)rand() % 2;
			dropitemdata.m_maxhelth = 0;
			dropitemdata.m_def = 3;
			dropitemdata.movespeed = 5 +(int)rand() % 5;
			dropitemdata.m_attackspeed = 25 + (int)rand() % 15;
			Dropitem* item = Manager::GetScene()->AddObject<Dropitem>(1);
			item->Setitem(dropitemdata);
			item->SetPosition(m_Position);
		}
		if (dropitem == 3)
		{
			Item dropitemdata;
			dropitemdata.m_skillNo = 0;
			dropitemdata.m_ItemNo = 2;
			dropitemdata.m_ItemNum = 1;
			dropitemdata.m_damage = 2;
			dropitemdata.m_maxhelth = 0;
			dropitemdata.movespeed = 2 +(int)rand() % 15;
			Dropitem* item = Manager::GetScene()->AddObject<Dropitem>(1);
			item->Setitem(dropitemdata);
			item->SetPosition(m_Position);
		}
		
		//ParticleInerface::SetEmitter(new EmitterBrast(m_Position, {}));
		SetDestroy();
		
	}

	if (Input::GetKeyTrigger(0x31))
	{
		Degubtest(0);
	}
	if (Input::GetKeyTrigger(0x32))
	{
		Degubtest(1);
	}
	if (Input::GetKeyTrigger(0x33))
	{
		Degubtest(2);
	}
	if (Input::GetKeyTrigger(0x34))
	{
		Degubtest(3);
	}
}
float aaaa = 0;
void Enemy::Draw()
{
	aaaa += 0.003f;
	if (aaaa > 1)
	{
		aaaa = 0;
	}
	//m_Scale = { 0.33f,0.33f,0.33f };

	//((AnimationModel*)m_Component)->Update("Run", m_AnimationFrame, "idle", m_AnimationFrame, aaaa);

	m_AnimationFrame++;


	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	
	//rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_quat));
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	if (m_hit > 0)
	{
		material.Diffuse = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	material.TextureEnable = true;
	Renderer::SetMaterial(material);
	//カラー設定
	XMFLOAT4 coler = { 1.0f,1.0f,1.0f,1.0f };
	if (m_hit > 0)
	{
		coler = { 1.0f, 0.0f, 0.0f, 1.0f };
	}
	//((ModelRenderer*)m_Component)->Draw(coler);
	((AnimationModel*)m_Component)->Draw();
	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_quat));
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//m_Componenthitbox->Draw();
}



void Enemy::AddDamage(float damage)
{
	if (damage > 0)
	{
		hp -= damage;
		m_hit = 30;
	}

}

//if (Input::GetKeyPress(0x45))
//{
//	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(0.1f, 0.0f, 0.0f);
//	quat = XMQuaternionMultiply(XMLoadFloat4(&m_quat), quat);
//	XMStoreFloat4(&m_quat, quat);
//}
//if (Input::GetKeyPress(0x52))
//{
//	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(0.0f, 0.1f, 0.0f);
//	quat = XMQuaternionMultiply(XMLoadFloat4(&m_quat), quat);
//	XMStoreFloat4(&m_quat, quat);
//}
//if (Input::GetKeyPress(0x54))
//{
//	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(0.0f, 0.0f, 0.1f);
//	quat = XMQuaternionMultiply(XMLoadFloat4(&m_quat), quat);
//	XMStoreFloat4(&m_quat, quat);
//}