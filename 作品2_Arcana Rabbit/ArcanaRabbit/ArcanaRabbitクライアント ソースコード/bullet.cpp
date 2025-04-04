#include "main.h"
#include "bullet.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "enemy.h"
#include"pch.h"
void bullet::Init() {
	m_Position = XMFLOAT3{ 10.0f,0.0f,0.0f };
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\bullet.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}
void bullet::Uninit() {
	//((ModelRenderer*)m_Component)->UnloadAll();
	m_Component->UnInit();
	delete m_Component;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void bullet::Update()
{

	Scene* scene = Manager::GetScene();
	float bullet_speed = 0.1f;
	m_Position.x += sinf(m_Rotation.y) * cosf(m_Rotation.x) * bullet_speed;
	m_Position.z += cosf(m_Rotation.y) * cosf(m_Rotation.x) * bullet_speed;
	m_Position.y += sinf(m_Rotation.x) * bullet_speed;
	m_Component->Update();
	m_life--;


	std::list<Enemy*> enemylist;
	enemylist = Manager::GetScene()->GetEntitylist<Enemy>();
	for (Enemy* enemy : enemylist)
	{
		XMFLOAT3 vec;
		vec.x = enemy->GetPosition()->x - m_Position.x;
		vec.y = enemy->GetPosition()->y - m_Position.y;
		vec.z = enemy->GetPosition()->z - m_Position.z;
		float len = D3DXVec3LengthSq(&vec);

		if (len <1)
		{
			enemy->SetDestroy();
			this->SetDestroy();
			break;
		}
	}
	if (m_life <= 0)
	{

		SetDestroy();
	}
}

void bullet::Draw()
{
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_Component->Draw();
}
