#pragma once
#include "baseparticle.h"
#include "main.h"
class Particle_Flame:public Baseparticle
{
private:
	unsigned int m_life;//����
	unsigned int m_startlife;//�����̊J�n
	float		m_Gravity;//�d��
	float		m_AirResist;//��C��R
	float		m_Enlarge;//�t���[���P�ʂ̊g�嗦
	D3DXVECTOR2 m_U;//UV
	D3DXVECTOR2 m_V;//UV
public:
	Particle_Flame(int life, D3DXVECTOR3 pos, D3DXVECTOR3 vel,D3DXVECTOR3 size, D3DXCOLOR coler,float gravity,float AirResist, float Enlarge) :
		Baseparticle(pos, { 0.0f, 0.0f, 0.0f }, size, vel, coler), m_life(life) {
		m_U = D3DXVECTOR2(0.0f + (int)(frand() * 2.0f) * 0.5f, 0.0f + (int)(frand() * 2.0f) * 0.5f);
		m_V = D3DXVECTOR2(0.5f, 0.5f);
		m_startlife = life;
		m_Gravity = gravity;
		m_AirResist = AirResist;
		m_Enlarge = Enlarge;


		// �}�e���A���ݒ�
		ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
		GetMaterial()->Diffuse = RefColor();
		GetMaterial()->Ambient = RefColor();
		GetMaterial()->noTexSampling = 0;
		
	};
	~Particle_Flame() {};
	void Update(void) override {
		if (m_life > 0)
		{
			m_life--;
		}
		SetPos({ RefPos().x + RefVel().x,RefPos().y + RefVel().y, RefPos().z + RefVel().z });//�����𑫂�
		SetPos({ RefPos().x, RefPos().y - m_Gravity, RefPos().z });//�d��
		SetVel(RefVel() * m_AirResist);//��C��R
		SetScl({ RefScl().x + m_Enlarge ,RefScl().y + m_Enlarge ,RefScl().z + m_Enlarge });
		SetColor(D3DXCOLOR(
			RefColor().r,
			RefColor().g - 1.0f / (float)m_startlife,
			RefColor().b,
			RefColor().a - 1.0f / (float)m_startlife));
		if (RefPos().y < 0)
		{
			SetPos({ RefPos().x, 0, RefPos().z });
		}
		if (m_life <= 0)
		{
			SetUse(false);
		}
	};
	bool Life(void) override {
		if (m_life == 0)
		{
			SetUse(false);
			return  true;
		}
		return false;
	}
	
	HRESULT Init() override { return 0; };
	void Uninit() override {};
	void Draw(void) override ;
	

};

