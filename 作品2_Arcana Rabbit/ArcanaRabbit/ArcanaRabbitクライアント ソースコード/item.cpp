#include "item.h"

void Item::Init()
{
	m_skillCD = 0;
}

void Item::Update()
{
	if (m_skillCD > 0)
	{
		--m_skillCD;
	}
}
