#pragma once
typedef struct {
	bool            use;//���̃q�b�g�{�b�N�X���g���Ă��邩
	D3DXVECTOR2     pos;//�q�b�g�{�b�N�X�̃|�W�V�����A�G���e�B�e�B�̒��S��0:0�ƂȂ�
	D3DXVECTOR2     size;//�q�b�g�{�b�N�X�̃T�C�Y
	int             type;//��_���ʂȂǂ�����
}HITBOX;
void Inithitbox(void);
void Drawhitbox(void);
