#include "main.h"
#include "manager.h"
#include "renderer.h"
#include <list>
#include "input.h"
#include "gameScene.h"
#include "modelRenderer.h"
#include "draw2d_Manager.h"


#include "Texture.h"
#include "material.h"
#include "audio.h"

#include "DictionarySkill.h"
#include "DictionaryItem.h"


#include "ServerManager.h"
//***********
//ƒV[ƒ“
//***********
#include "TestUDPScene.h"

Scene* Manager::m_scene{};
Scene* Manager::m_nextscene{};
void Manager::Init()
{	
	Renderer::Init();
	LoadMaterial();
	Audio::InitMaster();
	Draw2D_Manager::Init();
	DictionarySkill::Init();
	DictionaryItem::Init();
	m_scene = new TestUDPScene();
	m_scene->Init();
	ServerManager::Init();
}


void Manager::Uninit()
{

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
	m_scene->Update();
	ServerManager::Update();
	Draw2D_Manager::Update();
	Input::Update();
}

void Manager::Draw()
{
	Renderer::Begin();
	m_scene->Draw();
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
m_nextscene = new gameScene();


}




