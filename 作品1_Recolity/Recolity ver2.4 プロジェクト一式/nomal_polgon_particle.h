#pragma once
#pragma once
#include "baseparticle.h"
#include "main.h"
class Nomal_Polgon_Particle :public Baseparticle
{
private:
	unsigned int m_life;//����
	unsigned int m_startlife;//�����̊J�n
	float		m_Gravity;//�d��
	float		m_AirResist;//��C��R
	float		m_Enlarge;//�t���[���P�ʂ̊g�嗦
	bool		m_graoudstop;//�n�ʂɂ����Ƃ��Ɏ~�܂邩

	D3DXVECTOR2 m_U;//UV
	D3DXVECTOR2 m_V;//UV
public:
	Nomal_Polgon_Particle(int life, D3DXVECTOR3 pos, D3DXVECTOR3 vel, D3DXVECTOR3 size, D3DXCOLOR coler, float gravity, float AirResist, float Enlarge, bool groudstop = false);
		
	~Nomal_Polgon_Particle() = default;
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

