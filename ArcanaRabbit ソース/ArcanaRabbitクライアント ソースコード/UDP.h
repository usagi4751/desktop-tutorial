#pragma once

//========================================
// �ڑ��A����A�󂯎�肾��������
// �󂯎�����̂�UDPmanager��m_MassagePool�ɒ��߂Ă�
//========================================
#include "main.h"
#include <list>
class UDP
{
private:
	static char m_RecvBuf[1024];//���M���镶��
	static char m_SzBuf[1024];//���M���镶��
	static char m_SzServer[64];//IP�A�h���X
	static WSADATA m_WsaData;
	static SOCKET m_Socket;
	static SOCKADDR_IN m_Addrin;
	static HOSTENT* m_LpHostEnt;
	static unsigned int m_Addr;
	static int m_NRtn;
	static int m_NNo ;
	static u_short m_Port ;//portNo
	static char m_IPAddress[64] ;//IP�A�h���X
	static bool m_ServerAccessFlug;
	static std::string m_Name;

	static int m_MyIndex;//�T�[�o�[��ł̎����̔ԍ�

	static std::list < std::string >* m_MassagePool;
	static std::string* m_Chat;

	static short m_PacketNo;//�p�P�b�g�i���o�[

	//�O�̑��M�f�[�^�i�擪�R�}���h�j�ƑO�̑O�̑��M�f�[�^�i�擪�R�}���h�j
	static char m_RecoveryCommand[2];
	//�O�̑��M�f�[�^�i�{�̃R�}���h�j�ƑO�̑O�̑��M�f�[�^�i�{�̃R�}���h�j
	static std::string m_RecoveryText[2];

public:
	UDP() = default;
	~UDP() = default;
	static void Init();
	static void UnInit();

	static bool ServerAccess();
	static void ServerExit();
	static void SetPort(u_short port) { m_Port = port; };
	static void SetIPAddress(std::string string);
	static void SetName(std::string name) { m_Name = name; };

	static void Send(int Command,std::string CommandString);
	static void ChatSend(std::string CommandString);
	static void Recv();
	static void Link(std::list < std::string >* pool) { m_MassagePool = pool; }
	static void LinkChat(std::string* str) { m_Chat = str; }
	static int GetMyIndex() { return m_MyIndex; };
	

	static bool AccessFlug() { return m_ServerAccessFlug; };
	
};
