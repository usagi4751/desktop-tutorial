/*==============================================================================

	�L�[���͂̋L�^���� [keylogger.cpp]
														 Author : Youhei Sato
														 Date   : 2020/7/29
--------------------------------------------------------------------------------

==============================================================================*/

#define _CRT_SECURE_NO_WARNINGS

#include "Keylogger.h"
#include "keyboard.h"


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
typedef unsigned long KeyloggerType;
static KeyloggerType g_CurrentKeyState = 0; // ���̃t���[���ł̃L�[�̏�ԕێ��p
static KeyloggerType g_PrevKeyState    = 0; // �O�t���[���ł̃L�[��ԕێ��p
static KeyloggerType g_TriggerKeyState = 0; // �g���K�[��Ԃ̊m�F�p
static KeyloggerType g_ReleaseKeyState = 0; // �����[�X��Ԃ̊m�F�p

static int g_KeyloggerMode = 0; // 0 - �ʏ� 1 - �L�^ 2 - �Đ�
static KeyloggerType* g_pRecordCurrentData = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0; //


// �L�[���K�[�L�[����L�[�{�[�h�L�[�ւ̕ϊ��\
static const Keyboard_Keys g_KKs[KL_MAX] = {
	KK_W,
	KK_S,
	KK_A,
	KK_D,
	KK_Q,
	KK_E,
	KK_LEFT,
	KK_RIGHT,
	KK_UP,
	KK_DOWN,
	KK_LEFTALT,
	KK_SPACE,
	KK_D0
};


// �L�[���K�[���W���[���̏�����
void Keylogger_Initialize(void)
{
	g_CurrentKeyState = 0;
	g_PrevKeyState    = 0;
	g_TriggerKeyState = 0;
	g_ReleaseKeyState = 0;

	g_KeyloggerMode = 0;
	g_pRecordCurrentData = NULL;
	g_RecordFrame = 0;
	g_RecordPlayFrame = 0;
	g_RecordFrameMax = 0;//
}

// �L�[���K�[���W���[���̏I������
void Keylogger_Finalize(void)
{
	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}

// �L�[���K�[���W���[���̍X�V
void Keylogger_Update(void)
{
	// �O�t���[���̃L�[��Ԃ�ۑ����Ă���
	g_PrevKeyState = g_CurrentKeyState;
	
	// �L�[���K�[���[�h�ɂ���ē���ύX

	if (g_KeyloggerMode <= 1) {

		g_CurrentKeyState = 0;

		// �L�[���K�[�L�[�̏�Ԏ擾
		for (int i = 0; i < KL_MAX; i++) {

			if (Keyboard_IsKeyDown(g_KKs[i])) {
				g_CurrentKeyState |= 1u << i;
			}
		}

		// �L�[�L�^���[�h
		if (g_KeyloggerMode == 1) {
			if (g_RecordFrame < g_RecordFrameMax) {
				g_pRecordCurrentData[g_RecordFrame] = g_CurrentKeyState;
				g_RecordFrame++;
			}
		}
	}
	else {
		// �Đ����[�h

		// ���S���u�i�L�^�t���[�������������Đ����悤�Ƃ����j
		if (g_RecordPlayFrame < g_RecordFrame) {
			g_CurrentKeyState = g_pRecordCurrentData[g_RecordPlayFrame++];
		}
		else {
			g_CurrentKeyState = 0;
			g_KeyloggerMode = 0; // 0...���ʃ��[�h
		}

		// g_CurrentKeyState = g_RecordPlayFrame < g_RecordFrame ? g_pRecordCurrentData[g_RecordPlayFrame++] : 0;
	}

	// �������u�ԂƗ������u�Ԃ̃L�[���擾
	g_TriggerKeyState = (g_PrevKeyState ^ g_CurrentKeyState) & g_CurrentKeyState;
	g_ReleaseKeyState = (g_PrevKeyState ^ g_CurrentKeyState) & g_PrevKeyState;
}

// �L�[���͏�Ԃ̎擾
//
// ����:
//
// �߂�l:������Ă�����true
//
bool Keylogger_Press(KeyloggerKey kl)
{
	return g_CurrentKeyState & (1u << kl);
}

// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//
// ����:
//
// �߂�l:�������u�Ԃ�������true
//
bool Keylogger_Trigger(KeyloggerKey kl)
{
	return g_TriggerKeyState & (1u << kl);
}

// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//
// ����:
//
// �߂�l:�������u�Ԃ�������true
//
bool Keylogger_Release(KeyloggerKey kl)
{
	return g_ReleaseKeyState & (1u << kl);
}

void Keylogger_RecordStart(int frame_max)
{
	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
	}

	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType) * frame_max);
	g_KeyloggerMode = 1; // 1...�L�^���[�h
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;
}

void Keylogger_RecordEnd(void)
{
	if (!g_pRecordCurrentData) {
		return;
	}

	FILE* fp = fopen("keylogger.dat", "wb");
	// �t�@�C���̐擪�Ƀf�[�^�ʂ��L�^
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	// �t�@�C���փf�[�^��ۑ�
	fwrite(g_pRecordCurrentData, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);

	g_KeyloggerMode = 0; // ���ʃ��[�h

	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}

void keylogger_RecordLoad(void)
{
	FILE* fp = fopen("keylogger.dat", "rb");
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);

	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
	}
	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType) * g_RecordFrame);
	
	fread(g_pRecordCurrentData, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);
}

void keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyloggerMode = 2; // 2...�Đ����[�h
}

bool keylogger_IsRecordPlay(void)
{
	if (g_KeyloggerMode == 2) {
		return true;
	}

	return false;
}
