#include "result.h"
#include "main.h"
#include "polygon2D.h"
#include "polygon3D.h"
#include "camera.h"
#include "player.h"
#include "manager.h"
#include "bullet.h"
#include "input.h"
#include "scene.h"
#include "material.h"
void resultScene::Init()
{
	AddObject<Camera>(0);
}

void resultScene::Uninit()
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

void resultScene::Update()
{
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Update();
		}
		m_gameObject[i].remove_if([](GameObject* object) {return object->Destoroy(); });
	}
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Manager::setscene(0);
	}

}

void resultScene::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Draw();
		}
	}
	//Draw2d::SetText("ステージクリア", { 0,0,1500,500 }, 100, { 0.0f,0.0f ,0.0f ,1.0f }, 0.3f);
	//Draw2d::SetText("スペースを押してタイトルに戻る", { 500,900,10000,10000 }, 50, { 1.0f,1.0f ,1.0f ,1.0f }, 0.3f);
	//Draw2d::SetUI(GetImage().m_UI_image6, { 1.0f,1.0f,1.0f,1.0f }, { 960,540 }, { 1920,1080 }, {}, { 1.0f,1.0f }, {}, 0, 0.2f);
}
