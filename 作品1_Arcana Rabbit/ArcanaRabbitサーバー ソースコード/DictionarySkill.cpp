#include "DictionarySkill.h"
#include "SkilldataBase.h"
#include "Skill_FireBall.h"
std::vector<SkillDataBase*> DictionarySkill::m_Skilldata{};



void DictionarySkill::Init()
{
	//�����ŃX�L����ǉ�����
	m_Skilldata.push_back(new Fireball);
}

void DictionarySkill::UnInit()
{
	for (SkillDataBase* b : m_Skilldata)
	{
		delete b;
	}
	m_Skilldata.clear();
}


