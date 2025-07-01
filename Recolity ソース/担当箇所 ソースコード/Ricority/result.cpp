//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : 
//
//=============================================================================
#include <map>
#include "result.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "material.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
std::map<std::string, Button> g_ResultButton;
D3DXVECTOR2 g_ResultMousePos;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	g_ResultButton.emplace("�^�C�g��", Button({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT - 300 }, { 500,150 }));

	PlaySound("menu", -1, 1.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	g_ResultButton.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	//�J�[�\���̍��W�擾
	g_ResultMousePos = GetMousePos();

	if (g_ResultButton.at("�^�C�g��").IsPush(g_ResultMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_TITLE);

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_TITLE);
	}
#endif // _DEBUG
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	UI ui = UI{ {0.0f,0.0f},{SCREEN_WIDTH, SCREEN_HEIGHT},{0.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},0.0f };
	DrawScreenLT(ui, RefImageMaterial().m_BackGround);

	//�^�C�g���{�^��
	ui = UI{ g_ResultButton.at("�^�C�g��").RefPos(),g_ResultButton.at("�^�C�g��").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_ResultButton.at("�^�C�g��").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Title);

	//�^�C�g���{�^��
	ui = UI{ {SCREEN_WIDTH * 0.5f, 400.0f},{519.0f,308.0f}
		,{0.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},0.0f };
	DrawScreen(ui, RefImageMaterial().m_StageClear);

	//�J�[�\��
	ui = UI{ g_ResultMousePos,{50,50},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Reticle);
}
