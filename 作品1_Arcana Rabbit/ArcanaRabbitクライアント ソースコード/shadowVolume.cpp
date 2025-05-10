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
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//���[���h�}�g���b�N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.x);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	///�J���[�o�b�t�@�[�}�X�N�L��
	Renderer::SetBlendMaskEnable(true);

	//�X�e���V���������ݗL��
	Renderer::SetStencilEnable(true);

	//�J�����O����
	Renderer::SetCullEnable(false);

	m_Component->Draw();
			
	//�J���[�o�b�t�@�[�}�X�N����
	Renderer::SetBlendMaskEnable(false);

	//�X�e���V���������ݖ���
	Renderer::SetDepthEnable(true);

	//�J�����O�L��
	Renderer::SetCullEnable(true);
				

}