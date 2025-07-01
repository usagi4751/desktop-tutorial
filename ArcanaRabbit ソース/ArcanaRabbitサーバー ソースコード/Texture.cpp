/*==============================================================================

   �e�N�X�`���̓ǂݍ��� [texture.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "Texture.h"
/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/
#define MAX_TEXTURE_NUM 100

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
ID3D11ShaderResourceView*	g_pTexture[MAX_TEXTURE_NUM] = {};	//�e�N�X�`���z��
unsigned int g_TextureIndex = 0;					// �e�N�X�`���z��̖����������C���f�b�N�X
wchar_t g_TextureName[MAX_TEXTURE_NUM][256] = {};	// �e�N�X�`�����o�b�t�@

/*------------------------------------------------------------------------------
	�e�N�X�`���̓ǂݍ���
------------------------------------------------------------------------------*/
int LoadTexture(const wchar_t* fileName)
{
	//�ǂݍ��܂�Ă���e�N�X�`�����𒲂ׂāA�����̂��̂�
	//���łɓǂݍ��܂�Ă����炻�̔ԍ���Ԃ�
	for (unsigned int i = 0; i < g_TextureIndex; i++)
	{
		//�e�N�X�`�������r
		if (g_TextureName[i] ==fileName)
		{
			return i;
		}
	}

	//�ǂݍ��ݍő吔�𒴂��Ă����畉�̒l��Ԃ�
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return -1;
	}
	// �e�N�X�`���ǂݍ���
	TexMetadata metadata;
	ScratchImage image;
	HRESULT hr_load  = LoadFromWICFile(fileName, WIC_FLAGS_NONE, &metadata, image);
	HRESULT hr_shader =  CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &g_pTexture[g_TextureIndex]);
	assert(&g_pTexture[g_TextureIndex]);



	if (S_OK != hr_load)
	{
		//�ǂݍ��݂Ɏ��s�����ꍇ�A���̒l��Ԃ�
		return -1;
	}
	if (S_OK != hr_shader)
	{
		//�ǂݍ��݂Ɏ��s�����ꍇ�A���̒l��Ԃ�
		return -2;
	}
	//�ǂݍ��񂾃e�N�X�`������ۑ�����
	//strcpy_s(g_TextureName[g_TextureIndex], 256, fileName);
	wcscpy(g_TextureName[g_TextureIndex] , fileName);
	;
	int retIndex = g_TextureIndex;
	
	//�C���f�b�N�X����i�߂�
	g_TextureIndex++;

	return retIndex;

}

void UninitTexture(void)
{
	for (unsigned int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}



/*------------------------------------------------------------------------------
	�e�N�X�`���̃Q�b�^�[
------------------------------------------------------------------------------*/
ID3D11ShaderResourceView** GetTexture(int index)
{
	//index�̕s���l�`�F�b�N(���̒l)
	if (index < 0)
		return NULL;

	//index�̕s���l�`�F�b�N(�ő吔�I�[�o�[)
	if (index >= (int)g_TextureIndex)
		return NULL;

	return &g_pTexture[index];
}
