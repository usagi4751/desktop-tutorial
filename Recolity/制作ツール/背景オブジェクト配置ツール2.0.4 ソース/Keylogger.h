/*==============================================================================

	�L�[���͂̋L�^���� [keylogger.h]
														 Author : Youhei Sato
														 Date   : 2020/7/29
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

// �L�[���K�[�L�[�񋓌^
typedef enum KeyloggerKey_tag
{
	KL_FRONT, 
	KL_BACK,
	KL_LEFT,
	KL_RIGHT,
	KL_DOWN,
	KL_UP,
	KL_TURN_LEFT,
	KL_TURN_RIGHT,
	KL_TURN_UP,
	KL_TURN_DOWN,
	KL_ALT,
	KL_ATTACK,
	KL_DEBUG,
	KL_MAX
}KeyloggerKey;

// �L�[���K�[���W���[���̏�����
void Keylogger_Initialize(void);

// �L�[���K�[���W���[���̏I������
void Keylogger_Finalize(void);

// �L�[���K�[���W���[���̍X�V
void Keylogger_Update(void);

// �L�[���͏�Ԃ̎擾
//
// ����:
//
// �߂�l:������Ă�����true
//
bool Keylogger_Press(KeyloggerKey kl);

// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//
// ����:
//
// �߂�l:�������u�Ԃ�������true
//
bool Keylogger_Trigger(KeyloggerKey kl);

// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//
// ����:
//
// �߂�l:�������u�Ԃ�������true
//
bool Keylogger_Release(KeyloggerKey kl);


void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void keylogger_RecordLoad(void);
void keylogger_RecordPlay(void);
bool keylogger_IsRecordPlay(void);

#endif // KEYLOGGER_H