#pragma once
#include "main.h"
#include "draw2d_Manager.h"
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
private:

protected:
	int m_maxStack = 1;//�ő�X�^�b�N��
public:
	ItemDataBase() {};
	virtual ~ItemDataBase() {  };

	virtual void Attack(Item itemData) = 0;
	virtual void Use(Item* itemData) = 0;
	virtual int GetIcon() = 0;
	virtual void GetItemName(Item itemData,std::string* itemname, std::string* itemdescription, std::string* skillname, std::string* skilldescription) = 0;

	virtual SetSlot GetSlot() { return None; };
	void TextBackground();//�e�L�X�g�̃o�b�N�O���E���h
	void NomalDrawText(std::string itemname, std::string itemdescription);//�ʏ�̕`��
	virtual std::string NomalStatus(Item itemData);
	virtual int GetMaxStack() { return m_maxStack; };//�߂�l�ő�X�^�b�N��
	virtual Status GetStatus(Item itemData);
};

