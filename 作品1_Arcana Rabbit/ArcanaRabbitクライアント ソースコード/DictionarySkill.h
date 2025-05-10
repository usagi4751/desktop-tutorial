#pragma once
#include "main.h"
//�V���O���g��
//�X�L���̔ԍ��ŌĂяo����
//�Q�[���J�n���ɃX�L���𐶐�����

class SkillDataBase;
class DictionarySkill
{
private:
	static std::vector<SkillDataBase*> m_Skilldata;
	
	DictionarySkill();
public:

	~DictionarySkill() {};
	static void UnInit();//UnInit�����Q�[���I�����ɂP�x�̂݌Ă�
	static void Init();//Init�����Q�[���J�n���ɂP�x�̂݌Ă�
	static SkillDataBase* GetSkill(int index) {
		if (index > (int)m_Skilldata.size() - 1 || index < 0)
		{
			return nullptr;
		}
		return m_Skilldata[index]; 
	};


};

