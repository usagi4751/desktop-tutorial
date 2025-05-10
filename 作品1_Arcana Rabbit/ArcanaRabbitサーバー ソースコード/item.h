#pragma once

class Item
{
public:
	int m_ItemNo = 0;//アイテムのナンバー
	int m_ItemNum = 0;//アイテムの個数
	float m_damage = 0;//ダメージ
	float m_attackspeed = 0;//攻撃速度
	float m_def = 0;//防御力
	float m_maxhelth = 0;//最大体力
	float movespeed = 0;//移動速度
	int m_skillNo = -1;//スキルナンバー
	int m_skillCD = 0;//スキルクールタイム
	Item() {
	
	};
	virtual ~Item() {};
private:
	virtual void Init();
	virtual void Update();
	virtual Item GetItemData() { return *this; };
};

