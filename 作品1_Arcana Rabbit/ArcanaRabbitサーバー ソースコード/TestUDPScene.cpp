#include "TestUDPScene.h"
#include "main.h"
#include "player.h"
#include "camera.h"
#include "TextBox.h"
#include "TextForm.h"
#include "input.h"
#include "Buttun.h"
#include "enemy.h"
#include "showobjext.h"
#include "ServerManager.h"
#include "DummyMember.h"
void TestUDPScene::Init()
{

	AddObject<Camera>(0);
	Player* player =  AddObject<Player>(1);
	player->SetPosition({ 0,35,15 });
	player->SetRotation({ -1.3,XM_PI,0 });
	//Enemy* enemy = AddObject<Enemy>(1);
	ShowObject* field = AddObject<ShowObject>(1);
	field->SetPosition({ 0,-0.03f,0 });
	field->SetObject("asset\\model\\map1_3\\map1_3.obj");
	field->SetScale({ 1.3f,1.3f, 1.3f });
	float sc = 0.35f;
	//enemy->SetScale({ sc,sc,sc });
	ServerManager::CreateEnemy(0, 10, {}, {});
	for (int i = 0; i <20; i++)
	{
		m_DummyMember[i] = AddObject<DummyMember>(1);
		m_DummyMember[i]->SetPosition({ 0,0,0 });
		m_DummyMember[i]->SetScale({ 0.35f,0.35f, 0.35f });
	}
	

}

void TestUDPScene::Uninit()
{
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Uninit();
			delete gameobject;
		}
		m_gameObject[i].clear();
	}
	MouseClip(false);

}
void TestUDPScene::Update()
{
	if (Input::GetKeyTrigger('7'))
	{
		ServerManager::CreateEnemy(0, 10, {}, {});
	}
	for (int i = 0; i < 20; i++)
	{
		if (ServerManager::GetMember(i)->GetActive() == true)
		{
			m_DummyMember[i]->SetPosition(ServerManager::GetMember(i)->GetPosition());
			m_DummyMember[i]->SetRotation({0.0f,ServerManager::GetMember(i)-> GetRotate(),0});
		}
	
	}

	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Update();
		}
		m_gameObject[i].remove_if([](GameObject* object) {return object->Destoroy(); });
	}
	
}

void TestUDPScene::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Draw();
			if (i == 1)
			{
				for (ServerEnemy* e : *ServerManager::GetEnemyList())
				{
					e->Draw();
				}
			}
		}
	}
	
}
