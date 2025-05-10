#pragma once
#include "SkilldataBase.h"
class Fireball : public SkillDataBase
{
private:

public:
	Fireball() {};
	virtual ~Fireball() {};
	virtual void Use() ;
	virtual int CD();
	void GetSkillTextData(std::string* name, std::string* description) override;
};

