#pragma once
#include "main.h"
class SkillDataBase
{
public:
	SkillDataBase() {};
	virtual ~SkillDataBase() {};
	virtual void Use() = 0;
	virtual int CD() = 0;

	virtual void GetSkillTextData(std::string* name , std::string* description);

};


