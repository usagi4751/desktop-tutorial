#pragma once
#include "showobjext.h"
//==================================
// エネミーの表示基底クラス
//==================================
class BaseEnemyData
{
private:
	float m_HitboxSize;

	//描画処理
	ShowObject* m_Model;
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw( XMFLOAT3 pos, XMFLOAT3 rot);
	//モデル読み込み
	ShowObject* GetShowObject() { return m_Model; }
	float GethitBoxSize() { return m_HitboxSize; };
	void SethitBoxSize(float size) { m_HitboxSize = size; };
};


