#include "main.h"
#include "manager.h"
#include "renderer.h"
#include <list>
#include "input.h"
#include "gameScene.h"
#include "player.h"
#include "modelRenderer.h"
#include "draw2d_Manager.h"


#include "Texture.h"
#include "material.h"
#include "audio.h"
#include "particlemanager.h"
#include "particleInterface.h"
#include "inventory.h"
#include "DictionarySkill.h"
#include "DictionaryItem.h"


#include "UDPManager.h"
#include "EnemyDataManager.h"

//***********
//ƒV[ƒ“
//***********
#include "titleScene.h"
#include "gameScene2.h"
#include "gameScene3.h"
#include "TestUDPScene.h"
#include "result.h"
Scene* Manager::m_scene{};
Scene* Manager::m_nextscene{};
ParticleManager* p_ParticleManager;
UDPManager* Manager::m_UdpManager{};
void Manager::Init()
{	
	Renderer::Init();
	LoadMaterial();
	Audio::InitMaster();
	p_ParticleManager = new ParticleManager;
	p_ParticleManager->Create();
	ParticleInerface::Link(p_ParticleManager);
	Draw2D_Manager::Init();
	DictionarySkill::Init();
	DictionaryItem::Init();
	m_scene = new titleScene();
	m_scene->Init();
	Inventory::Init();
	UDP::Init();
	EnemyDataManager::Init();
	m_UdpManager = new UDPManager;
	m_UdpManager->Init();
}


void Manager::Uninit()
{

	Input::Uninit();
	m_scene->Uninit();
	Audio::UninitMaster();
	delete m_scene;
	p_ParticleManager->Release();
	delete p_ParticleManager;
	Draw2D_Manager::Uninit();
	DictionarySkill::UnInit();
	DictionaryItem::UnInit();
	Renderer::Uninit();
	ModelRenderer::UnloadAll();
	UDP::UnInit();
	m_UdpManager->UnInit();
	EnemyDataManager::UnInit();
	delete m_UdpManager;
}

void Manager::Update()
{
	m_scene->Update();
	Inventory::Update();
	p_ParticleManager->Update();
	m_UdpManager->Update();
	Draw2D_Manager::Update();
	Input::Update();
}

void Manager::Draw()
{
	Renderer::Begin();
	m_scene->Draw();
	p_ParticleManager->Draw();
	Draw2D_Manager::Draw();
	Renderer::End();

	if (m_nextscene)
	{
		m_scene->Uninit();
		delete m_scene;

		m_scene = m_nextscene;
		m_scene->Init();
		m_nextscene = nullptr;
	}
}

void Manager::setscene(int scene)
{
	switch (scene)
	{
	case 0:m_nextscene = new titleScene; break;
	case 1:m_nextscene = new gameScene(); break;
	case 2:m_nextscene = new gameScene2; break;
	case 3:m_nextscene = new gameScene3; break;
	case 4:m_nextscene = new resultScene; break;
	default:
		break;
	}

}

UDPManager* Manager::GetUdpManager()
{
	return m_UdpManager;
}




