#include "EnemyData.h"
#include "EnemyDataManager.h"
#include "UDP.h"
void EnemyData::Init()
{
}

void EnemyData::Uninit()
{
}

void EnemyData::Update()
{
	m_FreezeTime++;
}

void EnemyData::Draw()
{
	EnemyDataManager::Draw(m_Id, m_Position, m_Rotation);
}



void EnemyData::SetUUID(char* id)
{
	
	for (int i = 0; i < 32; i++)
	{
		m_Uuid[i] = id[i];
	}

}

char* EnemyData::GetUUID()
{
	return m_Uuid;
}

void EnemyData::AddDamage(float damage)
{
	std::string a = {};
	for (int i = 0; i < 32; i++)
	{
		a += m_Uuid[i];
	}
	a += std::to_string(damage);
	UDP::Send(2,  a);
}
