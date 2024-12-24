//=============================================================================
//
// �p�[�e�B�N������ [sprite.cpp]
// Author : 
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "particle.h"
#include <iostream>
#include <cmath>

PARTICLE particle[MAXPARTICLE];
int g_partex[2] = {};
enum
{
	FLAME = 1,
};
//********************************************************
// ����������
//********************************************************
void Initparticle(void) {
	g_partex[0] = LoadTexture((char*)"data/TEXTURE/glint.png");
	g_partex[1] = LoadTexture((char*)"data/TEXTURE/crit.hit.png");
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		particle[i].use = false;
		particle[i].posx = 0.0f;
		particle[i].posy = 0.0f;
		particle[i].di = 0.0f;
		particle[i].lp = 0.0f;
		particle[i].na = 0;
		particle[i].re = 0.0f;
		particle[i].si= 0.0f;
		particle[i].sp = 0.0f;
		particle[i].time = 0.0f;
		particle[i].we= 0.0f;
		particle[i].r = 1.0f; 
		particle[i].g = 1.0f;
		particle[i].b = 1.0f;
	}
}
void Uninitparticle(void) {

}
void Updateparticle(void) {
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		if (particle[i].use == true)
		{
			particle[i].posx += particle[i].sp * std::cos(PAI * particle[i].di / 1) ;
			particle[i].posy += particle[i].sp * std::sin(PAI * particle[i].di / 1);
			particle[i].sp = particle[i].sp * (1 - particle[i].re);
		}
		if (particle[i].time >= 0)
		{
			particle[i].time -= 1.0f /60.0f;
		}
		if (particle[i].time < 0)
		{
			particle[i].use = false;
		}

	}
}
void Drawparticle(void) {
	for (int i = 0; i < MAXPARTICLE; i++)
	{
		if (particle[i].use == true)
		{
			DrawSpriteColorRotate(g_partex[particle[i].na],
				particle[i].posx, particle[i].posy,
				particle[i].si, particle[i].si,
				0.0f, 0.0f, 1.0f, 1.0f,
				particle[i].r, particle[i].g, particle[i].b, 1.0f,
				0);
		}

	}
}
void setparticle(
	int pa_na,
	float pa_x, float pa_y,   //�p�[�e�B�N�����W
	float pa_dx, float pa_dy,//�p�[�e�B�N���������W�͈�
	float pa_sp,//�p�[�e�B�N�����x
	int pa_nu,//�p�[�e�B�N��������
	float pa_si,//�T�C�Y
	//�����܂ł͏���
	float pa_di, //����
	float pa_co , //������
	float pa_re,//������
	float pa_we,//�d��
	float pa_lp,//����
	float pa_lr ,//�\�����ԗ�
	float pa_spr ,//�X�s�[�h�����_��
	float pa_sir,//�T�C�Y�����_��
	float pa_r  ,//�J���[R
	float pa_g ,//�J���[G
	float pa_b  //�J���[B
){
	if (pa_spr < 0)
	{
		pa_spr = 0.0f;
	}
	if (pa_sir < 0)
	{
		pa_sir=  0.0f;
	}
	if (pa_lp < 0)
	{
		pa_lp = 2.0f;
	}
	if (pa_lr < 0)
	{
		pa_lr = 0.0f;
	}
	for (int nu = 0; nu < pa_nu; nu++)
	{
		for (int i = 0; i < MAXPARTICLE; i++)
		{
			if (particle[i].use == false)
			{

				particle[i].na = pa_na;
				particle[i].posx = pa_x - pa_dx + (pa_dx * 2) * frand();
				particle[i].posy = pa_y - pa_dy + (pa_dy * 2) * frand();
				particle[i].sp = pa_sp - (pa_sp * pa_spr * frand());
				particle[i].si = pa_si - (pa_si * pa_sir  * frand());
				particle[i].di = pa_di - pa_co+ (pa_co * 2 * frand());
				particle[i].time = pa_lp - (pa_lp * pa_lr  * frand());
				particle[i].re = pa_re;
				particle[i].use = true;
				particle[i].r = pa_r;
				particle[i].g = pa_g;
				particle[i].b = pa_b;

				break;
			}
		}
	}
	
}

