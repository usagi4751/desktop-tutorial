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
//�V�[��
//***********
#include "TestUDPScene.h"

Scene* Manager::m_scene{};
Scene* Manager::m_nextscene{};
void Manager::Init()
{	
	Renderer::Init();//�`��̏�����
	LoadMaterial();//�摜�f�[�^�̓ǂݍ���
	Audio::InitMaster();//�I�[�f�B�I�̓ǂݍ���
	Draw2D_Manager::Init();//2D�`��̏�����
	DictionarySkill::Init();//�X�L���f�[�^�̏�����
	DictionaryItem::Init();//�U���f�[�^�̏�����
	m_scene = new TestUDPScene();//�V�[���̓ǂݍ���
	m_scene->Init();//�V�[���̏�����
	ServerManager::Init();//UDP�ʐM�̏�����
}

void Manager::Uninit()
{
	//=========================
	//�������
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
	m_scene->Update();//�V�[���̍X�V
	ServerManager::Update();//�ʐM�̍X�V
	Draw2D_Manager::Update();//2D�`��̍X�V
	Input::Update();//���͂̍X�V
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




