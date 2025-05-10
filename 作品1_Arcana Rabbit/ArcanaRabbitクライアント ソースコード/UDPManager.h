#pragma once
#include "Member.h"
#include "EnemyData.h"
#include <list>
//=====================
// UDPを管理するマネージャ
//=====================
class UDPManager
{
private:
	std::string m_ChatData;//チャットのデータ
	std::list < std::string > m_MassagePool;//サーバーからのデータを貯めておく場所
	Member m_Member[20];
	std::list<EnemyData*> m_EnemyData;//サーバーから送られてきたエネミーのデータ
public:
	UDPManager() {};
	~UDPManager() {};
	void Init();
	void UnInit();
	void Update();
	void Draw();
	std::string GetChatData() { return m_ChatData; }
	std::list<EnemyData*>* GetEnemyList() { return &m_EnemyData; }
};

