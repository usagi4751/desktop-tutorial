#pragma once


#pragma once
#include "Component.h"
#include "gameObject.h"
class particleEmitter;
//短くするためにまとめた
struct Shader_Layout {
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* VertexLayout;
};
//サークル状にパーティクルを出すために作った
struct Sorcletime {//サークルパーティクル
	bool issorcle;//サークルを使うか
	bool isEmitter;//エミッターの座標を使うか
	bool isNoVel;//ベクトルを受けるか受けないか
	XMFLOAT2 Rotate;//座標の回転量
	XMFLOAT2 RotateVel;//座標の回転量
	float distance;//エミッターから離れてる距離
};
struct Particle_data
{
	XMFLOAT3 m_Vel;
	int m_life;
	XMFLOAT3 pos;//座標
	XMFLOAT2 scale;
	XMFLOAT4 coler;
	XMFLOAT4 endcoler;
	int tex;
	XMFLOAT2 uv_u;
	XMFLOAT2 uv_v;
};
class particle 
{
private:
	Particle_data m_data;
	int maxlife;//元のライフ
	XMFLOAT3 m_drawpos;//表示位置
	Sorcletime m_sorcler;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	Shader_Layout m_SL;
	particleEmitter* m_emitter = nullptr;//生成元のエミッター
public:
	virtual void crete(ID3D11PixelShader* pixelshader, ID3D11VertexShader* vertexshader, ID3D11InputLayout* vertexlayout);
	virtual void Release();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void SetParticle(Particle_data data, particleEmitter* emitter) {
		m_data = data; m_emitter = emitter; m_sorcler = {}; maxlife = data.m_life;
		Update();
	};
	virtual void SetParticle(Particle_data data, particleEmitter* emitter , Sorcletime sorcle) {
		m_data = data; m_emitter = emitter; m_sorcler = sorcle; maxlife = data.m_life;
		Update();
	};
	
	int Getlife() { return m_data.m_life; };
};

