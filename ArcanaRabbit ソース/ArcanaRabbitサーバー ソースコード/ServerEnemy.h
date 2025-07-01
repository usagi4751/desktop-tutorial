#pragma once

#include "showobjext.h"
#include "main.h"
class ServerEnemy
{
private:
	char m_Uuid[32];
	int m_EnemyID;
	float m_Helth;
	float m_MaxHelth;
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);


	//テスト用
	ShowObject* m_model;
public:
	ServerEnemy(int EnemyID, float MaxHelth, XMFLOAT3 Position) :m_EnemyID(EnemyID), m_MaxHelth(MaxHelth), m_Helth(MaxHelth), m_Position(Position) {};

	void SetUUID(char* uuid);
	void SetEnemyID(int id) { m_EnemyID = id; }
	void SetPosition(XMFLOAT3 pos) { m_Position = pos; }
	void SetRotation(XMFLOAT3 rot) { m_Rotation = rot; }
	void AddDamage(float damage) { if (damage > 0) { m_Helth -= damage; } }
	void SetHelth(float helth) {m_Helth = helth;}
	void SetMaxHelth(float maxhelth) { m_MaxHelth = maxhelth; }

	int GetEnemyID() { return m_EnemyID; }
	float GetHelth() { return m_Helth; }
	float GetMaxHelth() { return m_MaxHelth; }
	bool GetActive() { return m_Helth > 0 ?  true : false; };
	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3  GetRotation() { return m_Rotation; }
	char* GetUUID() { return m_Uuid; }


	virtual void Init() ;
	virtual void Uninit() ;
	virtual void Update() ;


	//テスト用
	void Draw() ;
};	

