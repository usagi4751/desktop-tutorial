#include "EnemyDataManager.h"
#include "showobjext.h"
std::vector<BaseEnemyData*> EnemyDataManager::m_ObjectList;
void EnemyDataManager::Init()
{
	BaseEnemyData* enemy = new BaseEnemyData;
	enemy->Init();
	enemy->GetShowObject()->SetObject("asset\\model\\rpg_enemy1_3.obj");
	enemy->GetShowObject()->SetScale({0.3f,0.3f,0.3f });
	m_ObjectList.push_back(enemy);
}

void EnemyDataManager::UnInit()
{
	for (BaseEnemyData* e : m_ObjectList)
	{
		e->Uninit();
		delete e;
	}
	m_ObjectList.clear();
}


void EnemyDataManager::Draw(int id, XMFLOAT3 pos, XMFLOAT3 rot)
{
	m_ObjectList[id]->Draw(pos,rot);
}
