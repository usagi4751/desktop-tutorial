//==========================================
//==========================================
#include "main.h"
#include "renderer.h"
#include "shadowVolume.h"
#include "modelRenderer.h"
void ShadowVolume::Init() {



	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\sphere_smooth.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

}
void ShadowVolume::Uninit() {
	((ModelRenderer*)m_Component)->UnInit();
	delete m_Component;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}
void ShadowVolume::Update() {


}
void ShadowVolume::Draw() {
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリックス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.x);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	///カラーバッファーマスク有効
	Renderer::SetBlendMaskEnable(true);

	//ステンシル書き込み有効
	Renderer::SetStencilEnable(true);

	//カリング無効
	Renderer::SetCullEnable(false);

	m_Component->Draw();
			
	//カラーバッファーマスク無効
	Renderer::SetBlendMaskEnable(false);

	//ステンシル書き込み無効
	Renderer::SetDepthEnable(true);

	//カリング有効
	Renderer::SetCullEnable(true);
				

}