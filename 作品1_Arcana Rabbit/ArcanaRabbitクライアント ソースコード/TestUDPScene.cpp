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
#include "material.h"
#include "manager.h"


//テスト用
#include "EnemyDataManager.h"
#include "UDPManager.h"
#include "DrawName.h"
void TestUDPScene::Init()
{

	AddObject<Camera>(0);
	//Player*  player = AddObject<Player>(1);

	ShowObject* field = AddObject<ShowObject>(1);
	field->SetPosition({ 0,-0.03f,0 });
	field->SetObject("asset\\model\\map1_3\\map1_3.obj");
	field->SetScale({ 1.3f,1.3f, 1.3f });

	

	m_Chat.Link(Draw2D_Manager::AddTEXT());
	m_Chat.SetRect({ 0,0,1920,1080 });
	m_Chat.SetText("");
	m_Chat.SetColer({ 1.0f,1.0f,1.0f,1.0f });

	m_IpAddressFormText.Link(Draw2D_Manager::AddTEXT());
	m_IpAddressFormText.SetRect({550,280,900,320});
	m_IpAddressFormText.SetText("ポート番号");
	m_IpAddressFormText.SetColer({0.0f,0.0f,0.0f,1.0f});

	m_PortFormText.Link(Draw2D_Manager::AddTEXT());
	m_PortFormText.SetRect({ 550,380,900,420 });
	m_PortFormText.SetText("IPアドレス");
	m_PortFormText.SetColer({ 1.0f,1.0f,1.0f,1.0f });

	m_NameFormText.Link(Draw2D_Manager::AddTEXT());
	m_NameFormText.SetRect({ 550,480,900,520 });
	m_NameFormText.SetText("名前");
	m_NameFormText.SetColer({ 1.0f,1.0f,1.0f,1.0f });

	m_SendPlayerDataButtun = new Buttun;
	m_SendPlayerDataButtun->SetPosition({ SCREEN_WIDTH * 0.5f + 350,650 });
	m_SendPlayerDataButtun->SetScale({ 200,200 });
	m_SendPlayerDataButtun->SetDepth(2.0f + 0.02f);
	m_SendPlayerDataButtun->SetTextuer(GetImage().m_fade);
	m_SendPlayerDataButtun->SetActive(false);

	m_StartButtun = new Buttun;
	m_StartButtun->SetPosition({ SCREEN_WIDTH * 0.5f + 350,400 });
	m_StartButtun->SetScale({ 200,200 });
	m_StartButtun->SetDepth(2.0f + 0.02f);

	m_PortForm = AddObject<TextForm>(2);
	m_PortForm->CloseTextBox();
	m_PortForm->SetScale({400.0f,40.0f,0});
	m_PortForm->SetPosition({SCREEN_WIDTH *0.5f,300,0});
	m_PortForm->SetColer({0.7f,0.7f ,0.7f ,1.0f });
	m_PortForm->SetTextSetting(NUMBER);
	m_PortForm->SetText("4751");

	m_NameForm = AddObject<TextForm>(2);
	m_NameForm->CloseTextBox();
	m_NameForm->SetScale({ 400.0f,40.0f,0 });
	m_NameForm->SetPosition({ SCREEN_WIDTH * 0.5f,500,0 });
	m_NameForm->SetColer({ 0.7f,0.7f ,0.7f ,1.0f });
	m_NameForm->SetTextSetting(NOMULTI);
	m_NameForm->SetText("aaa");


	m_IpAddressForm = AddObject<TextForm>(2);
	m_IpAddressForm->CloseTextBox();
	m_IpAddressForm->SetScale({ 400.0f,40.0f,0 });
	m_IpAddressForm->SetPosition({ SCREEN_WIDTH * 0.5f,400,0 });
	m_IpAddressForm->SetColer({ 0.7f,0.7f ,0.7f ,1.0f });
	m_IpAddressForm->SetTextSetting(NOMULTI);
	m_IpAddressForm->SetText("192.168.1.27");


	AddObject<TextBox>(2);
	MouseClip(false);
}

void TestUDPScene::Uninit()
{
	delete m_StartButtun;
	delete m_SendPlayerDataButtun;
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
void TestUDPScene::Update()
{
	m_Chat.SetText(  Manager::GetUdpManager()->GetChatData());
	if (Input::IsMouseLeftTriggered() && m_PortForm->OnMouseButtun())
	{
		m_PortForm->OpenTextBox();
	}
	if (Input::IsMouseLeftTriggered() && m_IpAddressForm->OnMouseButtun())
	{
		m_IpAddressForm->OpenTextBox();
	}
	if (Input::IsMouseLeftTriggered() && m_NameForm->OnMouseButtun())
	{
		m_NameForm->OpenTextBox();
	}
	if (Input::IsMouseLeftTriggered() && m_StartButtun->OnMouseButtun() )
	{
		UDP::SetIPAddress(*m_IpAddressForm->GetText());
		UDP::SetPort(atoi(m_PortForm->GetText()->c_str()));
		UDP::SetName(*m_NameForm->GetText());
		UDP::ServerAccess();

	}
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

void TestUDPScene::Draw()
{

	for (int i = 0; i < 3; i++)
	{
		for (GameObject* gameobject : m_gameObject[i])
		{
			gameobject->Draw();
		}
		if (i == 1)
		{
			Manager::GetUdpManager()->Draw();

		}
	}
	
}
