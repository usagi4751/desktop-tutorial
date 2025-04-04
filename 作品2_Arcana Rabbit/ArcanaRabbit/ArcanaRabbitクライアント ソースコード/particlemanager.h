#pragma once
#include <list>
#include "Component.h"
#include "gameObject.h"
#include "particle.h"
#define MAXPARTICLE (4096)
//============================
// パーティクルを管理するマネージャ
//============================
class particleEmitter;
class ParticleManager :public GameObject
{
private:
	particle m_particle[MAXPARTICLE];
	std::list<particleEmitter*> m_Emitterlist;
	Component* m_Component{};
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
public:
	//初期化
	virtual void Init();
	//解放
	virtual void Uninit();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//リソースの生成1回だけ呼ぶ
	virtual void Create();
	//終了　最後に呼ぶ
	virtual void Release();
	//パーティクルの作成
	virtual void Addperticle(Particle_data data, particleEmitter* emitter = nullptr, Sorcletime sorcle = {});
	//パーティクルエミッターの作成
	virtual void AddEmitter(particleEmitter* emitter);
//	void AddEmitter(particleEmitter* emitter) { m_EmitterList.push_back(emitter); };
	

};

