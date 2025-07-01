#include "dropitem.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "player.h"
#include "manager.h"
#include "inventory.h"
void Dropitem::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\dropitem.obj");
}

void Dropitem::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_Component->UnInit();
	delete m_Component;
}

void Dropitem::Update()
{
	if (m_Position.y > 0 )
	{
		m_Position.y = 0;
	}
	if (m_droptime > 0)
	{
		m_droptime--;
	}
	if (m_droptime < 1)
	{
		Player* player = Manager::GetScene()->GetGameObject<Player>();
		XMFLOAT3 PlayerPos = *player->GetPosition();
		XMFLOAT3 sq = { m_Position.x - PlayerPos.x,m_Position.y - PlayerPos.y,m_Position.z - PlayerPos.z };
		float len = D3DXVec3LengthSq(&sq);
		if (len < 2.0f)
		{
			Inventory::Getitem(m_DropItem);
			m_DropItem.m_ItemNo = -1;
			m_DropItem.m_ItemNum = 0;
			SetDestroy();
		}
	}
	
}

void Dropitem::Draw()
{
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(0.2f, 0.2f, 0.2f);

	//rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	rot = XMMatrixTranslation(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);
	//ƒ}ƒeƒŠƒAƒ‹Ý’è
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);
	m_Component->Draw();
}
