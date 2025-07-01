#include "main.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "bullet.h"
#include "input.h"
#include "audio.h"
#include "camera.h"
#include "floor.h"
#include "material.h"
#include "enemy.h"
#include "collision.h"
#include "DictionarySkill.h"
#include "SkilldataBase.h"
#include "ItemDataBase.h"
#include "DictionaryItem.h"
#include "item.h"
#include "meshField.h"
#include "audio.h"
#include "inventory.h"
#include "shadowVolume.h"
#include "TextBox.h"
#define BASEMOVESPEED 0.01f
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
void Player::Init() {


	m_Componentplayer = new ModelRenderer(this);
	((ModelRenderer*)m_Componentplayer)->Load("asset\\model\\player.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_audio = new Audio(this);
	((Audio*)m_audio)->Load("asset\\sound\\bgm.wav");

	m_floor = Manager::GetScene()->GetGameObject<Floor>();

	m_NomalAttackRange = 5.0f;

	Manager::GetScene()->GetGameObject<Camera>()->SetTagetEnable(true);

	m_fly = true;

}
void Player::Uninit() {
	((ModelRenderer*)m_Componentplayer)->UnInit();
	delete m_Componentplayer;
	((Audio*)m_audio)->Uninit();
	delete m_audio;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	bool OpenTextBoxflug = false;
	TextBox* textbox = Manager::GetScene()->GetGameObject<TextBox>();
	if (textbox != nullptr)
	{
		OpenTextBoxflug  = textbox->GetOpenFlug();
	}

	if (Input::IsMouseLeftTriggered() && OpenTextBoxflug == false)
	{
		//MouseClip(true);
	}
	m_oldpos = m_Position;

	CameraUpdate();

	Action();

	//Move();

	if (m_fly == false)
	{
		Jump();

		NomalOperation();

		IsGround();
	}
	DevelopDebugComand();
	if (m_fly == true) {
		DevelopFreeFly();
		DevelopFlyOperation();
	}





	//===================================================
	// カメラの更新
	// 消すな
	//===================================================
	Camera* Target = Manager::GetScene()->GetGameObject<Camera>();
	Target->SetPosition({m_Position.x ,m_Position.y + 1.8f ,m_Position.z});
	Target->SetRotation(m_Rotation);

	
}

void Player::Draw()
{

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリックス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(0, 0,0);
	trans = XMMatrixTranslation(m_Position.x , m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//m_Componentplayer->Draw();

	//インベントリの描画
	Inventory::DrawRect();

	//攻撃のクールタイムの描画
	//Draw2d::SetUI(GetImage().m_UI_image5, { 0.6f ,0.6f ,0.6f ,0.5f }, { 1600,870 }, { 200.0f ,200.0f }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 1.0f);
	//Draw2d::SetUI(GetImage().m_UI_image5, { 1.0f ,1.0f ,1.0f ,1.0f }, { 1600,770 + (1.0f - (float)m_AttackCD / 12000.0f) * 100.0f }, { 200.0f ,200.0f * (1.0f - (float)m_AttackCD / 12000.0f) }, { 0.0f,0.0f }, { 1.0f,1.0f - (float)m_AttackCD / 12000.0f }, { 0.0f,0.0f }, 0.0f, 1.0001f);

	//体力表示
	//Draw2d::SetUI(GetImage().m_fade, { 1.0f ,0.0f ,0.0f ,1.0f }, { 660 + 300.0f * (m_NowHp / Inventory::GetStayus().MaxHelth),970 }, { 600.0f * (m_NowHp / Inventory::GetStayus().MaxHelth) ,40.0f }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 1.0f);
	//Draw2d::SetText(std::to_string((int)m_NowHp) + "/" + std::to_string((int)Inventory::GetStayus().MaxHelth), { 660,970 - 25,1920,1080 }, 30, { 1.0f,1.0f ,1.0f ,1.0f }, 1.0001f);
	
	//画面中心のレティクルの描画
	//Draw2d::SetUI(GetImage().m_reticle_1, { 1.0f ,0.0f ,0.0f ,1.0f }, { 960,540 }, { 32.0f ,32.0f }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 1.0f);
	
	//デバック用のUI
#ifdef _DEBUG	// デバッグの時表示
	DevelopDebugUI();
#endif

}


void Player::NomalOperation()
{

	//物理演算
	if (m_vel.y > 0 || m_vel.y < 0)
	{
		float nowpos = m_Position.y;
		m_Position.y += m_vel.y;
		//落下したときに慣性をかなり減衰させる
		if (nowpos > 0 && m_Position.y <= 0)
		{
			m_vel.x *= 0.4f;
			m_vel.z *= 0.4f;
		}
	}
	if (m_vel.x > 0 || m_vel.x < 0)
	{
		m_Position.x += m_vel.x;
		m_vel.x *= 0.997f;
		if (m_IsGround)
		{
			m_vel.x *= 0.85f;
		}

	}
	if (m_vel.z > 0 || m_vel.z < 0)
	{
		m_Position.z += m_vel.z;
		m_vel.z *= 0.997f;
		if (m_IsGround)
		{
			m_vel.z *= 0.85f;
		}
	}
	if (m_vel.x < 0.00001f && m_vel.x > -0.00001f)
	{
		m_vel.x = 0.0f;
	}
	if (m_Position.y <= 0)
	{
		
		m_vel.y = 0.0f;
		m_Position.y = 0.0f;
	}
	else
	{
		m_vel.y -= 0.009f;
	}




	//meshField* fild = Manager::GetScene()->GetGameObject<meshField>();
	//if (fild->Getheight(m_Position) > m_Position.y)
	//{
	//	m_Position.y = fild->Getheight(m_Position);
	//	m_vel.y = 0.0f;
	//}
	//else
	//{
	//	m_vel.y -= 0.009f;
	//}
}

void Player::IsGround()
{
	m_IsGround = false;
	meshField* fild = Manager::GetScene()->GetGameObject<meshField>();
	if (m_Position.y <= 0)
	{
		m_IsGround = true;
	}
	//if (fild->Getheight(m_Position) >= m_Position.y)
	//{
	//	m_IsGround = true;
	//}
}

void Player::Jump()
{
	if (Input::GetKeyPress(VK_SPACE) && m_IsGround)
	{
		m_vel.y += 0.16f;
	}
}

void Player::Move()
{
	float dush = 1.0f;
	float sneeck = 1.0f;
	float movespeed = BASEMOVESPEED * Inventory::GetStayus().MoveSpeed * 0.01f;
	float ground = 1.0f;
	if (Input::GetKeyPress(VK_LSHIFT))
	{
		sneeck = 0.2f;
	}
	if (Input::GetKeyPress(VK_LCONTROL))
	{

		dush = 2.5f;
	}
	//移動方向
	XMFLOAT2 movevel;
	movevel.x = 0.0f;
	movevel.y = 0.0f;
	if (Input::GetKeyPress(0x57))//w
	{
		movevel.y += 1.0f;
	}
	if (Input::GetKeyPress(0x53))//s
	{
		movevel.y -= 1.0f;
	}
	if (Input::GetKeyPress(0x41))//a
	{
		movevel.x -= 1.0f;
	}
	if (Input::GetKeyPress(0x44))//d
	{
		movevel.x += 1.0f;
	}

	float nom = sqrtf(movevel.x * movevel.x + movevel.y * movevel.y);
	if (nom != 0)
	{
		nom = 1 / nom;
		movevel.x *= nom;
		movevel.y *= nom;
	}

	//wasd移動
	if (Input::GetKeyPress(0x57))
	{
		if (m_IsGround == false)
		{
			ground = 0.05f;
		}
		m_vel.x += sinf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
	}
	if (Input::GetKeyPress(0x53))
	{
		if (m_IsGround == false)
		{
			ground = 0.05f;
		}
		m_vel.x += sinf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
	}
	if (Input::GetKeyPress(0x41))
	{
		if (m_IsGround == false)
		{
			ground = 0.05f;
		}
		m_vel.x += sinf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
	}
	if (Input::GetKeyPress(0x44))
	{
		if (m_IsGround == false)
		{
			ground = 0.05f;
		}
		m_vel.x += sinf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
	}
}

void Player::CameraUpdate()
{
	m_Rotation.y += Input::GetMouseX() * 0.001f;
	m_Rotation.x -= Input::GetMouseY() * 0.001f;

	if (m_Rotation.x < (-XM_PIDIV2 + 0.01f))
	{
		m_Rotation.x = (-XM_PIDIV2 + 0.01f);
	}
	if (m_Rotation.x > (XM_PIDIV2 - 0.01f))
	{
		m_Rotation.x = (XM_PIDIV2 - 0.01f);
	}
	if (m_Rotation.y < -XM_PI)
	{
		m_Rotation.y += +XM_2PI;
	}
	if (m_Rotation.y > XM_PI)
	{
		m_Rotation.y -= XM_2PI;
	}
}

void Player::Action()
{
	//攻撃
	if (Input::IsMouseLeftTriggered() && m_InventoryOpen != true && m_AttackCD <= 0)
	{
		m_AttackCD = 12000;
	}
	//スキル
	if (Input::IsMouseRightTriggered() && m_InventoryOpen != true)
	{
	}
	if (Input::GetKeyTrigger(0x45))
	{
		m_InventoryOpen = !m_InventoryOpen;
	}
	//インベントリの開け閉め
	if (Input::GetMouseZ() > 0)
	{
		m_haveitem--;
		if (m_haveitem < 0)
		{
			m_haveitem = 7;
		}
	}
	if (Input::GetMouseZ() < 0)
	{
		m_haveitem++;
		if (m_haveitem > 7)
		{
			m_haveitem = 0;
		}
	}
}

void Player::AddDamage(float damage)
{
	if (damage > 0)
	{
	}
}

void Player::Addheal(float heal)
{
	if (heal > 0)
	{
	}
}

XMFLOAT3 Player::PlayerRay()
{
	XMFLOAT3 Rock;
	Rock.x = sinf(m_Rotation.y) * cosf(m_Rotation.x) * 1.0f;
	Rock.z = cosf(m_Rotation.y) * cosf(m_Rotation.x) * 1.0f;
	Rock.y = sinf(m_Rotation.x) * 1.0f;
	return Rock;
};




void Player::DevelopNuru()
{
	if (Input::IsMouseLeftPressed())
	{
		for (int i = -size; i < size + 1; i++)
		{
			for (int j = -size; j < size + 1; j++)
			{
				float rei = m_Rotation.x - (-XM_PIDIV2 + 0.01f);
				rei = tanf(rei) * (m_Position.y + 1.5f);
				if (rei < 20)
				{
					float xpos = m_Position.x + sinf(m_Rotation.y) * rei + (float)i;
					float zpos = m_Position.z + cosf(m_Rotation.y) * rei + (float)j;
					m_floor->SetFloor({ xpos ,zpos }, false);
				}

			}
		}

	}
	if (Input::IsMouseRightPressed())
	{
		for (int i = -size; i < size + 1; i++)
		{
			for (int j = -size; j < size + 1; j++)
			{
				float rei = m_Rotation.x - (-XM_PIDIV2 + 0.01f);
				rei = tanf(rei) * (m_Position.y + 1.5f);
				if (rei < 20)
				{
					float xpos = m_Position.x + sinf(m_Rotation.y) * rei + (float)i;
					float zpos = m_Position.z + cosf(m_Rotation.y) * rei + (float)j;
					m_floor->SetFloor({ xpos ,zpos }, true);
				}

			}
		}
	}
	if (Input::GetKeyTrigger(0x43))
	{

		float xpos = m_Position.x >= 0 ? m_Position.x : m_Position.x;
		float zpos = m_Position.z >= 0 ? m_Position.z : m_Position.z;
		if (xpos < -256) { xpos = -255; }
		if (xpos > 256) { xpos = 255; }
		if (zpos < -256) { zpos = -255; }
		if (zpos > 256) { zpos = 255; }
		m_floor->SetFloor({ xpos ,zpos }, true);

	}
	if (Input::GetMouseZ() > 0 && size < 5)
	{
		size++;
	}
	if (Input::GetMouseZ() < 0 && size > 0)
	{
		size--;
	}
}

void Player::DevelopFreeFly()
{
	if (Input::GetKeyPress(VK_SPACE))
	{
		m_Position.y += 0.1f;
	}
	if (Input::GetKeyPress(VK_LSHIFT))
	{
		m_Position.y -= 0.1f;
	}
	float dush = 1.0f;
	float sneeck = 1.0f;
	float movespeed = BASEMOVESPEED * Inventory::GetStayus().MoveSpeed * 0.01f;
	float ground = 1.0f;
	if (Input::GetKeyPress(VK_LSHIFT))
	{
		sneeck = 0.2f;
	}
	if (Input::GetKeyPress(VK_LCONTROL))
	{

		dush = 2.5f;
	}
	//移動方向
	XMFLOAT2 movevel;
	movevel.x = 0.0f;
	movevel.y = 0.0f;
	if (Input::GetKeyPress(0x57))//w
	{
		movevel.y += 1.0f;
	}
	if (Input::GetKeyPress(0x53))//s
	{
		movevel.y -= 1.0f;
	}
	if (Input::GetKeyPress(0x41))//a
	{
		movevel.x -= 1.0f;
	}
	if (Input::GetKeyPress(0x44))//d
	{
		movevel.x += 1.0f;
	}

	float nom = sqrtf(movevel.x * movevel.x + movevel.y * movevel.y);
	if (nom != 0)
	{
		nom = 1 / nom;
		movevel.x *= nom;
		movevel.y *= nom;
	}

	//wasd移動
	if (Input::GetKeyPress(0x57))
	{
	
		m_vel.x += sinf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
	}
	if (Input::GetKeyPress(0x53))
	{
	
		m_vel.x += sinf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y) * movespeed * movevel.y * dush * sneeck * ground;
	}
	if (Input::GetKeyPress(0x41))
	{
	
		m_vel.x += sinf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
	}
	if (Input::GetKeyPress(0x44))
	{
	
		m_vel.x += sinf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
		m_vel.z += cosf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x * dush * sneeck * ground;
	}
}

void Player::DevelopDebugComand()
{
	if (Input::GetKeyTrigger(VK_F1))
	{
		m_fly = !m_fly;
	}
	if (Input::IsMouseSide4Triggered())
	{
		LPCTSTR cursor = MAKEINTRESOURCE(32512);
		SetCursor(LoadCursor(NULL, cursor));
		MouseClip(false);
	}
	m_NowHp += 0.013333333f;
	if (Input::GetKeyTrigger('L'))
	{
		Item dropitem;
		dropitem.m_ItemNo = 0;
		dropitem.m_ItemNum = 100;
		dropitem.m_skillNo = -1;
		Inventory::Getitem(dropitem);
	}
	
if (Input::GetKeyTrigger('F'))
{
	Scene* scene = Manager::GetScene();
	bullet* bullet_ = scene->AddObject<bullet>(1);
	bullet_->SetPosition(XMFLOAT3{m_Position.x,m_Position.y + 1.5f,m_Position.z});
	bullet_->SetRotation(m_Rotation);
//	((Audio*)m_audio)->Play();
}


	if (Input::IsMouseSide5Triggered())
	{
		m_vel.x += sinf(m_Rotation.y) * 3.0f;
		m_vel.z += cosf(m_Rotation.y) * 3.0f;
	}

	if (Input::Input::GetKeyPress(0x50))
	{
		//m_Position.x = 0.0f;
		//m_Position.z = -255.5f;
	}
}

void Player::DevelopDebugUI()
{
	std::string  text = "WASD移動\n";
	text += "shift 歩く\nE インベントリを使う インベントリ中クリックで移動\nctrl ダッシュ\nspace ジャンプ";
	///Draw2d::SetText(text, { 0,0,1000,1000 }, 20, { 1.0f,1.0f ,1.0f ,1.0f }, 0.5f);
	//Draw2d::SetText("height" + std::to_string(Manager::GetScene()->GetGameObject<meshField>()->Getheight(m_Position)), { 0,160,8000,500 }, 30, { 1.0f,1.0f ,0.0f ,1.0f }, 1.3f);
	//Draw2d::SetText("uiscale" + std::to_string(g_size), { 0,160,8000,500 }, 30, { 1.0f,1.0f ,0.0f ,1.0f }, 1.3f);
	//XMFLOAT3 pos = *enemy->GetPosition();
	//XMFLOAT2 a = { (pos.x - m_Position.x),(pos.z - m_Position.z) };
	//float l2 = atan2(a.x,a.y);
	//Draw2d::SetText("enemy rot " + std::to_string(l2 * 180.0f / XM_PI) , { 0,60,8000,500 }, 30, { 1.0f,1.0f ,0.0f ,1.0f }, 1.3f);
//	Draw2d::SetText("RotY" + std::to_string(m_Rotation.y) , { 0,30,8000,500 }, 30, { 1.0f,1.0f ,0.0f ,1.0f }, 1.3f);
	//Draw2d::SetText("X" + std::to_string(m_Position.x) + "Y" + std::to_string(m_Position.y) + "Z" + std::to_string(m_Position.z), { 0,0,8000,500 }, 30, { 1.0f,1.0f ,0.0f ,1.0f }, 1.3f);

		//"E インベントリを使う インベントリ中クリックで移動\n"
	//std::string aa = std::to_string(l2 * 180.0f / XM_PI - m_Rotation.y * 180.0f / XM_PI);
	//Draw2d::SetText("sa ROt "+ aa, { 0,90,8000,500 }, 30, { 1.0f,1.0f ,0.0f ,1.0f }, 1.3f);
	//Draw2d::SetText("X" + std::to_string((int)m_Position.x) + "Y" + std::to_string((int)m_Position.y) + "Z" + std::to_string((int)m_Position.z), { 0,30,500,500 }, 30, { 0.0f,0.0f ,0.0f ,1.0f }, 1.3f);
	//	//Draw2d::SetUI(0,{ 1.0f ,1.0f ,1.0f ,1.0f }, { 200,200 }, { 100.0f ,100.0f }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 1.0f);
	//	//Draw2d::SetUI(0,{ 1.0f ,0.0f ,0.0f ,1.0f }, { 400,400 }, { 200.0f ,200.0f }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 1.0f);	
	//	//Draw2d::SetUI(0,{ 1.0f ,0.0f ,0.0f ,1.0f }, { 50,25 }, { 50.0f ,50.0f }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 1.0f);
	//	//Draw2d::SetUI(0, { 1.0f ,0.0f ,0.0f ,1.0f }, { 100,25 }, { 50.0f ,50.0f }, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f }, 0.0f, 1.0f);
}

void Player::DevelopSaveAndLoad()
{
	//保存
	if (Input::GetKeyPress(0x31))
	{
		const char* MapFilePath = "asset/stagedata/floor/stage.txt";  // 保存先ファイルパス

		std::ofstream ofs(MapFilePath);
		if (ofs.is_open())
		{
			for (int j = 0; j < 512; j++)
			{
				std::string textlen;
				bool tas[512];
				for (int i = 0; i < 512; i++)
				{
					tas[i] = m_floor->GetFloor({ (float)i ,(float)j });
				}
				for (int i = 0; i < 85; i++)
				{
					const char text = 0x30 + tas[0 + i * 6] + tas[1 + i * 6] * 2 + tas[2 + i * 6] * 4 + tas[3 + i * 6] * 8 + tas[4 + i * 6] * 16 + tas[5 + i * 6] * 32;
					textlen += text;
				}
				const char text = 0x30 + tas[0 + 85 * 6] + tas[1 + 85 * 6] * 2;
				textlen += text;


				ofs << textlen;
			}
			ofs.close();

		}
	}
	//読み込み
	if (Input::GetKeyPress(0x32))
	{
		const char* MapFilePath = "asset/stagedata/floor/stage.txt";  // 保存先ファイルパス

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
						m_floor->SetFloor({ ind * 6.0f + 5 ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f + 5 ,(float)i }, false);
					}

					if (num > 15)
					{
						num -= 16;
						m_floor->SetFloor({ ind * 6.0f + 4 ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f + 4 ,(float)i }, false);
					}

					if (num > 7)
					{
						num -= 8;
						m_floor->SetFloor({ ind * 6.0f + 3 ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f + 3 ,(float)i }, false);
					}

					if (num > 3)
					{
						num -= 4;
						m_floor->SetFloor({ ind * 6.0f + 2 ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f + 2 ,(float)i }, false);
					}

					if (num > 1)
					{
						num -= 2;
						m_floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, false);
					}

					if (num > 0)
					{
						num -= 1;
						m_floor->SetFloor({ ind * 6.0f ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f ,(float)i }, false);
					}
				}
				else
				{
					if (num > 1)
					{
						num -= 2;
						m_floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f + 1 ,(float)i }, false);
					}

					if (num > 0)
					{
						num -= 1;
						m_floor->SetFloor({ ind * 6.0f ,(float)i }, true);
					}
					else
					{
						m_floor->SetFloor({ ind * 6.0f ,(float)i }, false);
					}
				}
				ind++;
			}
		}

	}
}

void Player::DevelopFlyOperation()
{
	bool on_earth = false;
	//物理演算もどき

	if (m_vel.x > 0 || m_vel.x < 0)
	{
		m_Position.x += m_vel.x;
		m_vel.x *= 0.98f;
		m_vel.x *= 0.85f;

		if (m_vel.x < 0.00001f && m_vel.x > -0.00001f)
		{
			m_vel.x = 0.0f;
		}
	}
	if (m_vel.z > 0 || m_vel.z < 0)
	{
		m_Position.z += m_vel.z;
		m_vel.z *= 0.98f;
		m_vel.z *= 0.85f;

		if (m_vel.z < 0.00001f && m_vel.z > -0.00001f)
		{
			m_vel.z = 0.0f;
		}
	}


}

