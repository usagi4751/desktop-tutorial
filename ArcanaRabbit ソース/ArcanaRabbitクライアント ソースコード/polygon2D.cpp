#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "material.h"
#include "Texture.h"
#include "audio.h"
#include "camera.h"3
#include "manager.h"
void Polygon2D::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position	= XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position	= XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position	 = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	 = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	 = XMFLOAT2(1.0f, 1.0f);


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);




	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
}

void Polygon2D::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


}

void Polygon2D::Update()
{
	
}
void Polygon2D::Draw()
{

	Drawdrafault();


}
void Polygon2D::Drawdrafault()
{

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���b�N�X�ݒ�
	Renderer::SetWorldViewProjection2D();
	//D3D11_MAPPED_SUBRESOURCE msr;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);
	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(GetImage().m_yuka));

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::SetStencilEnable(false);
	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

	Renderer::SetDepthEnable(true);
	
	Camera* camera =  Manager::GetScene()->GetGameObject<Camera>();
		if (camera != nullptr)
		{
			camera->Draw();
		}
}

void Polygon2D::Drawmap()
{
	/*
	for (int i = 0; i < 20; i++)
	{
		// ���̓��C�A�E�g�ݒ�
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		// �V�F�[�_�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		// �}�g���b�N�X�ݒ�
		Renderer::SetWorldViewProjection2D();
		// 2D�`��Ȃ̂Ő[�x����
		Renderer::SetDepthEnable(false);
		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;
		m_Scale = { 50.0f ,50.0f ,0 };
		m_Scale.x *= 0.5f;
		m_Scale.y *= 0.5f;
		// ���W�ϊ�
		float m_rot = 0.0f;
		XMFLOAT2 m_Pos = { 500,500 };
		pVtx[0].Position.x = i * 50 - m_Scale.x;
		pVtx[0].Position.y = 300 - m_Scale.y;
		pVtx[1].Position.x = i * 50 + m_Scale.x;
		pVtx[1].Position.y = 300 - m_Scale.x;
		pVtx[2].Position.x = i * 50 - m_Scale.x;
		pVtx[2].Position.y = 300 + m_Scale.x;
		pVtx[3].Position.x = i * 50 + m_Scale.x;
		pVtx[3].Position.y = 300 + m_Scale.x;

		pVtx[0].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		pVtx[1].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		pVtx[2].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		pVtx[3].Diffuse = { 1.0f,1.0f,1.0f,1.0f };

		pVtx[0].TexCoord = { 0.0f, 0.0f };
		pVtx[1].TexCoord = { 1.0f, 0.0f };
		pVtx[2].TexCoord = { 0.0f, 1.0f };
		pVtx[3].TexCoord = { 1.0f, 1.0f };

		pVtx[0].Normal = { 0.0f, 0.0f, -1.0f };
		pVtx[1].Normal = { 0.0f, 0.0f, -1.0f };
		pVtx[2].Normal = { 0.0f, 0.0f, -1.0f };
		pVtx[3].Normal = { 0.0f, 0.0f, -1.0f };


		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
		//�}�e���A���ݒ�
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		material.TextureEnable = true;
		Renderer::SetMaterial(material);
		// �e�N�X�`���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(GetImage().m_testimage));

		// �v���~�e�B�u�g�|���W�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);

		// 2D�`��Ȃ̂Ő[�x����
		Renderer::SetDepthEnable(true);
	}
	*/

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���b�N�X�ݒ�
	Renderer::SetWorldViewProjection2D();
	// 2D�`��Ȃ̂Ő[�x����
	Renderer::SetDepthEnable(false);
	// ���_�o�b�t�@�ւ̃|�C���^���擾
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;
	m_Scale = { 100.0f ,100.0f ,0 };
	m_Scale.x *= 0.5f;
	m_Scale.y *= 0.5f;
	// ���W�ϊ�
	float m_rot = 1.0f;
	XMFLOAT2 m_Pos = { 500,500 };
	pVtx[0].Position.x = (-m_Scale.x) * cosf(m_rot) - (-m_Scale.y) * sinf(m_rot) + m_Pos.x;
	pVtx[0].Position.y = (-m_Scale.x) * sinf(m_rot) + (-m_Scale.y) * cosf(m_rot) + m_Pos.y;
	pVtx[1].Position.x = (m_Scale.x) * cosf(m_rot) - (-m_Scale.y) * sinf(m_rot) + m_Pos.x;
	pVtx[1].Position.y = (m_Scale.x) * sinf(m_rot) + (-m_Scale.y) * cosf(m_rot) + m_Pos.y;
	pVtx[2].Position.x = (-m_Scale.x) * cosf(m_rot) - (m_Scale.y) * sinf(m_rot) + m_Pos.x;
	pVtx[2].Position.y = (-m_Scale.x) * sinf(m_rot) + (m_Scale.y) * cosf(m_rot) + m_Pos.y;
	pVtx[3].Position.x = (m_Scale.x) * cosf(m_rot) - (m_Scale.y) * sinf(m_rot) + m_Pos.x;
	pVtx[3].Position.y = (m_Scale.x) * sinf(m_rot) + (m_Scale.y) * cosf(m_rot) + m_Pos.y;

	pVtx[0].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	pVtx[1].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	pVtx[2].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	pVtx[3].Diffuse = { 1.0f,1.0f,1.0f,1.0f };

	pVtx[0].TexCoord = { 0.0f, 0.0f };
	pVtx[1].TexCoord = { 1.0f, 0.0f };
	pVtx[2].TexCoord = { 0.0f, 1.0f };
	pVtx[3].TexCoord = { 1.0f, 1.0f };

	pVtx[0].Normal = { 0.0f, 0.0f, -1.0f };
	pVtx[1].Normal = { 0.0f, 0.0f, -1.0f };
	pVtx[2].Normal = { 0.0f, 0.0f, -1.0f };
	pVtx[3].Normal = { 0.0f, 0.0f, -1.0f };


	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);
	// �e�N�X�`���ݒ�
//	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(GetImage().m_testimage));

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	//Renderer::GetDeviceContext()->Draw(4, 0);

	// 2D�`��Ȃ̂Ő[�x����
	Renderer::SetDepthEnable(true);

}
