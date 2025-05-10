#pragma once
#include "BaseEnemyData.h"
#include <list>
//=================================
// エネミーの表示機能・生成・管理するクラス
//=================================
class EnemyDataManager
{
private:
	static std::vector<BaseEnemyData*> m_ObjectList;

public:
	static void Init();
	static void UnInit();
	static void Draw(int id,XMFLOAT3 pos,XMFLOAT3 rot);


};


