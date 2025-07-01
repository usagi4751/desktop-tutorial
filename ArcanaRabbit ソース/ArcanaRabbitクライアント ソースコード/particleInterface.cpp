#include "particleInterface.h"
#include "particlemanager.h"
#include "particleEmitter.h"
ParticleManager* ParticleInerface::m_manager;

void ParticleInerface::Link(ParticleManager* manager)
{
	m_manager= manager;
}
void ParticleInerface::Init()
{
	m_manager->Init();
}
void ParticleInerface::Uninit()
{
	m_manager->Uninit();
}

void ParticleInerface::SetEmitter(particleEmitter* emitter)
{
	m_manager->AddEmitter(emitter);
	emitter->SetManager(m_manager);
}


