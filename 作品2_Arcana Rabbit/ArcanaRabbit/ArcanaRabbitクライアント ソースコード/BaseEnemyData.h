#pragma once
#include "showobjext.h"
//==================================
// �G�l�~�[�̕\�����N���X
//==================================
class BaseEnemyData
{
private:
	float m_HitboxSize;

	//�`�揈��
	ShowObject* m_Model;
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw( XMFLOAT3 pos, XMFLOAT3 rot);
	//���f���ǂݍ���
	ShowObject* GetShowObject() { return m_Model; }
	float GethitBoxSize() { return m_HitboxSize; };
	void SethitBoxSize(float size) { m_HitboxSize = size; };
};


