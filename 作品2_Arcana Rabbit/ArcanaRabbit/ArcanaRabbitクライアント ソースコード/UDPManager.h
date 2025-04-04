#pragma once
#include "Member.h"
#include "EnemyData.h"
#include <list>
//=====================
// UDP���Ǘ�����}�l�[�W��
//=====================
class UDPManager
{
private:
	std::string m_ChatData;//�`���b�g�̃f�[�^
	std::list < std::string > m_MassagePool;//�T�[�o�[����̃f�[�^�𒙂߂Ă����ꏊ
	Member m_Member[20];
	std::list<EnemyData*> m_EnemyData;//�T�[�o�[���瑗���Ă����G�l�~�[�̃f�[�^
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

