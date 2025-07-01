/*==============================================================================

   ���_�Ǘ�[polygon.h]
   �C���x���g����}�b�v�̕`��Ȃǂ�����
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void DrawPolygon2(void);
//�E�B���h�E�Ƀe�L�X�g��\������
void SetText(std::string settext, float X, float Y, float size, float r = 1.0f, float g = 1.0f, float b = 1.0f, float z = 1.0f, int font = 0);

D3DXVECTOR2 Getcamera();
D3DXVECTOR2 Getcorsor();
//�_���[�W�̕\��
void SetDamage(float damage, D3DXVECTOR2 pos//x y
	, D3DXCOLOR coler//r,g,b,a�̃J���[
	, int type//�t�H���g
	,int vel//�_���[�W�̃e�L�X�g�����ł�������
);
typedef struct {
	bool open;//�J���Ă��邩
	int page;//�K�w�y�[�W
	int dangionselect;//�I��ł�_���W����
	int dangionpage;//�_���W�����y�[�W
}PORTAL;
int haveitem();
bool gettabopen();//�C���x���g�����J���Ă邩
bool shopbopen();//�V���b�v���Ђ炢�Ă��邩
D3DXVECTOR2 GetNowcorsor();
void GetItem(WEAPONITEM n);
int GetItemtex(int n);
std::string Getskillname(int n);//�X�L���̖��O���擾
int Getskillct(int n);//�X�L���̃N�[���^�C��
int* shopmoder();
int* shopppage();
int* shoppclect();
bool* craftpopen();
int* craftpcelct();
int* craftppage();
PORTAL* pGetportal();
std::string Getdangiongame(int n);
void clearPorigon();
int Getstageflag(int n, int m);
int Getbgmvol();