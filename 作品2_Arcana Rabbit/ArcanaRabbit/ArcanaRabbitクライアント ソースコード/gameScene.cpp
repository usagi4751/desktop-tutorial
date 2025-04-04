#include "gameScene.h"
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
#include "material.h"
#include "dropitem.h"
#include "Emitterportal.h"
#include "meshField.h"
#include "shadowVolume.h"
#include "UDPManager.h"
#include "UDP.h"
#include "TextBox.h"
void gameScene::Init()
{
	AddObject<Camera>(0);
	Floor* floor = AddObject<Floor>(0);//床の当たり判定
	AddObject<Field>(1);//床の当たり判定
	AddObject<TextBox>(2);

	//AddObject<meshField>(1);

	AddObject<ShadowVolume>(1)->SetPosition({ 0.0f,0.0f,0.0f });;

	AddObject<Polygon2D>(1);

	Player* player = AddObject<Player>(1);


	ShowObject* field = AddObject<ShowObject>(1);
	field->SetPosition({ 14,-0.03f,0 });
	field->SetObject("asset\\model\\map1_3\\map1_3.obj");
	field->SetScale({ 1.3f,1.3f, 1.3f });


	ShowObject* field2 = AddObject<ShowObject>(1);
	field2->SetPosition({ 105,-0.03f,0 });
	field2->SetObject("asset\\model\\stage2.obj");
	field2->SetScale({ 6.0f,6.0f, 6.0f });

	ShowObject* portal = AddObject<ShowObject>(1);
	portal->SetPosition({ -14,-0.03f,-17 });
	portal->SetObject("asset\\model\\map1_portal\\map1_portal.obj");
	portal->SetScale({ 1.0f,1.0f, 1.0f });

	ShowObject* ie = AddObject<ShowObject>(1);
	ie->SetPosition({ -2,-0.03f,15 });
	ie->SetObject("asset\\model\\map1_ie\\map1_ie.obj");
	ie->SetRotation({ 0.0f,XM_PI * 1.5f,0.0f });
	ie->SetScale({ 1.2f,1.2f, 1.2f });

	ShowObject* ie2 = AddObject<ShowObject>(1);
	ie2->SetPosition({ 6,-0.03f,-7 });
	ie2->SetObject("asset\\model\\map1_2ie\\map1_2ie.obj");
	ie2->SetRotation({ 0.0f,-1.1,0.0f });
	ie2->SetScale({ 0.9f,0.9f, 0.9f });

	ShowObject* ie3 = AddObject<ShowObject>(1);
	ie3->SetPosition({ 13.5f,-0.03f,-10.5 });
	ie3->SetObject("asset\\model\\map1_3ie\\map1_3ie.obj");
	ie3->SetRotation({ 0.0f,-1.1,0.0f });
	ie3->SetScale({ 0.9f,0.9f, 0.9f });

	ShowObject* ie4 = AddObject<ShowObject>(1);
	ie4->SetPosition({ 30,-0.03f,0 });
	ie4->SetObject("asset\\model\\map1_ie\\map1_ie.obj");
	ie4->SetRotation({ 0.0f,XM_PI * 1.7f,0.0f });
	ie4->SetScale({ 1.2f,1.2f, 1.2f });

	ShowObject* ki[16];
	for (int i = 0; i < 16; i++)
	{
		ki[i] = AddObject<ShowObject>(1);
		ki[i]->SetObject("asset\\model\\ki\\map1_ki.obj");
		ki[i]->SetRotation({ 0.0f,2.7f,0.0f });
		ki[i]->SetScale({ 0.2f,0.2f, 0.2f });
	}
	ki[0]->SetPosition({ -20.5,1,-12 });
	ki[1]->SetPosition({ 37,1,-8 });
	ki[2]->SetPosition({ 36,1,-15 });
	ki[3]->SetPosition({ 23,1,-30 });
	ki[4]->SetPosition({ 18,1,16 });
	ki[5]->SetPosition({ -3,1,-7 });
	ki[6]->SetPosition({ -1.3,1,-13 });
	ki[7]->SetPosition({ -5.5,1,-19.3 });
	ki[8]->SetPosition({ -9.3,1,-27.5 });
	ki[9]->SetPosition({ -14.5,1,-30 });
	ki[10]->SetPosition({ -21.5,1,29.5 });
	ki[11]->SetPosition({ -23.5,1,-23.5 });
	ki[12]->SetPosition({ -24.5,1,-16 });
	ki[13]->SetPosition({ -25,1,-11 });
	ki[14]->SetPosition({ -19,1,-4 });
	ki[15]->SetPosition({ -18,1,-5.5 });
	



	//ステージの読み込み
	{
		const char* MapFilePath = "asset/stagedata/floor/stage1.txt";  // 保存先ファイルパス

		std::ifstream inputFile(MapFilePath);
		std::string line;
		if (inputFile.is_open())
		{
			while (std::getline(inputFile, line))
			{

			}
			inputFile.close();

		}

		std::string loadlen[512];
		for (int i = 0; i < 512; i++)
		{
			loadlen[i] = line.substr(86 * i, 86);
			float ind = 0;
			for (char a : loadlen[i])
			{
				//頭まで引く
				int num = a;
				num = num - 0x30;
				if ((int)ind < 85)
				{
					if (num > 31)
					{
						num -= 32;
						floor->SetFloor({ ind * 6.0f + 5 ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f + 5 ,(float)i }, false);
					}

					if (num > 15)
					{
						num -= 16;
						floor->SetFloor({ ind * 6.0f + 4 ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f + 4 ,(float)i }, false);
					}

					if (num > 7)
					{
						num -= 8;
						floor->SetFloor({ ind * 6.0f + 3 ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f + 3 ,(float)i }, false);
					}

					if (num > 3)
					{
						num -= 4;
						floor->SetFloor({ ind * 6.0f + 2 ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f + 2 ,(float)i }, false);
					}

					if (num > 1)
					{
						num -= 2;
						floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, false);
					}

					if (num > 0)
					{
						num -= 1;
						floor->SetFloor({ ind * 6.0f ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f ,(float)i }, false);
					}
				}
				else
				{
					if (num > 1)
					{
						num -= 2;
						floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, false);
					}

					if (num > 0)
					{
						num -= 1;
						floor->SetFloor({ ind * 6.0f ,(float)i }, true);
					}
					else
					{
						floor->SetFloor({ ind * 6.0f ,(float)i }, false);
					}
				}
				ind++;
			}
		}
	}


	
}

void gameScene::Uninit()
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

void gameScene::Update()
{
	if (UDP::AccessFlug())
	{

		XMFLOAT3 playerpos = *Manager::GetScene()->GetGameObject<Player>()->GetPosition();
		float rot = Manager::GetScene()->GetGameObject<Player>()->GetRot().y;
		std::string send = {};
		send += std::to_string(playerpos.x) + " ";
		send += std::to_string(playerpos.y) + " ";
		send += std::to_string(playerpos.z) + " ";
		send += std::to_string(rot) + " ";
		UDP::Send(1, send);
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

void gameScene::Draw()
{
	for (int i = 0; i < 3; i++)
	{
 		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Draw();
			if (i == 1)
			{
				Manager::GetUdpManager()->Draw();
			}
		}
	}

}


