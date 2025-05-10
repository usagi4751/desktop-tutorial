#pragma once
#pragma once
//�x�W�F�Ȑ���Ƀp�[�e�B�N�����o��
//�f�o�b�N�Ŏg����
#include "particleEmitter.h"
class EmitterBezier : public particleEmitter {
	int m_life = 0;
	XMFLOAT3 m_vel;
public:
	EmitterBezier() = delete;
	EmitterBezier(XMFLOAT3 pos, XMFLOAT3 rot);
	virtual void Uninit() override;
	virtual void Update() override;
	virtual bool Delete() override;
};
