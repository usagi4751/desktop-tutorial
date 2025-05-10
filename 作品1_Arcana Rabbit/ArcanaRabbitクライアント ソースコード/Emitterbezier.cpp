#include "Emitterbezier.h"
#include "particlemanager.h"
#include "material.h"
#include "particle.h"
EmitterBezier::EmitterBezier(XMFLOAT3 pos, XMFLOAT3 rot)
	:particleEmitter(pos, rot) {
	m_life = 10000;
	m_vel = {};
}

void EmitterBezier::Uninit()
{

}

void EmitterBezier::Update()
{
	const int pointMAX = 4;
	XMFLOAT2 point[]{
		{0,0},
		{0,33},
		{-44,33},
		{-39,0},
	};
	XMFLOAT2		ControlPoint[4][pointMAX];		// 制御点
	XMFLOAT2		BezierPoint[120];
	// ポイントの初期化
	for (int i = 0; i < pointMAX; i++) {
		ControlPoint[0][i].x = point[i].x;		// 制御点(= [0][*])を初期化
		ControlPoint[0][i].y = point[i].y;
	}
	//16
	int		i, j, k, p;
	int qua = 100;
	int Qty = 119;

	// 全フレームにおけるベジェ曲線上のポイントを計算
	for (k = 0; k <= Qty; k++) {
		p = qua * k / Qty;
		// ３次なので３回
		for (i = 1; i <= 3; i++)
		{
			for (j = 0; j < pointMAX - i; j++)
			{
				ControlPoint[i][j].x = ((qua - p) * ControlPoint[i - 1][j].x + p * ControlPoint[i - 1][j + 1].x) / qua;
				ControlPoint[i][j].y = ((qua - p) * ControlPoint[i - 1][j].y + p * ControlPoint[i - 1][j + 1].y) / qua;
			}
		}
		// ０次の時の点を記憶
		BezierPoint[k].x = ControlPoint[3][0].x;
		BezierPoint[k].y = ControlPoint[3][0].y;
	}

	if (m_life > 0)
	{
		m_life--;
	}
	
		Particle_data data;
		data.m_life = 10;
		//data.m_Vel = { -velspeed + frand() * velspeed * 0.5f,-velspeed + frand() * velspeed * 0.5f ,-velspeed + frand() * velspeed * 0.5f };
		data.m_Vel = {
			0.0f,
			0.0f ,
			0.0f };

		data.scale = { 0.2f,0.2f };
		data.coler = { 1.0f,1.0f,1.0f,1.0f };
		data.endcoler = data.coler;
		data.endcoler.w = 1.0f;
		data.uv_u = { 0.0f ,0.0f};
		data.uv_v = { 1.0f,1.0f };
		data.tex = GetImage().m_particle_Ster;
		Sorcletime sorcre;
		sorcre.issorcle = false;
		sorcre.isNoVel = false;
		sorcre.isEmitter = false;
		sorcre.Rotate.y = 0;
		sorcre.Rotate.x = 0;
		sorcre.distance = 0.2f;
		sorcre.RotateVel.y = 0.1f;
		sorcre.RotateVel.x = 0.0f;
		for (int i = 0; i < 120; i++)
		{
			data.pos = m_Pos;
			data.pos.x += BezierPoint[i].x;
			data.pos.y += 0.2f;
			data.pos.z += BezierPoint[i].y;
			m_mamager->Addperticle(data, this, sorcre);
		}

		

	


}

bool EmitterBezier::Delete()
{
	if (m_life <= 0)
	{
		return true;
	}
	return false;
}
