#include "titleScene.h"
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
#include "showobjext.h"
#include "Emitterbezier.h"
#include "particleInterface.h"
#include "renderer.h"
#include "scene.h"
#include "audio.h"
#include "Emitterbrast.h"
#include "inventory.h"
#include "Buttun.h"
#include "TextBox.h"
#include "TextForm.h"
#include "UDP.h"
//切替
bool swic =false;
void titleScene::Init()
{
	Inventory::ShowUI(false);
	m_audio = new Audio(nullptr);
	((Audio*)m_audio)->Load("asset\\sound\\Time_limit.wav");
	((Audio*)m_audio)->Play(true);
	m_camera = AddObject<Camera>(0);
	m_camera->SetPosition({ 26,6,-23 } );
	if (swic == true)
	{
	Player* player = AddObject<Player>(1);
	player->SetPosition({26,0.0f,-23});
	player->SetRotation({ 0.0f,XM_2PI,0.0f });
	}
	ParticleInerface::SetEmitter(new EmitterBrast({ -14,-0.03f,-20 }, {}));
	ShowObject* field = AddObject<ShowObject>(1);
	field->SetPosition({ 14,-0.03f,0 });
	field->SetObject("asset\\model\\map1_3\\map1_3.obj");
	field->SetScale({ 1.3f,1.3f, 1.3f });


	ShowObject* field2 = AddObject<ShowObject>(1);
	field2->SetPosition({105,-0.03f,0 });
	field2->SetObject("asset\\model\\stage2.obj");
	field2->SetScale({6.0f,6.0f, 6.0f});

	ShowObject* portal = AddObject<ShowObject>(1);
	portal->SetPosition({ -14,-0.03f,-17 });
	portal->SetObject("asset\\model\\map1_portal\\map1_portal.obj");
	portal->SetScale({ 1.0f,1.0f, 1.0f });

	ShowObject* ie = AddObject<ShowObject>(1);
	ie->SetPosition({ -2,-0.03f,15});
	ie->SetObject("asset\\model\\map1_ie\\map1_ie.obj");
	ie->SetRotation({0.0f,XM_PI * 1.5f,0.0f});
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
	ki[1]->SetPosition({37,1,-8 });
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

	m_fade.Link(Draw2D_Manager::AddUI());
	m_fade.SetScale({1920,1080});
	m_fade.SetPosition({960,540});
	m_fade.SetColer({0.0f,0.0f ,0.0f ,0.0f });
	m_fade.SetDepth(1000);


	m_PortFormText.Link(Draw2D_Manager::AddTEXT());
	m_PortFormText.SetRect({ 550,380,900,420 });
	m_PortFormText.SetText("IPアドレス");
	m_PortFormText.SetColer({ 1.0f,1.0f,1.0f,1.0f });

	m_NameFormText.Link(Draw2D_Manager::AddTEXT());
	m_NameFormText.SetRect({ 550,480,900,520 });
	m_NameFormText.SetText("名前");
	m_NameFormText.SetColer({ 1.0f,1.0f,1.0f,1.0f });

	m_PasswordFormText.Link(Draw2D_Manager::AddTEXT());
	m_PasswordFormText.SetRect({ 550,580,900,620 });
	m_PasswordFormText.SetText("パスワード");
	m_PasswordFormText.SetColer({ 1.0f,1.0f,1.0f,1.0f });

	m_StartButtun = new Buttun;
	m_StartButtun->SetPosition({ SCREEN_WIDTH * 0.5f + 350,400 });
	m_StartButtun->SetScale({ 200,200 });
	m_StartButtun->SetDepth(2.0f + 0.02f);


	m_NameForm = AddObject<TextForm>(2);
	m_NameForm->CloseTextBox();
	m_NameForm->SetScale({ 400.0f,40.0f,0 });
	m_NameForm->SetPosition({ SCREEN_WIDTH * 0.5f,500,0 });
	m_NameForm->SetColer({ 0.7f,0.7f ,0.7f ,1.0f });
	m_NameForm->SetTextSetting(NOMULTI);

	m_PasswordForm = AddObject<TextForm>(2);
	m_PasswordForm->CloseTextBox();
	m_PasswordForm->SetScale({ 400.0f,40.0f,0 });
	m_PasswordForm->SetPosition({ SCREEN_WIDTH * 0.5f,600,0 });
	m_PasswordForm->SetColer({ 0.7f,0.7f ,0.7f ,1.0f });
	m_PasswordForm->SetTextSetting(NOMULTI);
	


	m_IpAddressForm = AddObject<TextForm>(2);
	m_IpAddressForm->CloseTextBox();
	m_IpAddressForm->SetScale({ 400.0f,40.0f,0 });
	m_IpAddressForm->SetPosition({ SCREEN_WIDTH * 0.5f,400,0 });
	m_IpAddressForm->SetColer({ 0.7f,0.7f ,0.7f ,1.0f });
	m_IpAddressForm->SetTextSetting(NOMULTI);


	

	//const char* M = "asset/stagedata/floor/stage.txt";
	const char* M = "asset/logindata.txt";
	std::ifstream inputFile(M);
	std::string line;
	if (inputFile.is_open())
	{
		std::getline(inputFile, line);
		m_IpAddressForm->SetText("localhost");
		std::getline(inputFile, line);
		m_NameForm->SetText(line);
		std::getline(inputFile, line);
		m_PasswordForm->SetText(line);
		inputFile.close();

	}
	else {
		line = " error";
	}
	//ベジェ曲線
	{
		const int pointMAX = 4;
		XMFLOAT2 point[]{
			{41,-20},
			{50,-02},
			{-14,14},
			{-14,-15},
		};
		XMFLOAT2		ControlPoint[4][pointMAX];		// 制御点
		// ポイントの初期化
		for (int i = 0; i < pointMAX; i++) {
			ControlPoint[0][i].x = point[i].x;		// 制御点(= [0][*])を初期化
			ControlPoint[0][i].y = point[i].y;
		}
		//16
		int		i, j, k, p;
		int qua = 100;
		int Qty = 100;

		// 全フレームにおけるベジェ曲線上のポイントを計算
		for (k = 0; k <= Qty; k++) {
			p = qua * k / Qty;
			// ３次なので３回
			for (i = 1; i <= 3; i++)
			{
				for (j = 0; j < pointMAX - i; j++)
				{
					ControlPoint[i][j].x = ((qua - p) * ControlPoint[i - 1][j].x + p * ControlPoint[i - 1][j + 1].x) / qua;
					ControlPoint[i][j].y = ((qua - p) * ControlPoint[i - 1][j].y + p * ControlPoint[i - 1][j + 1].y) / qua;
				}
			}
			// ０次の時の点を記憶
			BezierPoint[k].x = ControlPoint[3][0].x;
			BezierPoint[k].y = ControlPoint[3][0].y;
		}
	}
}

void titleScene::Uninit()
{
	m_StartButtun->Uninit();
	delete m_StartButtun;
	m_audio->UnInit();
	((Audio*)m_audio)->Uninit();
	delete m_audio;
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Uninit();
			delete gameobject;
		}
		m_gameObject[i].clear();
	}
	
	
	Draw2D_Manager::DeleateUI(m_PortFormText.GetObjectData());
	Draw2D_Manager::DeleateUI(m_NameFormText.GetObjectData());
	Draw2D_Manager::DeleateUI(m_fade.GetObjectData());
	Inventory::ShowUI(true);
}
float timer = 0;
void titleScene::Update()
{


	if (Input::IsMouseLeftTriggered() && m_IpAddressForm->OnMouseButtun())
	{
		m_IpAddressForm->OpenTextBox();
	}
	if (Input::IsMouseLeftTriggered() && m_NameForm->OnMouseButtun())
	{
		m_NameForm->OpenTextBox();
	}
	if (Input::IsMouseLeftTriggered() && m_StartButtun->OnMouseButtun())
	{
		UDP::SetIPAddress(*m_IpAddressForm->GetText());
		UDP::SetPort(4751);
		UDP::SetName(*m_NameForm->GetText());
		if (UDP::ServerAccess() == true)
		{
			std::ofstream ofs("asset/LoginData.txt");
			if (ofs.is_open())
			{
				std::string name;
				name = "usagin\n";
				std::string serveraddress = "localhost\n";

				std::string password = "1234\n";


				ofs << serveraddress + name + password;
				ofs.close();
			}
		}
	
		fade += 0.01f;
	}

	if (m_effectfade > 0)
	{
		m_effectfade += 0.01f;
		if (sinf(m_effectfade) >= 0.99)
		{
			m_camera->SetPosition({ 70 ,6 - m_stagetime * 0.1f,7 });
			m_camera->settarget({ 74,5 ,7 });
			m_stagetime += 0.01f;
			m_bezitime = 0;
		}
		if (sinf(m_effectfade) < 0)
		{
			m_camera->settarget({ 5,0,0 });
			m_effectfade = 0;
			
		
		}
	}
	if (m_townnomaltime > 0)
	{
		m_townnomaltime +=0.002f;
	}
	if (m_stagetime > 0)
	{
		m_stagetime += 0.002f;
	}
	if (m_bezitime > 0)
	{
		m_bezitime += 0.1f;
	}
	
	XMFLOAT2 bezi;
	if (m_bezitime > 97)
	{
		
		m_bezitime = 97;
		m_effectfade += 0.01f;
	}
	if (m_townnomaltime > XM_PIDIV2)
	{
		m_townnomaltime = 0;
		m_bezitime += 0.01f;
	}
	if (m_stagetime > XM_PIDIV2)
	{
		m_stagetime = 0;
		m_townnomaltime += 0.01f;
	}
	int be_1 = (int)m_bezitime;
	int be_2 = (int)m_bezitime + 1;
	if (be_2 > 97)
	{
		be_2 = 0;
	}
	float be_di = m_bezitime - (float)be_1;//b

	XMFLOAT2 dipoint;
	dipoint.x =   BezierPoint[be_2].x - BezierPoint[be_1].x;
	dipoint.y =   BezierPoint[be_2].y - BezierPoint[be_1].y;

	bezi.x = BezierPoint[be_1].x + dipoint.x * be_di;
	bezi.y = BezierPoint[be_1].y + dipoint.y * be_di;


	
	if (swic == false && m_bezitime > 0)
	{
		m_camera->settarget({ -14,1.8 ,-15 });
		m_camera->SetPosition({ bezi.x,17.0f - (m_bezitime / 100.0f) * 15.0f,bezi.y });
	}
	if (swic == false && m_townnomaltime > 0)
	{
		m_camera->SetPosition({ -11 - sinf(m_townnomaltime) * 2.0f ,2 + sinf(m_townnomaltime) * 2.0f,0 });
	}
	if (swic == false && m_stagetime > 0)
	{
		m_camera->SetPosition({ 70 ,6 - m_stagetime * 0.3f,7 });
		m_camera->settarget({ 74,4 ,7 });
	}

	
	timer += 1.0f / 60.0f;
	tennmetu += 0.08;
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Update();
		}
		m_gameObject[i].remove_if([](GameObject* object) {return object->Destoroy(); });
	}
	//Manager::GetScene()->GetGameObject<Camera>()->SetRotation({0.0f,timer,0.0f});

	if (fade > 0)
	{
		fade += 0.01f;
	}
	if (fade > 1)
	{
		Manager::setscene(1);
	}
	m_fade.SetColer({0.0f,0.0f ,0.0f ,fade});
}

void titleScene::Draw()
{
	Renderer::SetAlphaTestEnable(true);
	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Draw();
		}
	}
	Renderer::SetAlphaTestEnable(false);
	////Draw2d::SetUI(GetImage().m_UI_image6, { 1.0f,1.0f,1.0f,1.0f }, { 960,540 }, { 1920,1080 }, {}, { 1.0f,1.0f }, {}, 0, 0.2f);
	//Draw2d::SetText("カフェインRPG", { 0,0,10000,500 },30, { 0.0f,0.0f ,0.0f ,1.0f }, 0.3f);
	//Draw2d::SetUI(GetImage().m_titol, { 1.0f,1.0f,1.0f,1.0f }, { 500,500 }, { 1000,1000 }, {}, { 1.0f,1.0f }, {}, 0, 2);
	//Draw2d::SetText("スペースを押してスタート", { 600,900,10000,10000 }, 50, { 1.0f,1.0f ,1.0f ,cosf(tennmetu) }, 0.3f);
	if (fade > 0)
	{
		//Draw2d::SetUI(GetImage().m_fade, { 1.0f,1.0f,1.0f,fade }, { 960,540 }, { 1920,1080 }, {}, { 1.0f,1.0f }, {},0, 10000);
	}
	if (m_effectfade > 0)
	{
		//Draw2d::SetUI(GetImage().m_fade, { 1.0f,1.0f,1.0f,sinf(m_effectfade) }, { 960,540 }, { 1920,1080 }, {}, { 1.0f,1.0f }, {}, 0, 10000);
	}
}
