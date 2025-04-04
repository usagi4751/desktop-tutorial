#pragma once
#include "particleEmitter.h"
class Emitterportal : public particleEmitter {
	int m_life = 0;
	XMFLOAT3 m_vel;
public:
	Emitterportal() = delete;
	Emitterportal(XMFLOAT3 pos, XMFLOAT3 rot);
	virtual void Uninit() override;
	virtual void Update() override;
	virtual bool Delete() override;
};

