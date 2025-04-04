#include "SkilldataBase.h"
#include "material.h"
void SkillDataBase::TextBackground()
{
	//Draw2d::SetUI(GetImage().m_UI_image3, { 1.0f,1.0f ,1.0f ,1.0f }, { 270,820 }, { 450,360 }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, 0.5f);
}

void SkillDataBase::NomalDraw(std::string skillname, std::string skilldescription)
{
	TextBackground();
	//Draw2d::SetText(skillname, { 55,660,490,710 }, 25, { 1.0f,0.0f,1.0f,1.0f }, 0.5f + 0.01f);
	//Draw2d::SetText(skilldescription, { 55,715,490,1000 }, 15, { 1.0f,1.0f,1.0f,1.0f }, 0.5f + 0.01f);
}
