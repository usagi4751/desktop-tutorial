#include "DrawName.h"
#include "renderer.h"
#include "material.h"
#include "manager.h"
#include "camera.h"
#include "scene.h"
#include "Texture.h"
void DrawName::Init()
{
	VERTEX_3D vertex[4 * 12];

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4 * 12;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
}

void DrawName::UnInit()
{
}
void DrawName::Draw(XMFLOAT3 pos)
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�J�����̃r���[�}�g���b�N�X�擾
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewmatrix();


	//�r���[�̋t�s��
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	//���[���h�}�g���b�N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.x);
	trans = XMMatrixTranslation(pos.x, pos.y, pos.z);
	world = scale * invView * trans;
	Renderer::SetWorldMatrix(world);


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
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(GetImage().m_Mozi));

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Renderer::SetAlphaTestEnable(true);
	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4 * 12, 0);

	//	//���e�X�g��L����
	Renderer::SetAlphaTestEnable(false);
}
void DrawName::SetName(std::string name)
{

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	float stringsize = name.size();
	if (stringsize > 12)
	{
		stringsize = 12;
	}
	float drawsize = 0.10f;
	
	for (int i = 0; i < 12; i++)
	{
		
		float x = 0;
		float y = 0;
		if (stringsize > i)
		{
			x= (name.at(i) - 32) % 16 * 0.0624f;
			y= (name.at(i) - 32) / 16 * 0.16665f;
		}
		
		vertex[0 + i * 4].Position = XMFLOAT3(-drawsize * 0.5f * stringsize + (float)i * drawsize, drawsize, 0.0f);
		vertex[0 + i * 4].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[0 + i * 4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0 + i * 4].TexCoord = XMFLOAT2(x, y);

		vertex[1 + i * 4].Position = XMFLOAT3(-drawsize * 0.5f * stringsize + (float)(i + 1)*drawsize, drawsize, 0.0f);
		vertex[1+ i * 4].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1+ i * 4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1+ i * 4].TexCoord = XMFLOAT2(x + 0.0624f, y);

		vertex[2+ i * 4].Position = XMFLOAT3(-drawsize * 0.5f * stringsize + (float)i * drawsize, -drawsize, 0.0f);
		vertex[2+ i * 4].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2+ i * 4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2+ i * 4].TexCoord = XMFLOAT2(x, y + 0.16665f);

		vertex[3+ i * 4].Position = XMFLOAT3(-drawsize * 0.5f * stringsize + (float)(i + 1) * drawsize, -drawsize, 0.0f);
		vertex[3+ i * 4].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3+ i * 4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3+ i * 4].TexCoord = XMFLOAT2(x + 0.0624f, y + 0.16665f);

		if (i > stringsize)
		{
			vertex[0 + i * 4].Position = XMFLOAT3(0, 1.0f, 0.0f);
			vertex[1 + i * 4].Position = XMFLOAT3(0, 1.0f, 0.0f);
			vertex[2 + i * 4].Position = XMFLOAT3(0, 1.0f, 0.0f);
			vertex[3 + i * 4].Position = XMFLOAT3(0, 1.0f, 0.0f);
		}
	}
	

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
}


