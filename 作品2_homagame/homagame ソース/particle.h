#pragma once
#define PAI 3.141593f
#define MAXPARTICLE 8192 
typedef struct {
	bool use;//�p�[�e�B�N�����g���Ă��邩 
	float time;//���ݎ��� 
	float lp;//[����]�p�[�e�B�N���̕\������ 
	int na;//�p�[�e�B�N���� 
	float posx;//[���W]x 
	float posy;//[���W]y 
	float sp;//[���x]�p�[�e�B�N���̑��� 
	float si;//[�T�C�Y] �p�[�e�B�N���̑傫�� 
	float di;//[����]0�`2�΂̕��� 
	float re;//[������]��C��R�̂悤�Ȃ��� 
	float we;//[�d��]�d�͂ŗ�������悤�ȍČ����� 
	float r;
	float g;
	float b;

}PARTICLE;	

//float dposx;//[�͈͍��W]x ���������Ƃ��ɂ΂�������邩 
//float dposy;//[�͈͍��W]y ���������Ƃ��ɂ΂�������邩 
//int nu;//[��]���������
//int mo;//[���[�h] �p�[�e�B�N���̍L������� 0�S���� 1������̂�
//float co;//[������]0�`180�� +-�ƂȂ�
//float lr;//[�\�����ԗ�]lp�̎��Ԃ��ς��
//float sir;//[�T�C�Y�̃����_��]0-1�ŃT�C�Y���ς��

void Initparticle(void);
void Uninitparticle(void);
void Updateparticle(void);
void Drawparticle(void);
void setparticle(
	int pa_na,
	float pa_x, float pa_y,   //�p�[�e�B�N�����W
	float pa_dx, float pa_dy,//�p�[�e�B�N���������W�͈�
	float pa_sp,//�p�[�e�B�N�����x
	int pa_nu,//�p�[�e�B�N��������
	float pa_si,//�T�C�Y
	//�����܂ł͏���
	float pa_di = -1.0f, //����
	float pa_co = -1.0f, //������
	float pa_re = -1.0f,//������
	float pa_we = -1.0f,//�d��
	float pa_lp = -1.0f,//����
	float pa_lr = -1.0f,//�\�����ԗ�
	float pa_spr = -1.0f,//�X�s�[�h�����_��
	float pa_sir = -1.0f,//�T�C�Y�����_��
	float pa_r = 1.0f,//�J���[R
	float pa_g = 1.0f,//�J���[G
	float pa_b = 1.0f//�J���[B
);
int Getparticletex(int n);
void clearparticleAll();


