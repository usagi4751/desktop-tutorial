#include "ServerEnemy.h"
#include "ServerManager.h"
#include "ServerMember.h"
void ServerEnemy::SetUUID(char* uuid)
{
	for (int i = 0; i < 32; i++)
	{
		m_Uuid[i] = uuid[i];
	}

}

void ServerEnemy::Init()
{
	m_model = new ShowObject();
	m_model->Init();
	m_model->SetObject("asset\\model\\rpg_enemy1_3.obj");
	m_model->SetScale({ 0.3f,0.3f,0.3f });
	
}

void ServerEnemy::Uninit()
{
	m_model->Uninit();
	delete m_model;
}

void ServerEnemy::Update()
{

	//ƒvƒŒƒCƒ„[‚ğ’Ç‚¢‚©‚¯‚é
	int shortlength = -1;
	float lengh = 100;
	for (int i = 0; i < SERVERMAX; i++)
	{
		if (ServerManager::GetMember(i)->GetActive() == true)
		{
			XMFLOAT3 playerlen = { m_Position.x - ServerManager::GetMember(i)->GetPosition().x,
			m_Position.y - ServerManager::GetMember(i)->GetPosition().y ,
			m_Position.z - ServerManager::GetMember(i)->GetPosition().z };
			if (lengh > D3DXVec3LengthSq(&playerlen))
			{
				shortlength = i;
				lengh = D3DXVec3LengthSq(&playerlen);
			}
		}
	
	}
	if (shortlength > -1)
	{
		XMFLOAT2 a = { (ServerManager::GetMember(shortlength)->GetPosition().x - m_Position.x),(ServerManager::GetMember(shortlength)->GetPosition().z - m_Position.z) };
		float l2 = atan2(a.x, a.y);
		m_Rotation.y = l2;
		m_Position.x = m_Position.x + sinf(m_Rotation.y) * 0.03f;
		m_Position.z = m_Position.z + cosf(m_Rotation.y) * 0.03f;
	}

	m_model->SetPosition(m_Position);
	m_model->SetRotation(m_Rotation);
}

void ServerEnemy::Draw()
{
	m_model->Draw();
}
