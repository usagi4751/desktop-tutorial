//==========================================
// �f�o�b�O�p�̃I�u�W�F�N�g���̕\������������
//==========================================
#include "main.h"
#include "renderer.h"
#include "polygon3D.h"
#include "manager.h"
#include "player.h"
#include "floor.h"
void Field::Init() {

	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);;
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);;

	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(0.0f,0.0f,1.0f);
	vertex[0].Normal = XMFLOAT3(0.0f,1.0f,0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 0.0f, 1.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd,sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���ǂݍ���
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\yuka.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");


}
void Field::Uninit() {

	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}
void Field::Update() {

	if (on == false)
	{
		on = true;
		m_player = Manager::GetScene()->GetGameObject<Player>();
		m_floor = Manager::GetScene()->GetGameObject<Floor>();

	}

}
void Field::Draw() {
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	int xpos = m_player->GetPosition()->x ;
	int zpos = m_player->GetPosition()->z ;
	if (xpos < 0)
	{
		xpos = 0;
	}
	if (xpos > 511)
	{
		xpos = 511;
	}
	if (zpos < 0)
	{
		zpos = 0;
	}
	if (zpos > 511)
	{
		zpos = 511;
	}

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			if (xpos - 30 <= i && xpos + 30 >= i &&
				zpos - 30 <= j && zpos + 30 >= j)//����ꏊ����+-30
		
			{

				if (m_floor->GetFloor({(float)i, (float)j}))//�t���A����������`��
				{
			
					//���[���h�}�g���b�N�X�ݒ�
					XMMATRIX world, scale, rot, trans;
					scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
					rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.x);
					trans = XMMatrixTranslation((float)i, 0.0f, (float)j );
					world = scale * rot * trans;
					Renderer::SetWorldMatrix(world);

					// ���_�o�b�t�@�ݒ�
					UINT stride = sizeof(VERTEX_3D);
					UINT offset = 0;
					Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

					// �|���S���`��
					Renderer::GetDeviceContext()->Draw(4, 0);
				}
				
			}
			
		}
	}
	
}