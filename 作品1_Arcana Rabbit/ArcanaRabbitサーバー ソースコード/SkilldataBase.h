#pragma once
#include "main.h"
class SkillDataBase
{
public:
	SkillDataBase() {};
	virtual ~SkillDataBase() {};
	virtual void Draw() = 0;
	virtual void Use() = 0;
	virtual int CD() = 0;
	void TextBackground();//テキストのバックグラウンド
	//===========================
	//基本のスキルの描画型
	//skillname スキルの名前
	//skilldescription スキルの説明端まで行くと自動で改行してくれる自分でセットも可能
	//===========================
	void NomalDraw(std::string skillname, std::string skilldescription);

};


