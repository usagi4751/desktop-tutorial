#pragma once
#include "particleInterface.h"
class particleEmitter {

protected:

	ParticleManager* m_mamager;
	XMFLOAT3 m_Pos;
	XMFLOAT3 m_Rot;
public:
	particleEmitter(XMFLOAT3 pos, XMFLOAT3 rot) :m_Pos(pos), m_Rot(rot){};
	void SetManager(ParticleManager* mamager) { m_mamager = mamager; };
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual bool Delete() = 0;
	XMFLOAT3 GetPos() { return m_Pos; };
	XMFLOAT3 GetRot() { return m_Rot; };
};
