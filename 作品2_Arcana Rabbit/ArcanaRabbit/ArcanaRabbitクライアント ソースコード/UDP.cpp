#include "UDP.h"
#include "main.h"





char			UDP::m_RecvBuf[1024]{};
char			UDP::m_SzBuf[1024]{};
char			UDP::m_SzServer[64]{};
WSADATA			UDP::m_WsaData{};
SOCKET			UDP::m_Socket{};
SOCKADDR_IN		UDP::m_Addrin{};
HOSTENT*		UDP::m_LpHostEnt{};
unsigned int	UDP::m_Addr{};
int				UDP::m_NRtn{};
int				UDP::m_NNo{};
u_short			UDP::m_Port{};
char			UDP::m_IPAddress[64]{};
int				UDP::m_MyIndex;
std::list < std::string >* UDP::m_MassagePool;
char			UDP::m_RecoveryCommand[2];
std::string		UDP::m_RecoveryText[2];
bool			UDP::m_ServerAccessFlug;
std::string		UDP::m_Name;
std::string*	UDP::m_Chat;
short			UDP::m_PacketNo;
void UDP::Init()
{
	m_NRtn = WSAStartup(MAKEWORD(1, 1), &m_WsaData);
	if (m_NRtn != 0) {
		MessageBox(GetWindow(), TEXT("WASStartupに失敗しました"), TEXT("エラー"), MB_OKCANCEL);
		return;

	}
	//初期化でコマンド無しの状態にする
	m_RecoveryCommand[0] = -1;
	m_RecoveryCommand[1] = -1;
	m_PacketNo = 1;
}

void UDP::UnInit()
{
	WSACleanup();
}

bool UDP::ServerAccess()
{

	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket < 0) {
		WSACleanup();
		MessageBox(GetWindow(), TEXT("ソケットエラーです"), TEXT("エラー"), MB_OKCANCEL);
		return false;
	}
	m_LpHostEnt = gethostbyname(m_IPAddress);
	if (m_LpHostEnt == NULL) {
		m_Addr = inet_addr(m_IPAddress);
		m_LpHostEnt = gethostbyaddr((char*)&m_Addr, 4, AF_INET);
		if (m_LpHostEnt == NULL) {
			MessageBox(GetWindow(), TEXT("サーバーが識別されませんでした"), TEXT("エラー"), MB_OKCANCEL);
			return false; 
		}
	}


	memset(&m_Addrin, 0, sizeof(m_Addrin));
	memcpy(&(m_Addrin.sin_addr),
		m_LpHostEnt->h_addr_list[0],
		m_LpHostEnt->h_length);
	m_Addrin.sin_port = htons(m_Port);
	m_Addrin.sin_family = AF_INET;

	 int ret = WSAAsyncSelect(m_Socket, GetWndprccWindow(), MY_MSG, FD_READ | FD_WRITE);

	 memset(m_SzBuf, '\0', 1024);
	 m_SzBuf[0] = 1;
	 int copy = 1;
	 for (char a : m_Name) {
		 if (copy < 1024)
		 {
			 m_SzBuf[copy] = a; 
			 copy++;
		 }
	 
	 }
	 sendto(m_Socket, m_SzBuf, (int)strlen(m_SzBuf) + 1, 0,
		 (LPSOCKADDR)&m_Addrin, sizeof(m_Addrin));
	 return true;
	//sendto(m_Socket, m_SzBuf, (int)strlen(m_SzBuf) + 1, 0,(LPSOCKADDR)&m_Addrin, sizeof(m_Addrin));
	


}

void UDP::ServerExit()
{
	if (m_ServerAccessFlug == true)
	{
		memset(m_SzBuf, '\0', 1024);
		m_SzBuf[0] = -1;
		m_SzBuf[1] = m_MyIndex;
		sendto(m_Socket, m_SzBuf, (int)strlen(m_SzBuf) + 1, 0,
			(LPSOCKADDR)&m_Addrin, sizeof(m_Addrin));
	}
	
}

void UDP::SetIPAddress(std::string string)
{
	string.copy(m_IPAddress, 64);
}

void UDP::Send(int Command, std::string CommandString)
{
	//テスト
	char cmd[2];
	std::string NowPac1;
	std::string RecvPac1;
	std::string RecvPac2;

	cmd[0] = Command;
	cmd[1] = '\0';
	NowPac1 = cmd;
	cmd[0] = m_RecoveryCommand[0];
	cmd[1] = '\0';
	RecvPac1 = cmd;
	cmd[0] = m_RecoveryCommand[1];
	cmd[1] = '\0';
	RecvPac2 = cmd;


	int Recv1pos = -1;
	int Nowpos = -1;
	NowPac1 += CommandString;
	RecvPac1 += m_RecoveryText[0];
	RecvPac2 += m_RecoveryText[1];


	Recv1pos = 6 + RecvPac2.size();
	Nowpos = 6 + RecvPac2.size() + RecvPac1.size();

	//先頭データ
	char a[8];
	a[0] = 2;//コマンド
	a[1] = m_MyIndex;//自分の保存構造体番号
	a[2] = m_PacketNo;//パケロス復元用ID 1～255 pacetID 
	a[3] = -1;
	if ((Recv1pos) > 254)
	{
		a[3] = (Recv1pos) / 254;
	}
	a[4] = (Recv1pos) % 254;
	a[5] = -1;
	if ((Nowpos) > 254)
	{
		a[5] = (Nowpos) / 254;
	}
	a[6] = (Nowpos) % 254;
	a[7] = '\0';//端

	std::string aa = a;
	aa += RecvPac2;
	aa += RecvPac1;
	aa += NowPac1;
	m_PacketNo++;
	if (m_PacketNo > 127)
	{
		m_PacketNo = 1;
	}
		m_RecoveryCommand[1] = m_RecoveryCommand[0];
		m_RecoveryText[1] = m_RecoveryText[0];

		m_RecoveryCommand[0] = Command;
		m_RecoveryText[0] = CommandString;

	

	memset(m_SzBuf, '\0', 1024);
	int i = 0;
	for (char a : aa)
	{
		if (i < 1024)
		{
			m_SzBuf[i] = a;
			i++;
		}
	
	}
	sendto(m_Socket, m_SzBuf, (int)strlen(m_SzBuf) + 1, 0,(LPSOCKADDR)&m_Addrin, sizeof(m_Addrin));

}

void UDP::ChatSend(std::string CommandString)
{
	memset(m_SzBuf, '\0', 1024);
	int i = 1;
	m_SzBuf[0] = 3;
	m_SzBuf[1] = '\0';
	for (char a : CommandString)
	{
		if (i < 1024)
		{
			m_SzBuf[i] = a;
			i++;
		}

	}
	sendto(m_Socket, m_SzBuf, (int)strlen(m_SzBuf) + 1, 0, (LPSOCKADDR)&m_Addrin, sizeof(m_Addrin));
}

void UDP::Recv()
{
	m_NNo =  (int)sizeof(m_Addrin);//メモリサイズ
	m_NRtn = recvfrom(m_Socket,
		m_RecvBuf,
		(int)sizeof(m_RecvBuf) - 1,
		0,
		(SOCKADDR*)&m_Addrin,
		&m_NNo);

	 if (m_NRtn == SOCKET_ERROR) {
		 MessageBox(GetWindow(), TEXT("受信エラーです"), TEXT("エラー"), MB_OKCANCEL);
		 closesocket(m_Socket);
	 }
	 m_RecvBuf[m_NRtn] = '\0';//szBufの文字の一番最後を終わりにする
	 if (m_RecvBuf[0] == 1)
	 {
		 m_MyIndex = m_RecvBuf[1];
		 m_ServerAccessFlug = true;
	 }
	 else if (m_RecvBuf[0] == 6)
	 {
		 std::string chat = m_RecvBuf;
		 *m_Chat += chat.substr(1);
	 }
	 else
	 {
		 m_MassagePool->push_back(m_RecvBuf);
	 }

}
