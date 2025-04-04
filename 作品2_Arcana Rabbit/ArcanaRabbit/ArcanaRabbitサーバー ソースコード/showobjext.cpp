#include "showobjext.h"
#include "renderer.h"
#include "modelRenderer.h"

void ShowObject::Init()
{

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\hemisphereLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\hemisphereLightingPS.cso");

	//Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	//Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
	
}

void ShowObject::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	if (m_Component != nullptr)m_Component->UnInit();
	delete m_Component;
}

void ShowObject::Update()
{
}

void ShowObject::Draw()
{
	if (m_Component != nullptr)
	{
		LIGHT light;
		light.Enable = true;
		XMVECTOR di;
		light.Direction = { 0.2f, -1.0f, 0.2f, 0.0f };
		di = XMVector4Normalize(XMLoadFloat4(&light.Direction));
		XMStoreFloat4(&light.Direction,di);
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
		rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
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
		m_Component->Draw();
		Renderer::SetAlphaTestEnable(false);
	}
}

void ShowObject::SetObject(const char* Loadonject)
{
	if (m_Component == nullptr)
	{
		m_Component = new ModelRenderer(this);
		((ModelRenderer*)m_Component)->Load(Loadonject);
	}
}

void ShowObject::SetShader(ShaderSetting setting)
{

	if (m_VertexLayout != nullptr)
	{
		m_VertexLayout->Release();
	}
	if (m_VertexShader != nullptr)
	{
		m_VertexShader->Release();
	}
	if (m_PixelShader != nullptr)
	{
		m_PixelShader->Release();
	}
	switch (setting)
	{
	case Nomal:
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\hemisphereLightingVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader, "shader\\hemisphereLightingPS.cso");
		break;
	case hemisphereLighting:
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
		break;
	default:
		break;
	}
}


