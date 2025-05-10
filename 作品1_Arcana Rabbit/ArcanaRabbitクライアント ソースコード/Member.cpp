#include "Member.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "DrawName.h"
void Member::Init()
{
	m_DrawName = new DrawName();
	m_DrawName->Init();
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_Component = new AnimationModel(this);
	((AnimationModel*)m_Component)->Load("asset\\model\\player6.fbx");

	m_Scale = {0.35f,0.35f ,0.35f };
}

void Member::Uninit()
{
	m_DrawName->UnInit();
	delete m_DrawName;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	if (m_Component != nullptr)m_Component->UnInit();
	delete m_Component;
}

void Member::Update()
{

}

void Member::Draw()
{
	if (m_Component != nullptr && m_Active == true)
	{
		XMVECTOR quat = XMQuaternionRotationRollPitchYaw(XM_PIDIV2, m_Rotation.y + XM_PI, 0.0f);
		XMStoreFloat4(&m_quat, quat);
		LIGHT light;
		light.Enable = true;
		XMVECTOR di;
		light.Direction = { 0.2f, -1.0f, 0.2f, 0.0f };
		di = XMVector4Normalize(XMLoadFloat4(&light.Direction));
		XMStoreFloat4(&light.Direction, di);
		light.Ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
		light.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };

		Renderer::SetLight(light);
		// 入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		// シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		XMMATRIX world, scale, rot, trans;
		scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		rot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_quat));
		trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(world);
		//マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		material.TextureEnable = true;
		Renderer::SetMaterial(material);
		Renderer::SetAlphaTestEnable(true);
		((AnimationModel*)m_Component)->Draw();
		Renderer::SetAlphaTestEnable(false);


		m_DrawName->Draw({ m_Position.x ,m_Position.y + 2.1f ,m_Position.z});
	}
}

void Member::SetActive(bool active)
{
	m_Active = active;
}

void Member::SetName(std::string name)
{
	m_DrawName->SetName(name);
}



