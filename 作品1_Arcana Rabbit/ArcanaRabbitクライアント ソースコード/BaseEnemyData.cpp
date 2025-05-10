#include "BaseEnemyData.h"

void BaseEnemyData::Init()
{
	m_Model = new ShowObject;
	m_Model->Init();
}

void BaseEnemyData::Uninit()
{
	
	m_Model->Uninit();
	delete m_Model;
}

void BaseEnemyData::Update()
{
	m_Model->Update();
}

void BaseEnemyData::Draw( XMFLOAT3 pos, XMFLOAT3 rot)
{
	m_Model->SetPosition(pos);
	m_Model->SetRotation(rot);
	m_Model->Draw();
}
