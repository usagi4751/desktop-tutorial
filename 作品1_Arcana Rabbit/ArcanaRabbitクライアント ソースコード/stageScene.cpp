#include "stageScene.h"
#include "main.h"
#include "polygon2D.h"
#include "polygon3D.h"
#include "camera.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "input.h"
#include "scene.h"
#include "manager.h"
#include "audio.h"
#include "timer.h"
#include "floor.h"
#include "showobjext.h"
void Stage1Scene::Init()
{
	AddObject<Camera>(0);
	AddObject<Floor>(0);
	AddObject<Field>(1);
	AddObject<Player>(1);
	ShowObject* field = AddObject<ShowObject>(1);
	field->SetPosition({ 150,-0.03f,250 });
	field->SetObject("asset\\model\\map3.obj");
	field->SetScale({ 10.0f,10.0f,10.0f });
	//AddObject<Polygon2D>(2);
	//AddObject<Timer>(2);

	//Enemy* enemy =  AddObject<Enemy>(1);
	//enemy->SetPosition({ 2.0f,0.01f,3.0f });
	//enemy->SetScale({ 10.0f,10.0f,10.0f });


}

void Stage1Scene::Uninit()
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


}

void Stage1Scene::Update()
{

	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Update();
		}
		m_gameObject[i].remove_if([](GameObject* object) {return object->Destoroy(); });
	}
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::setscene(2);
	}
}

void Stage1Scene::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Draw();
		}
	}

}
