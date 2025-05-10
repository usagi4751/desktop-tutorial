//=============================================================================
//
// ���j���[��ʏ��� [menu.cpp]
// Author : 
//
//=============================================================================
#include "menu.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "material.h"
#include "button.h"
#include "title.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
std::map<std::string, Button> g_MenuButton;
D3DXVECTOR2 g_MenuMousePos;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMenu(void)
{
	//�{�^���̓o�^
	g_MenuButton.emplace("�X�e�[�W", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.25f }, { 500,150 }));
	g_MenuButton.emplace("�^�C�g��", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.5f }, { 500,150 }));
	g_MenuButton.emplace("�f�b�L", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.75f }, { 500,150 }));

	ResumeSound("menu");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMenu(void)
{
	g_MenuButton.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMenu(void)
{
	//�J�[�\���̍��W�擾
	g_MenuMousePos = GetMousePos();

	//�{�^�����Ƃ̏���
	if (g_MenuButton.at("�X�e�[�W").IsPush(g_MenuMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_STAGE);
	if (g_MenuButton.at("�^�C�g��").IsPush(g_MenuMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_TITLE);
	if (g_MenuButton.at("�f�b�L").IsPush(g_MenuMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_DECK);

#ifdef _DEBUG
	//�f�o�b�N�p�V�[���J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SceneTransition(SCENE_GAME);
	}
#endif // _DEBUG
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMenu(void)
{
	//�w�i
	UI ui = UI{ {0.0f,0.0f},{SCREEN_WIDTH, SCREEN_HEIGHT},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreenLT(ui, RefImageMaterial().m_BackGround);

	//�Q�[���{�^��
	ui = UI{ g_MenuButton.at("�X�e�[�W").RefPos(),g_MenuButton.at("�X�e�[�W").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuButton.at("�X�e�[�W").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Stage);

	//�^�C�g���{�^��
	ui = UI{ g_MenuButton.at("�^�C�g��").RefPos(),g_MenuButton.at("�^�C�g��").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuButton.at("�^�C�g��").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Title);

	//�f�b�L�{�^��
	ui = UI{ g_MenuButton.at("�f�b�L").RefPos(),g_MenuButton.at("�f�b�L").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuButton.at("�f�b�L").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Deck);

	//�J�[�\��
	ui = UI{ g_MenuMousePos,{50,50},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Reticle);
}