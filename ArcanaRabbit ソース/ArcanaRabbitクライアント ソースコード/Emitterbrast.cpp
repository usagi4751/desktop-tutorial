#include "Emitterbrast.h"
#include "particlemanager.h"
#include "material.h"
#include "particle.h"
EmitterBrast::EmitterBrast(XMFLOAT3 pos, XMFLOAT3 rot)
:particleEmitter(pos, rot) {
	m_life = 2000000;
	m_vel = {};
}

void EmitterBrast::Uninit()
{

}

void EmitterBrast::Update()
{
	if (m_life > 0)
	{
		m_life--;
	}
	for (int i = 0; i < 2; i++)
	{
		Particle_data data;
		data.m_life = 280;
		float velspeed = 0.06f;
		//data.m_Vel = { -velspeed + frand() * velspeed * 0.5f,-velspeed + frand() * velspeed * 0.5f ,-velspeed + frand() * velspeed * 0.5f };
		data.m_Vel = {
			-velspeed * 0.5f + frand() * velspeed ,
			 frand() * velspeed  ,
			-velspeed * 0.5f + frand() * velspeed };
		data.pos = m_Pos;
		data.pos.x -= 1.2f - 3.0f * frand();
		data.pos.y += 0.2f;
		data.pos.z -= 1.2f - 3.0f * frand();
		data.scale = { 0.23f,0.23f };
		data.coler = { 1.0f,0.0f,1.0f,1.0f };
		data.endcoler = data.coler;
		data.endcoler.w = 0;
		data.uv_u = { frand() > 0.5f ? 0.0f : 0.5f,frand() > 0.5f ? 0.0f : 0.5f };
		data.uv_v = { 0.5f,0.5f };
		data.tex = GetImage().m_particle_Flame;
		Sorcletime sorcre;
		sorcre.issorcle = false;
		sorcre.isNoVel = false;
		sorcre.isEmitter = false;
		sorcre.Rotate.y = 0;
		sorcre.Rotate.x = 0;
		sorcre.distance = 0.2f;
		sorcre.RotateVel.y = 0.1f;
		sorcre.RotateVel.x = 0.0f;

		
			m_mamager->Addperticle(data, this, sorcre);
		
	}
	
	//m_vel.y -= 0.01f;
	//float speed = 0.3f;
	//m_Pos.x += sinf(m_Rot.y) * cosf(m_Rot.x) * speed + m_vel.x;
	//m_Pos.z += cosf(m_Rot.y) * cosf(m_Rot.x) * speed + m_vel.z;
	//m_Pos.y += sinf(m_Rot.x) * speed + m_vel.y;
}

bool EmitterBrast::Delete()
{
	if (m_life <= 0)
	{
		return true;
	}
	return false;
}
