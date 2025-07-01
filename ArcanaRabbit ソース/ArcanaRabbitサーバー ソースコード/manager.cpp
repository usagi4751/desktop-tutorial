#include "main.h"
#include "manager.h"
#include "renderer.h"
#include <list>
#include "input.h"
#include "modelRenderer.h"
#include "draw2d_Manager.h"


#include "Texture.h"
#include "material.h"
#include "audio.h"

#include "DictionarySkill.h"
#include "DictionaryItem.h"


#include "ServerManager.h"
//***********
//シーン
//***********
#include "TestUDPScene.h"

Scene* Manager::m_scene{};
Scene* Manager::m_nextscene{};
void Manager::Init()
{	
	Renderer::Init();//描画の初期化
	LoadMaterial();//画像データの読み込み
	Audio::InitMaster();//オーディオの読み込み
	Draw2D_Manager::Init();//2D描画の初期化
	DictionarySkill::Init();//スキルデータの初期化
	DictionaryItem::Init();//攻撃データの初期化
	m_scene = new TestUDPScene();//シーンの読み込み
	m_scene->Init();//シーンの初期化
	ServerManager::Init();//UDP通信の初期化
}

void Manager::Uninit()
{
	//=========================
	//解放処理
	//=========================
	Input::Uninit();
	m_scene->Uninit();
	Audio::UninitMaster();
	delete m_scene;
	Draw2D_Manager::Uninit();
	DictionarySkill::UnInit();
	DictionaryItem::UnInit();
	Renderer::Uninit();
	ModelRenderer::UnloadAll();
	ServerManager::UnInit();
}

void Manager::Update()
{
	m_scene->Update();//シーンの更新
	ServerManager::Update();//通信の更新
	Draw2D_Manager::Update();//2D描画の更新
	Input::Update();//入力の更新
}

void Manager::Draw()
{
	Renderer::Begin();

	m_scene->Draw();
	Draw2D_Manager::Draw();

	Renderer::End();
}

void Manager::setscene(int scene)
{
}




