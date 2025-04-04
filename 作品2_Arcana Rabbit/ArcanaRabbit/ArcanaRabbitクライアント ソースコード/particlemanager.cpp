#include "particlemanager.h"
#include "particleInterface.h"
#include "particleEmitter.h"
#include "renderer.h"
#include "particle.h"
#include "Emitterbrast.h"
#include "input.h"
void ParticleManager::Create()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		m_particle[i].crete(m_PixelShader, m_VertexShader, m_VertexLayout);
	}
}

void ParticleManager::Release()
{
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		m_particle[i].Release();
	}
	for (particleEmitter* emiter : m_Emitterlist)
	{
		emiter->Uninit();
		delete emiter;
	}
	m_Emitterlist.clear();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}


void ParticleManager::Init()
{

	for (int i = 0; i < MAXPARTICLE; i++)
	{
		m_particle[i].Init();
	}
	
}

void ParticleManager::Uninit()
{
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		m_particle[i].Uninit();
	}
	for (particleEmitter* emiter : m_Emitterlist)
	{
		emiter->Uninit();
		delete emiter;
	}
	m_Emitterlist.clear();
	//for (particleEmitter* emitter: m_EmitterList)
	//{
	//	emitter->Uninit();
	//	delete emitter;
	//}
	//m_EmitterList.clear();

}

void ParticleManager::Update()
{

	for (int i = 0; i < MAXPARTICLE; i++)
	{
		if (m_particle[i].Getlife() > 0)
		{
			m_particle[i].Update();
		}
	}
	for (particleEmitter* emitter: m_Emitterlist) {
		
		emitter->Update();
		
	}
	m_Emitterlist.remove_if([](particleEmitter* emitter) {
		if (emitter->Delete()) {
			delete emitter;
			return true;
		}
		return false; }
	);
	

}

void ParticleManager::Draw()
{
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		if (m_particle[i].Getlife() > 0)
		{
			m_particle[i].Draw();
		}
	}
}




void ParticleManager::Addperticle(Particle_data data, particleEmitter* emitter, Sorcletime sorcle)
{
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		if (m_particle[i].Getlife() <= 0)
		{
			m_particle[i].SetParticle(data, emitter,sorcle);
			break;
		}
	}
}

void ParticleManager::AddEmitter(particleEmitter* emitter)
{
	m_Emitterlist.push_back(emitter);
}









