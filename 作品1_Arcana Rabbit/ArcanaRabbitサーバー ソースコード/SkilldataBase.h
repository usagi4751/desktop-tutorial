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
	void TextBackground();//�e�L�X�g�̃o�b�N�O���E���h
	//===========================
	//��{�̃X�L���̕`��^
	//skillname �X�L���̖��O
	//skilldescription �X�L���̐����[�܂ōs���Ǝ����ŉ��s���Ă���鎩���ŃZ�b�g���\
	//===========================
	void NomalDraw(std::string skillname, std::string skilldescription);

};


