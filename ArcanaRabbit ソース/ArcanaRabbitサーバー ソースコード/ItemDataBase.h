#pragma once
#include "main.h"
//�A�C�e���ŗL�̕\�����@����ʂ�\��

//������������ʒu
enum SetSlot
{
	None = 0,
	Head,
	Chest,
	LEGGINGS,
	BOOTS,
};
class Item;
struct Status;
class ItemDataBase
{
protected:
	int m_maxStack = 1;//�ő�X�^�b�N��
public:
	ItemDataBase() { };
	virtual ~ItemDataBase() {  };

	virtual void Attack(Item itemData) = 0;
	virtual void Use(Item* itemData) = 0;
	virtual void Draw(Item itemData) = 0;
	virtual void DrawIcon(XMFLOAT2 pos, float size, float Depth, Item itemData) = 0;
	virtual SetSlot GetSlot() { return None; };
	void TextBackground();//�e�L�X�g�̃o�b�N�O���E���h
	void NomalDrawText(std::string itemname, std::string itemdescription);//�ʏ�̕`��
	virtual std::string NomalStatus(Item itemData);
	virtual int GetMaxStack() { return m_maxStack; };//�߂�l�ő�X�^�b�N��
	virtual Status GetStatus(Item itemData);
};

