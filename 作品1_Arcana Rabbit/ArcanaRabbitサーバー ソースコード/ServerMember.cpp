#include "ServerMember.h"
#include <nlohmann/json.hpp>
void Member::SetActive(bool in)
{
	m_IN = in;
}

void Member::SetName(std::string name)
{
	m_Name = std::string(name);
}

void Member::SetReg(SOCKADDR_IN so)
{
	m_From = so;
}

void Member::Update()
{
	//ステータスの更新など
}

void Member::SendData(SOCKET s, char* lpszMessage)
{

	sendto(s,
		lpszMessage,
		(int)strlen(lpszMessage),
		0,
		(SOCKADDR*)&m_From,
		(int)sizeof(m_From));
}
