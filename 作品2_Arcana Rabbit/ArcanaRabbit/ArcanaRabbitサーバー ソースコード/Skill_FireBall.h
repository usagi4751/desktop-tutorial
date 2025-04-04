#pragma once
#include "SkilldataBase.h"
class Fireball : public SkillDataBase
{
private:

public:
	Fireball() {};
	virtual ~Fireball() {};
	virtual void Draw() ;
	virtual void Use() ;
	virtual int CD();
};

