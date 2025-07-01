#pragma once
#include "main.h"
#include <list>
#include "draw2d_Manager.h"
//===============================
// �v���C���[�̃C���x���g���̃N���X
// �X�e�[�^�X�̌v�Z�������ł���
//===============================
struct Status
{
	float MaxHelth;
	float Damage;
	float MoveSpeed;
	float AttackSpeed;
	float Def;
};
//�X�L���̕`��p
struct ItemSkillDraw {
	UI_Tex		m_ItemBg;
	UI_Text		m_ItemTextName;
	UI_Text		m_ItemTextdescription;

	UI_Tex		m_SkillBg;
	UI_Text		m_SkillTextName;
	UI_Text		m_SkillTextdescription;
};
class Item;
class Inventory
{
private:
	//=======================
	// �C���x���g��0-31 32�g
	// ���� 32-35 4�g
	//=======================
	static Item m_itemlist[36];
	static Item m_hand;//�J�[�\���ł܂�ł�A�C�e��
	static bool m_openflug;//�C���x���g�����󂢂Ă��邩
	static float m_posY;
	static float m_size;
	static int m_haveitem;//�����Ă鏊�̃i���o�[

	//�}�E�X���d�Ȃ��Ă���A�C�e���X���b�g�ԍ�
	static int Getitemno(XMFLOAT2 mousepos);

	//�`��p
	static bool m_ShowUI;

	static UI_Tex m_HotBerCell[8];
	static UI_Tex m_Cell[36];
	static UI_Tex m_Bg;
	static UI_Tex m_Celect;
	static UI_Tex m_SkillText;
	static UI_Tex m_CellOnMouse;
	static UI_Tex m_Hand;

	static UI_Tex m_HotBerCellItem[8];
	static UI_Tex m_CellItem[36];

	static ItemSkillDraw m_ItemTextDraw;
public:
	//������
	static void Init();
	//�X�V
	static void Update();
	//�`��
	static void DrawRect();

	//���ݎ����Ă���A�C�e���X���b�g�ԍ�
	static void SetHaveItem(int hand) {m_haveitem = hand;};
	//�C���x���g���̑傫��
	static void SetScale(float size) { m_size = size; };
	//�C���x���g���̍���
	static void SetYpos(float posy) { m_posY = posy; };
	//�C���x���g���̃X�e�[�^�X�̍��v�l
	static Status GetStayus();


	//================================
	//�v���C���[�̎g�p����R�}���h
	//================================

	//�A�C�e���ōU��
	static void Attack();
	//�A�C�e���̎g�p
	static void Use();
	//�A�C�e���̎擾
	static void Getitem(Item getitem) ;
	//�C���x���g���̃I�[�v���N���[�Y
	static void SetOpen(bool flug) { m_openflug = flug; };


	//================================
	// �ǂݍ��݂⃀�[�r�[���ɃC���x���g���̃��b�N���|����@�\
	//================================

	//�C���x���g��������\��
	static void ShowUI(bool flug);
};


