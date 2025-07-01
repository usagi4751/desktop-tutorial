#pragma once

//========================================
// 接続、送る、受け取りだけをする
// 受け取ったのはUDPmanagerのm_MassagePoolに貯めてく
//========================================
#include "main.h"
#include <list>
class UDP
{
private:
	static char m_RecvBuf[1024];//送信する文字
	static char m_SzBuf[1024];//送信する文字
	static char m_SzServer[64];//IPアドレス
	static WSADATA m_WsaData;
	static SOCKET m_Socket;
	static SOCKADDR_IN m_Addrin;
	static HOSTENT* m_LpHostEnt;
	static unsigned int m_Addr;
	static int m_NRtn;
	static int m_NNo ;
	static u_short m_Port ;//portNo
	static char m_IPAddress[64] ;//IPアドレス
	static bool m_ServerAccessFlug;
	static std::string m_Name;

	static int m_MyIndex;//サーバー上での自分の番号

	static std::list < std::string >* m_MassagePool;
	static std::string* m_Chat;

	static short m_PacketNo;//パケットナンバー

	//前の送信データ（先頭コマンド）と前の前の送信データ（先頭コマンド）
	static char m_RecoveryCommand[2];
	//前の送信データ（本体コマンド）と前の前の送信データ（本体コマンド）
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
