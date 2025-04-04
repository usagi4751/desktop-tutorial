#include "UDPManager.h"
#include "UDP.h"
#include "manager.h"

void UDPManager::Init()
{
	UDP::Link(&m_MassagePool);
	UDP::LinkChat(&m_ChatData);
	for (int i = 0; i < 20; i++)
	{
		m_Member[i].Init();
	}
	
}

void UDPManager::UnInit()
{
	for (EnemyData* e :  m_EnemyData)
	{
		e->Uninit();
		delete e;
	}
	m_EnemyData.clear();
	for (int i = 0; i < 20; i++)
	{
		m_Member[i].Uninit();
	}
}

void UDPManager::Update()
{
	for (std::string t : m_MassagePool) {
		if (t.at(0) == 2)
		{
			XMFLOAT3 pos = {};
			float rot = 0;
			int next = 2;
			int old = next;
			next = t.find(' ', old);
			int len = next - old;
			pos.x = std::stof(t.substr(old, len).c_str());
			old = next;
			next = t.find(' ', old + 1);
			len = next - old;
			pos.y = std::stof(t.substr(old, len).c_str());
			old = next;
			next = t.find(' ', old + 1);
			len = next - old;
			pos.z = std::stof(t.substr(old, len).c_str());
			old = next;
			next = t.find(' ', old + 1);
			len = next - old;
			rot = std::stof(t.substr(old, len).c_str());
			m_Member[t.at(1) - 1].SetPosition(pos);
			m_Member[t.at(1) - 1].SetRotation({XM_PIDIV2,rot,0});
		}

		if (t.at(0) == 3)
		{
			m_Member[t.at(1) - 1].SetActive(true);
				
		}
		if (t.at(0) == 4)
		{
			m_Member[t.at(1) - 1].SetActive(false);

		}
		if (t.at(0) == 5)
		{
			std::string name = t.substr(2);
			m_Member[t.at(1) - 1].SetName(name);
		}
		if (t.at(0) == 6)
		{
			m_ChatData += t.substr(1);
			m_ChatData += "\n";
		}
		if (t.at(0) == 7)
		{
			char		uuid[32];
			bool		searchflug = false;//入ってきたデータで同じUUIDがあったか
			int			id;
			XMFLOAT3	pos = {};
			float		rot = 0;
			id = t.at(1) -1;
			{
				int next = 34;
				int old = next;
				next = t.find(' ', old);
				int len = next - old;
				pos.x = std::stof(t.substr(old, len).c_str());
				old = next;
				next = t.find(' ', old + 1);
				len = next - old;
				pos.y = std::stof(t.substr(old, len).c_str());
				old = next;
				next = t.find(' ', old + 1);
				len = next - old;
				pos.z = std::stof(t.substr(old, len).c_str());
				old = next;
				next = t.find(' ', old + 1);
				len = next - old;
				rot = std::stof(t.substr(old, len).c_str());
			}

			for (int i = 0; i < 32; i++)
			{
				uuid[i] = t.at(2 + i);
			}
			for (EnemyData* e : m_EnemyData) {
				searchflug = true;
				for (int i = 0; i < 32; i++)
				{
					if (e->GetUUID()[i] != uuid[i])
					{
						searchflug = false;
					}
				}
				if(searchflug == true)
				{
					e->SetID(id);
					e->SetPosition(pos);
					e->SetRotation({ 0.0f,rot,0.0f });
				}
			}
			if (searchflug == false)
			{
				EnemyData* enemy = new EnemyData;
				enemy->SetID(id);
				enemy->SetUUID(uuid);
				enemy->SetPosition(pos);
				enemy->SetRotation({0.0f,rot,0.0f});
				m_EnemyData.push_back(enemy);
			}
		}
		if (t.at(0) == 8)
		{
			char		uuid[32];
			bool		searchflug = false;//入ってきたデータで同じUUIDがあったか
			for (int i = 0; i < 32; i++)
			{
				uuid[i] = t.at(2 + i);
			}
			for (EnemyData* e : m_EnemyData) {
				searchflug = false;
				for (int i = 0; i < 32; i++)
				{
					if (e->GetUUID()[i] != uuid[i])
					{
						searchflug = true;
					}
				}
				if (searchflug == true)
				{
					e->SetDeth();
				}
			}
		
		}
	}

	for (EnemyData* e : m_EnemyData) {
		e->Update();
	}
	m_EnemyData.remove_if([](EnemyData* e) {if (e->GetDestory()) {
 		e->Uninit();
	}
	return e->GetDestory(); });
	m_MassagePool.clear();
}

void UDPManager::Draw()
{
	for (int i = 0; i < 20; i++)
	{
		if (UDP::GetMyIndex() -1 != i)
		{
			m_Member[i].Draw();
		}

	}
	for (EnemyData* e : m_EnemyData) {
		e->Draw();
	}
}
