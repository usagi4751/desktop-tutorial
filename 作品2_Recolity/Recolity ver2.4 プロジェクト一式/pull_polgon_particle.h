#pragma once
#include "baseparticle.h"
#include "material.h"
#include "main.h"
class Pull_Polgon_Particle :public Baseparticle
{
private:
	D3DXVECTOR3 m_PullPoint;//�����񂹂�����W
	float		berak_circle;//�����񂹂�ꂽ���ɂǂ̂��炢�̋����ŏ����邩(�}�C�i�X�l�Ŗ�����)
	unsigned int m_life;//����
	float		m_AirResist;//��C��R
	float		m_Enlarge;//�t���[���P�ʂ̊g�嗦
	int* m_tex;//�e�N�X�`��
	D3DXVECTOR2 m_U;//UV
	D3DXVECTOR2 m_V;//UV
public:
	//=====================================
	// life����
	// pos�����ʒu
	// size�p�[�e�B�N���̑傫��
	// coler�F
	// AirResist��C��R0�`1
	// Enlarge�t���[�����̊g��
	//=====================================
	Pull_Polgon_Particle(int life, D3DXVECTOR3 pos, D3DXVECTOR3 goal, D3DXVECTOR3 size, D3DXCOLOR coler, float spd ,float delrange, float AirResist, float Enlarge, int* tex);

	~Pull_Polgon_Particle() = default;
	void Update(void) override;
	bool Life(void) override {
		if (m_life == 0)
		{
			return  true;
		}
		return false;
	}

	HRESULT Init() override { return 0; };
	void Uninit() override {};
	void Draw(void) override;


};

