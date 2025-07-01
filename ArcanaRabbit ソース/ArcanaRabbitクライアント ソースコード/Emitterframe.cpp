#include "Emitterframe.h"
#include "particlemanager.h"
#include "material.h"
#include "particle.h"
EmitterFrame::EmitterFrame(XMFLOAT3 pos, XMFLOAT3 rot)
	:particleEmitter(pos, rot) {
	m_life = 1;
	m_vel = {};
}

void EmitterFrame::Uninit()
{

}

void EmitterFrame::Update()
{
	if (m_life > 0)
	{
		m_life--;
	}

		Particle_data data;
		data.m_life = 120;
		float velspeed = 0.03f;
		//data.m_Vel = { -velspeed + frand() * velspeed * 0.5f,-velspeed + frand() * velspeed * 0.5f ,-velspeed + frand() * velspeed * 0.5f };
		data.m_Vel = {
			-velspeed * 0.5f + frand() * velspeed ,
			-velspeed * 0.5f + frand() * velspeed  ,
			-velspeed * 0.5f + frand() * velspeed };
		data.pos = m_Pos;
		data.scale = { 0.2f,0.2f };
		data.coler = { 1.0f,0.75f,0.0f,1.0f };
		data.endcoler = {1.0f,0.0f,0.0f,0.0f};
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

	

	m_vel.y -= 0.01f;
	float speed = 0.3f;
	m_Pos.x += sinf(m_Rot.y) * cosf(m_Rot.x) * speed + m_vel.x;
	m_Pos.z += cosf(m_Rot.y) * cosf(m_Rot.x) * speed + m_vel.z;
	m_Pos.y += sinf(m_Rot.x) * speed + m_vel.y;
}

bool EmitterFrame::Delete()
{
	if (m_life <= 0)
	{
		return true;
	}
	return false;
}
