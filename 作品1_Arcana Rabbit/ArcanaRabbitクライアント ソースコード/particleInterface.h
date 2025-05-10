#pragma once
#include "main.h"
class ParticleManager;
class particleEmitter;
//=============================================
//パーティクルマネージャのインターフェース
//=============================================
class ParticleInerface {
private:
	static ParticleManager* m_manager;
public:
	//マネージャの接続
	static void Link(ParticleManager* manager);
	//初期化
	static void Init();
	//解放
	static void Uninit();
	//エミッターの作成
	static void SetEmitter(particleEmitter* emitter);
};

