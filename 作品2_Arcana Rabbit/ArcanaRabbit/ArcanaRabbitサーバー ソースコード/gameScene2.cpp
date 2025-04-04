#include "gameScene2.h"
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
void gameScene2::Init()
{
	AddObject<Camera>(0);
	Floor* floor = AddObject<Floor>(0);
	Player* player = AddObject<Player>(1);
	ShowObject* field = AddObject<ShowObject>(1);
	Dropitem* item = AddObject<Dropitem>(1);
	item->SetPosition({ 141.0f,0.0f,106.0f });
	Item dropitem = {};
	dropitem.m_ItemNo = 1;
	dropitem.m_ItemNum = 1;
	dropitem.m_damage = 2;
	dropitem.m_def = 0;
	dropitem.m_maxhelth = 0;
	dropitem.movespeed = 0;
	dropitem.m_attackspeed = 0;
	dropitem.m_skillCD = 0;
	dropitem.m_skillNo = 0;
	item->Setitem(dropitem);
	field->SetPosition({ 150,-0.03f,250 });
	field->SetObject("asset\\model\\stage2.obj");
	field->SetScale({ 10.0f,10.0f,10.0f });
	player->SetPosition({ 143, 0, 206 });

	//ステージの読み込み

	const char* MapFilePath = "asset/stagedata/floor/stage2.txt";  // 保存先ファイルパス

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


	//AddObject<Polygon2D>(2);
	//AddObject<Timer>(2);




}

void gameScene2::Uninit()
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

void gameScene2::Update()
{
	std::list< Enemy*> enemylist = GetEntitylist<Enemy>();
	if (enemylist.size() < 1)
	{
		Floor* fror = GetGameObject<Floor>();
		XMFLOAT2 pos = { frand() * 512 , frand() * 512 };
		if (fror->GetFloor(pos) == true)
		{
			Enemy* enemy = AddObject<Enemy>(1);
			enemy->SetPosition({ pos.x, 0, pos.y });
			enemy->SetScale({ 0.01f,0.01f,0.01f });
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
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::setscene(3);
	}
	if (fade > 0)
	{
		fade -= 0.03f;
	}
	if (fadeout > 0)
	{
		fadeout += 0.01f;
	}
	if (fadeout >= 1.0f)
	{
		Manager::setscene(3);
	}
	//148 292
	Player* player = GetGameObject<Player>();
	XMFLOAT3 playeros = *player->GetPosition();
	XMFLOAT3 teloportpos = { 147 - playeros.x ,0, 292 - playeros.z };
	if (D3DXVec3LengthSq(&teloportpos) < 9)
	{
		Manager::GetScene()->fadein();
	}
}


void gameScene2::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Draw();
		}
	}
	//Draw2d::SetUI(GetImage().m_fade, { 1.0f,1.0f,1.0f,fade }, { 960,540 }, { 1920,1080 }, {}, { 1.0f,1.0f }, {}, 0, 10000);
}
