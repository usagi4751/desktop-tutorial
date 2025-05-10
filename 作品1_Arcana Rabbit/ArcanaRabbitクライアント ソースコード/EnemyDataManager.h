#pragma once
#include "BaseEnemyData.h"
#include <list>
//=================================
// �G�l�~�[�̕\���@�\�E�����E�Ǘ�����N���X
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


