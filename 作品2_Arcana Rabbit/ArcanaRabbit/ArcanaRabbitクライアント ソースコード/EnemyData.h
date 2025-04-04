#pragma once
#include "main.h"
//============================
//敵のデータと処理のクラス
//============================

class EnemyData 
{
private:
	bool m_Active;
	int m_Id;//エネミーの番号
	char m_Uuid[32];//エネミーの個体ID
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	int m_FreezeTime;
	bool m_Deth;
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetActive(bool active) { m_Active = active; };
	void SetUUID(char* id);
	void SetID(int id) { m_Id = id; };
	void SetPosition(XMFLOAT3 pos) { m_FreezeTime = 0; m_Position = pos; };
	void SetRotation(XMFLOAT3 rot) { m_Rotation = rot; };
	void SetDeth() { m_Deth = true; }

	bool GetDestory() { if (m_FreezeTime > 900 || m_Deth == true) { return true; } return false; }
	char* GetUUID();
	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	void AddDamage(float damage);


};

