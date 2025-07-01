//=============================================================================
//
// �X�e�[�W�I�����j���[��ʏ��� [menu_stage.cpp]
// Author : 
//
//=============================================================================
#include "menu_stage.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "material.h"
#include "button.h"
#include "text.h"
#include "camera.h"
#include"Game.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
std::map<std::string, Button> g_MenuStageButton;
D3DXVECTOR2 g_MenuStageMousePos;
int g_Loopanime = 0;
int g_stageSound;
int g_maneCrick;
int ManePressTimer = 0;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitMenuStage(void)
{
	g_Loopanime = 0;
	//�{�^���̓o�^
	g_MenuStageButton.emplace("�X�^�[�g", Button({ SCREEN_WIDTH * 0.25f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.33f }, BASE_BUTTTON_SIZE));
	g_MenuStageButton.emplace("���j���[", Button({ SCREEN_WIDTH * 0.75f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.33f }, BASE_BUTTTON_SIZE));
	g_MenuStageButton.emplace("�`���[�g���A��", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.7f }, {567.0f * 0.6f,128.0f * 0.6f }));
	g_MenuStageButton.emplace("�X�e�[�W1", Button({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.5f }, {428.0f * 0.6f,154.0f * 0.6f }));
	//g_MenuStageButton.emplace("�X�e�[�W2", Button({ SCREEN_WIDTH * 0.6f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.5f }, { 428.0f * 0.6f,154.0f * 0.6f }));

	g_MenuStageButton.emplace("EASY", Button({ SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.45f }, { 588.0f * 0.3f,275.0f * 0.3f }));
	g_MenuStageButton.emplace("NOMAL", Button({ SCREEN_WIDTH * 0.825f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.55f }, { 588.0f * 0.45f,275.0f * 0.3f }));
	g_MenuStageButton.emplace("HARD", Button({ SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT - SCREEN_HEIGHT * 0.65f }, { 588.0f * 0.3f,275.0f * 0.3f }));

	g_maneCrick = LoadSound("bottun2");
	g_stageSound =  LoadSound("bottun1");
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMenuStage(void)
{
	g_MenuStageButton.clear();
	StopSound(g_maneCrick);
	StopSound(g_stageSound);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMenuStage(void)
{
	if (IsMouseLeftPressed())
	{
		ManePressTimer++;
	}
	if (!IsMouseLeftPressed())
	{
		ManePressTimer = 0;
	}
	g_Loopanime++;
	//�J�[�\���̍��W�擾
	g_MenuStageMousePos = GetMousePos();

	//�{�^�����Ƃ̏���
	if (g_MenuStageButton.at("�X�^�[�g").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered())) {
		PuaseSound("menu");
		SceneTransition(SCENE_GAME);
	}
	if (g_MenuStageButton.at("���j���[").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered()))
		SceneTransition(SCENE_MENU);
	//�{�^�����Ƃ̏���
	if (g_MenuStageButton.at("�`���[�g���A��").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered())) {
		PlaySound(g_stageSound, 0, 1.0f);
		SetStageScelect(Tutorial);
	}
		
	if (g_MenuStageButton.at("�X�e�[�W1").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered()))
	{
		PlaySound(g_stageSound, 0, 1.0f);
		SetStageScelect(Stage1);
	}
	//if (g_MenuStageButton.at("�X�e�[�W2").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered()))
	//{
	//	PlaySound(g_stageSound, 0, 1.0f);
	//	SetStageScelect(Stage2);
	//}
	
	if (g_MenuStageButton.at("EASY").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered()))
	{
		PlaySound(g_stageSound, 0, 1.0f);
		SetGamemode(Easy);
	}
		
	if (g_MenuStageButton.at("NOMAL").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered()))
	{
		PlaySound(g_stageSound, 0, 1.0f);
		SetGamemode(Nomal);
	}
		
	if (g_MenuStageButton.at("HARD").IsPush(g_MenuStageMousePos, IsMouseLeftTriggered()))
	{
		PlaySound(g_stageSound, 0, 1.0f);
		SetGamemode(Hard);
	}
	float plusx = 650.0f;
	float plusy = -600.0f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//poseui.m_Rot = D3DX_PI * (float)i + D3DX_PI;
			//poseui.m_Pos = { (float)i * 160.0f + 450.0f,(float)j * 40.0f + 750.0f };
			if (GetMousePos().x > (float)i * 160.0f + 450.0f - 32.0f + plusx * 1.46f &&
				GetMousePos().x < (float)i * 160.0f + 450.0f + 32.0f + plusx * 1.46f &&
				GetMousePos().y >(float)j * 40.0f + 650.0f - 20.0f  + plusy &&
				GetMousePos().y < (float)j * 40.0f + 650.0f + 20.0f+ plusy &&
				IsMouseLeftTriggered())
			{
				if (j == 0)
				{
					SetVolumeAll(GetWolrdSound() - 0.01f + i * 0.02f);
				}
				if (j == 1)
				{
					SetVolumeKinds("SE", GetSESound() - 0.01f + i * 0.02f);
				}
				if (j == 2)
				{
					SetVolumeKinds("BGM", GetBGMSound() - 0.01f + i * 0.02f);
				}
				if (j == 3)
				{
					*GetMouseKando() += -0.1f + (float)i * 0.2f;
				}

				PlaySound(g_maneCrick, 0, 1.0f);
			}
			if (ManePressTimer > 15 && ManePressTimer % 6 == 0 &&
				GetMousePos().x > (float)i * 160.0f + 450.0f - 32.0f + plusx * 1.46f &&
				GetMousePos().x < (float)i * 160.0f + 450.0f + 32.0f + plusx * 1.46f &&
				GetMousePos().y >(float)j * 40.0f + 650.0f - 20.0f + plusy &&
				GetMousePos().y < (float)j * 40.0f + 650.0f + 20.0f+ plusy
				)
			{
				if (j == 0)
				{
					SetVolumeAll(GetWolrdSound() - 0.01f + i * 0.02f);
				}
				if (j == 1)
				{
					SetVolumeKinds("SE", GetSESound() - 0.01f + i * 0.02f);
				}
				if (j == 2)
				{
					SetVolumeKinds("BGM", GetBGMSound() - 0.01f + i * 0.02f);
				}
				if (j == 3)
				{
					*GetMouseKando() += -0.1f + (float)i * 0.2f;
				}

				PlaySound(g_maneCrick, 0, 1.0f);
			}
		}
	}

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
void DrawMenuStage(void)
{
	//�w�i
	UI ui = UI{ {0.0f,0.0f},{SCREEN_WIDTH, SCREEN_HEIGHT},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreenLT(ui, RefImageMaterial().m_BackGround);

	//�X�^�[�g�{�^��
	ui = UI{ g_MenuStageButton.at("�X�^�[�g").RefPos(),g_MenuStageButton.at("�X�^�[�g").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("�X�^�[�g").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Start);

	//���j���[�{�^��
	ui = UI{ g_MenuStageButton.at("���j���[").RefPos(),g_MenuStageButton.at("���j���[").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("���j���[").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Button_Menu);



	//�X�e�[�W�Z���N�g�{�^�� �`���[�g���A��
	ui = UI{ g_MenuStageButton.at("�`���[�g���A��").RefPos(),g_MenuStageButton.at("�`���[�g���A��").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("�`���[�g���A��").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Tutorial);

	//�X�e�[�W�Z���N�g�{�^�� �`���[�g���A��
	ui = UI{ g_MenuStageButton.at("�X�e�[�W1").RefPos(),g_MenuStageButton.at("�X�e�[�W1").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("�X�e�[�W1").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_Stage_1);
	//�X�e�[�W�Z���N�g�{�^�� �`���[�g���A��
	//ui = UI{ g_MenuStageButton.at("�X�e�[�W2").RefPos(),g_MenuStageButton.at("�X�e�[�W2").RefSize()
	//	,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("�X�e�[�W2").RefColor(),0.0f };
	//DrawScreen(ui, RefImageMaterial().m_Stage_2);


	//��Փx�I��
	ui = UI{ g_MenuStageButton.at("EASY").RefPos(),g_MenuStageButton.at("EASY").RefSize()
		,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("EASY").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_EasyIcon);
	ui = UI{ g_MenuStageButton.at("NOMAL").RefPos(),g_MenuStageButton.at("NOMAL").RefSize()
	,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("NOMAL").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_NomalIcon);
	ui = UI{ g_MenuStageButton.at("HARD").RefPos(),g_MenuStageButton.at("HARD").RefSize()
	,{0.0f,0.0f},{1.0f,1.0f},g_MenuStageButton.at("HARD").RefColor(),0.0f };
	DrawScreen(ui, RefImageMaterial().m_HardIcon);

	UI poseui;
	float plusx = 650.0f;
	float plusy = -600.0f;
	poseui.m_Color = { 1.0f,1.0f ,1.0f ,1.0f };
	poseui.m_Pos = { 800 + plusx,SCREEN_CENTER_Y - 100 + plusy };
	poseui.m_Uv_v = { 0.0f,0.0f };
	poseui.m_Uv_f = { 1.0f,1.0f };
	poseui.m_Scl = { 300.0f * 1.5f,512.0f * 1.5f };
	poseui.m_Rot = 0.0f;
	SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 200.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "�S�̉���");
	SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 240.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "���ʉ���");
	SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 280.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "BGM");
	SetText({ poseui.m_Pos.x - 190.0f,poseui.m_Pos.y + 320.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, "���_���x");

	SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 200.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(GetWolrdSound() * 100.0f)));
	SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 240.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(GetSESound() * 100.0f)));
	SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 280.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(GetBGMSound() * 100.0f)));
	SetText({ poseui.m_Pos.x + 15.0f,poseui.m_Pos.y + 320.0f,SCREEN_WIDTH,SCREEN_HEIGHT }, std::to_string((int)(*GetMouseKando() * 10.0f)));
	poseui.m_Scl = { 64,40 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			poseui.m_Rot = D3DX_PI * (float)i + D3DX_PI;
			poseui.m_Pos = { (float)i * 160.0f + 450.0f+ plusx * 1.46f ,(float)j * 40.0f + 650.0f  + plusy };
			DrawScreen(poseui, RefImageMaterial().m_SoundUi2);
			DrawScreen(poseui, RefImageMaterial().m_SoundUi1);
		}
	}

	D3DXVECTOR2 uipos = g_MenuStageButton.at("EASY").RefPos();
	uipos.y -= ((int)GetGamemode() ) * 108.0f;
	uipos.x -= 150.0f + sinf((float)g_Loopanime * 0.1f) * 5.0f;
	ui = UI{ uipos,{120,120}
,{(float)((int)((float)g_Loopanime / 5.0f) % 4 * 0.25f) ,((float)((int)((float)g_Loopanime / 5.0f) /4) * 0.5f)},{0.25f,0.5f},{1.0f,1.0f,1.0f,1.0f},0.0f };
	DrawScreen(ui, RefImageMaterial().ScelectAneme);

	//�J�[�\��
	ui = UI{ g_MenuStageMousePos,{50,50},{0.0f,0.0f},{1.0f,1.0f},DIK_COLER_WHITE,0.0f };
	DrawScreen(ui, RefImageMaterial().m_Reticle);
}