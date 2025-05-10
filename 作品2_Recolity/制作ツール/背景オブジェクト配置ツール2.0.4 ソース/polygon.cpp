//=============================================================================
//
// �|���S���\������ [polygon.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "texture.h"
#include "font.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��

#define	SIZE_X			(100.0f)					// �n�ʂ̃T�C�Y(X����)
#define	SIZE_Y			(100.0f)					// �n�ʂ̃T�C�Y(Y����)
#define	SIZE_Z			(100.0f)					// �n�ʂ̃T�C�Y(Z����)

#define POLYGON_NUM 10000
DirectWrite* g_Write[5];
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPolygon(void);
void toVertex(int index);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���

static POLYGON						g_Polygon[POLYGON_NUM];			// �|���S���f�[�^
static VERTEX_3D					g_VertexArray[POLYGON_NUM * 4];
static int							g_TexNo;			// �e�N�X�`���ԍ�
static int							g_VertexIndex;			// �e�N�X�`���ԍ�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{
	int index = 0;
	float xpos = SIZE_X * (POLYGON_NUM / 100 / 2) * -1;
	float zpos = SIZE_Z * (POLYGON_NUM / 100 / 2);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			g_Polygon[index].pos = D3DXVECTOR3(xpos + SIZE_X * j, 0.0f, SIZE_Z - SIZE_Z * i);
			index++;
		}
	}

	g_VertexIndex = 0;
	for (int i = 0; i < POLYGON_NUM; i++)
	{
		toVertex(i);
	}

	// ���_�o�b�t�@�̍쐬
	MakeVertexPolygon();

	// �e�N�X�`������
	g_TexNo = LoadTexture((char*)"data/TEXTURE/yuka.png");


	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < POLYGON_NUM; i++)
	{
		g_Polygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Polygon[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Polygon[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}


	//�t�H���g�f�[�^�̏�����
	
	FontData* fodata[5];
		for (int i = 0; i < 5; i++)
		{
			fodata[i] = new  FontData();
		}

	for (int i = 0; i < 5; i++)
	{
		fodata[i]->fontSize = 10 + i * 5;
		fodata[i]->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
		g_Write[i] = new DirectWrite(fodata[i]);
		g_Write[i]->TextInit();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	CAMERA *cam = GetCamera();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon_Field(void)
{
	//// ���_�o�b�t�@�ݒ�
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	//// �v���~�e�B�u�g�|���W�ݒ�
	//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// �e�N�X�`���ݒ�
	//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	//D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//for (int i = 0; i < POLYGON_NUM; i++)
	//{
	//	// ���[���h�}�g���b�N�X�̏�����
	//	D3DXMatrixIdentity(&g_Polygon[i].mtxWorld);

	//	// �X�P�[���𔽉f
	//	D3DXMatrixScaling(&mtxScl, g_Polygon[i].scl.x, g_Polygon[i].scl.y, g_Polygon[i].scl.z);
	//	D3DXMatrixMultiply(&g_Polygon[i].mtxWorld, &g_Polygon[i].mtxWorld, &mtxScl);

	//	// ��]�𔽉f
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Polygon[i].rot.y, g_Polygon[i].rot.x , g_Polygon[i].rot.z);
	//	D3DXMatrixMultiply(&g_Polygon[i].mtxWorld, &g_Polygon[i].mtxWorld, &mtxRot);

	//	// �ړ��𔽉f
	//	/*D3DXMatrixTranslation(&mtxTranslate, g_Polygon[i].pos.x, g_Polygon[i].pos.y, g_Polygon[i].pos.z);
	//	D3DXMatrixMultiply(&g_Polygon[i].mtxWorld, &g_Polygon[i].mtxWorld, &mtxTranslate);*/

	//	// ���[���h�}�g���b�N�X�̐ݒ�
	//	SetWorldMatrix(&g_Polygon[i].mtxWorld);

	//	// �|���S���`��
	//	GetDeviceContext()->Draw(4, i * 4);
	//}
}
HRESULT MakeVertexPolygon(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;;
	bd.ByteWidth = sizeof(VERTEX_3D) * POLYGON_NUM * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// �O���[�o���̒��_�z�񂩂璸�_�o�b�t�@������
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_VertexArray;

	GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	return S_OK;
}

void toVertex(int index)
{
	//�|�W�V����
	g_VertexArray[g_VertexIndex + 0].Position = D3DXVECTOR3(g_Polygon[index].pos.x - (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z + (SIZE_Z / 2));
	g_VertexArray[g_VertexIndex + 1].Position = D3DXVECTOR3(g_Polygon[index].pos.x + (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z + (SIZE_Z / 2));
	g_VertexArray[g_VertexIndex + 2].Position = D3DXVECTOR3(g_Polygon[index].pos.x - (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z - (SIZE_Z / 2));
	g_VertexArray[g_VertexIndex + 3].Position = D3DXVECTOR3(g_Polygon[index].pos.x + (SIZE_X / 2), 0.0f, g_Polygon[index].pos.z - (SIZE_Z / 2));

	//�@���E�J���[
	for (int i = 0; i < 4; i++)
	{
		g_VertexArray[g_VertexIndex + i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_VertexArray[g_VertexIndex + i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	g_VertexArray[g_VertexIndex + 0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	g_VertexArray[g_VertexIndex + 1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	g_VertexArray[g_VertexIndex + 2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	g_VertexArray[g_VertexIndex + 3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	g_VertexIndex += 4;
}
void SetText(std::string text, D3DXVECTOR2 pos, Textsize size) {

	switch (size)
	{
	case TextSc_1:g_Write[0]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_2:g_Write[1]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_3:g_Write[2]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_4:g_Write[3]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	case TextSc_5:g_Write[4]->DrawString(text, { pos.x,pos.y,SCREEN_WIDTH,SCREEN_HEIGHT }, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		break;
	default:
		break;
	}
	
}