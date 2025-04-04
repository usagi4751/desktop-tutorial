#include "ServerManager.h"
#include "main.h"
#include "input.h"
Member					ServerManager::m_Member[SERVERMAX]{};
MYDATA					ServerManager::m_Mydata;
std::list<std::string>	ServerManager::m_MassagePool;
UI_Text					ServerManager::rettext;
SOCKADDR_IN				ServerManager::m_Insockaddr;
std::list<ServerEnemy*> ServerManager::m_EnemyList;
//ロスしたパケットを出す
//int packet 今回のパケットの番号
//int memberpacket　メンバーのパケット番号
//戻り値　ロスしたパケットの数
int LossPacket(int packet, int memberpacket);
void CreateUUID(char* uuid);
void ServerManager::Init()
{
	m_Mydata.startdata = WSAStartup(MAKEWORD(1, 1), &m_Mydata.wasadata);
	if (m_Mydata.startdata != 0) {
		MessageBox(GetWindow(), TEXT("WASStartupに失敗しました"), TEXT("エラー"), MB_OKCANCEL);
		return;
	}

	m_Mydata.socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Mydata.socket < 0) {
		MessageBox(GetWindow(), "socket失敗", "エラー", MB_OK);
	}

	memset(&m_Mydata.addr_in, 0, sizeof(m_Mydata.addr_in));
	m_Mydata.addr_in.sin_family = AF_INET;
	m_Mydata.addr_in.sin_port = htons(m_Mydata.port);
	m_Mydata.addr_in.sin_addr.s_addr = htonl(INADDR_ANY);

	m_Mydata.ret = bind(m_Mydata.socket, (LPSOCKADDR)&m_Mydata.addr_in, (int)sizeof(m_Mydata.addr_in));
	if (m_Mydata.ret == SOCKET_ERROR) {
		MessageBox(GetWindow(), "bindエラーです", "エラー", MB_OK);
		closesocket(m_Mydata.socket);
	}


	m_Mydata.ret = WSAAsyncSelect(m_Mydata.socket, GetWndprccWindow(), MY_MSG, FD_READ);

	if (m_Mydata.ret == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			MessageBox(GetWindow(), "非同期化失敗", "エラー", MB_OK);
			int errer;
			errer = closesocket(m_Mydata.socket);
			if (errer == SOCKET_ERROR)
			{
				MessageBox(GetWindow(),"ソケットのクローズ失敗", "エラー",MB_OK);
			}
		}
	}
	rettext.Link(Draw2D_Manager::AddTEXT());
	rettext.SetRect({ 0,0,1920,1080 });
	rettext.SetColer({ 1.0f,1.0f,1.0f,1.0f });

	
}

void ServerManager::UnInit()
{
	for (ServerEnemy* e : m_EnemyList)
	{
		e->Uninit();
		delete e;
	}
	m_EnemyList.clear();
	WSACleanup();
}

void ServerManager::Update()
{
	std::string text;
	text = "";
	//enemyの更新
	for (ServerEnemy* e : m_EnemyList)
	{
		e->Update();

		//1-32 uuid

		char enemy[1024] = {};
		enemy[0] = EnemyMassage;
		enemy[1] = e->GetEnemyID() + 1;
		for (int i = 0; i < 32; i++)
		{
			enemy[2 + i] = e->GetUUID()[i] + 1;
		}
		std::string str;
		str += std::to_string(e->GetPosition().x) + " ";
		str += std::to_string(e->GetPosition().y) + " ";
		str += std::to_string(e->GetPosition().z) + " ";
		str += std::to_string(e->GetRotation().y) + " ";

		int l = 34;
		for (char a : str)
		{
			if (l < 1024)
			{
				enemy[l] = a;
				l++;
			}
		}
		AllSend(enemy);
	}

	m_EnemyList.remove_if([](ServerEnemy* e) { 
		if (!e->GetActive()) {
			char enemy[1024] = {};
			enemy[0] = DethEnemyMassage;
			enemy[1] = e->GetEnemyID() + 1;
			for (int i = 0; i < 32; i++)
			{
				enemy[2 + i] = e->GetUUID()[i] + 1;
			}
			AllSend(enemy);
		}
		return !e->GetActive(); });
	//メッセージの処理
	for (std::string t :m_MassagePool)
	{
		
		int index = t.at(1) - 1; //格納されてる場所
		int lossPacket = LossPacket(t.at(2),m_Member[index].GetConnectID()); // ロスしてるパケット
		m_Member[index].SetconnectID(t.at(2));
		text += "ロスパケット" + std::to_string(lossPacket) + "\n";
		int recpos = t.at(3) > 0 ? t.at(3)* 254 + t.at(4) : t.at(4);
		int nowpos = t.at(5) > 0 ? t.at(5) * 254 + t.at(6) : t.at(6);
		std::string Massage[3] = {};
		//パケットを分ける
		{
			if (lossPacket > 0)
			{
				if (lossPacket > 1)
				{
					Massage[0] = t.substr(7, recpos - 7);//2個前のパケット
				}
				Massage[1] = t.substr(recpos+1, nowpos - recpos);//1個前のパケット
			}
			Massage[2] = t.substr(nowpos + 1);
		}
		
		//処理
		for (int i = 0; i < 3; i++)
		{
			if (Massage[i].size() != 0)
			{
				if (Massage[i].at(0) == 1)
				{
					XMFLOAT3 pos = {};
					float rot = 0;
					int next = 1 ;
					int old = next;
					next = Massage[i].find(' ', old);
					int len = next - old;
					pos.x = std::stof(Massage[i].substr(old, len).c_str());
					old = next;
					next = Massage[i].find(' ', old + 1);
					len = next - old;
					pos.y = std::stof(Massage[i].substr(old, len).c_str());
					old = next;
					next = Massage[i].find(' ', old + 1);
					len = next - old;
					pos.z = std::stof(Massage[i].substr(old, len).c_str());
					old = next;
					next = Massage[i].find(' ', old + 1);
					len = next - old;
					rot = std::stof(Massage[i].substr(old, len).c_str());
					m_Member[index].SetPosition(pos);
					m_Member[index].SetRotate(rot);

					text += "Pac:" + std::to_string(i) + "\n";
					text += "Pos: X" + std::to_string(m_Member[index].GetPosition().x) + " Y " + std::to_string(m_Member[index].GetPosition().y) + " Z " + std::to_string(m_Member[index].GetPosition().z) + "\n";
				}
				if (Massage[i].at(0) == 2)
				{
					float damage;
					char uuid[32] = {};
					for (int l= 0; l < 32; l++)
					{
						uuid[l] = Massage[i].at(l + 1) - 1;
					}
					int len = Massage[i].find(' ', 33);
					damage = std::stof(Massage[i].substr(33, len).c_str());
					bool searchflug ;
					for (ServerEnemy* e : m_EnemyList) {
						for (int i = 0; i < 32; i++)
						{
							searchflug = true;
							if (e->GetUUID()[i] != uuid[i])
							{
								searchflug = false;
							}
							if (searchflug == true)
							{
								e->AddDamage(damage);
								break;
							}
						}
					}

				}
			}
		}
		

		
	
		
	}
	m_MassagePool.clear();

	//アクセスしてる人に他のプレイヤーなどのデータを送る
	char sendcommand[1024] = {};
	for (int i = 0; i < SERVERMAX; i++)
	{
		if (m_Member[i].GetActive() == true)
		{
			//プレイヤーの座標と回転情報を送る
			{
			memset(sendcommand, '\0', 1024);
			sendcommand[0] = Position;
			sendcommand[1] = i + 1;
			sendcommand[2] = '\0';
			std::string str;
			str += sendcommand;
			str += std::to_string(m_Member[i].GetPosition().x) + " ";
			str += std::to_string(m_Member[i].GetPosition().y) + " ";
			str += std::to_string(m_Member[i].GetPosition().z) + " ";
			str += std::to_string(m_Member[i].GetRotate()) + " ";

			int l = 0;
			for (char a : str)
			{
				if (l < 1024)
				{
					sendcommand[l] = a;
					l++;
				}

			}
			AllSend(sendcommand);
		}
			//接続しているかを送る
			{
				char acsses[1024] = {};
				acsses[0] = AcssesFlug_True;
				acsses[1] = i + 1;
				acsses[2] = '\0';
				AllSend(acsses);
			}
			//名前の送信
			{
				char name[1024] = {};
				name[0] = Name;
				name[1] = i + 1;
				name[2] = '\0';
				int k = 2;
				for (char a : m_Member[i].GetName())
				{
					if (k < 1024)
					{
						name[k] = a;
						k++;
					}

				}
				AllSend(name);
			}
		}
		else
		{
			//アクティブではなかったらアクセスしていないと送る
			{
				char acsses[1024] = {};
				acsses[0] = AcssesFlug_False;
				acsses[1] = i + 1;
				acsses[2] = '\0';
				AllSend(acsses);
			}
		}
	}






	//デバック表示
	text += "X:" + std::to_string(m_Member[0].GetPosition().x) + "\nY:" + std::to_string(m_Member[0].GetPosition().y) + "\nz:" + std::to_string(m_Member[0].GetPosition().z) + "\n";
	for (int i = 0; i < 20; i++)
	{
		text += std::to_string(i) + std::to_string( m_Member[i].GetActive()) + " ";
	}
	rettext.SetText(text);


	
	
	
}

void ServerManager::RecvMassage()
{
	m_Mydata.addr_in_size = (int)sizeof(m_Insockaddr);//メモリサイズ
	//受け取り
	m_Mydata.ret = recvfrom(m_Mydata.socket,
		m_Mydata.recvmassage,
		(int)sizeof(m_Mydata.recvmassage) - 1,
		0,
		(SOCKADDR*)&m_Insockaddr,
		&m_Mydata.addr_in_size);
	//受信エラーで閉じる
	if (m_Mydata.ret  == SOCKET_ERROR)
	{
		 closesocket(m_Mydata.socket);
		MessageBox(GetWindow(), TEXT("受信エラーです"), TEXT("エラー"), MB_OKCANCEL);
	}
	//文字の一番最後を終わりにする
	m_Mydata.recvmassage[m_Mydata.ret] = '\0';

	//初回のアクセス
	//初回なら保存indexを返す
	if (m_Mydata.recvmassage[0] == 1)
	{
		int  index = 0;
		index = register_user(m_Insockaddr);//保存場所を取得
		//保存場所を送信
		char a[1024];
		a[0] = AcsessMassage;//送信番号
		a[1] = index + 1;//保存場所
		a[2] = '\0';
		SingleSend(index,a);
		std::string name = m_Mydata.recvmassage;
		name.erase(0, 1);
		m_Member[index].SetName(name);
	}
	else if (m_Mydata.recvmassage[0] == 3)
	{
		char ChatData[1024] = {};
		ChatData[0] = Chat;
		for (int i = 1; i < 1024; i++)
		{
			ChatData[i] = m_Mydata.recvmassage[i];
		}
		AllSend(ChatData);
	}
	else if (m_Mydata.recvmassage[0] == -1)
	{
		int index = m_Mydata.recvmassage[1];
		exit_user(index - 1);
	}
	else
	{
		//プールに追加する
		m_MassagePool.push_back(m_Mydata.recvmassage);
	}

}

Member* ServerManager::GetMember(int n)
{
	return &m_Member[n];
}

void ServerManager::CreateEnemy(int EnemtID, float MaxHelth, XMFLOAT3 Position, XMFLOAT3 Rotation)
{
	ServerEnemy* enemy = new ServerEnemy(EnemtID, MaxHelth, Position);
	enemy->SetRotation(Rotation);
	char uuid[32];
	CreateUUID(uuid);
	enemy->SetUUID(uuid);
	enemy->Init();

	m_EnemyList.push_back(enemy);
}


void ServerManager::AllSend(char* lpszMessage)
{
	for (int  i = 0; i < SERVERMAX; i++)
	{
		if (m_Member[i].GetActive())
		{
			m_Member[i].SendData(m_Mydata.socket, lpszMessage);
		}
	}
}

void ServerManager::SingleSend(int n, char* lpszMessage)
{
	if (m_Member[n].GetActive())
	{
		m_Member[n].SendData(m_Mydata.socket, lpszMessage);
	}
}

int ServerManager::register_user(SOCKADDR_IN sa)
{
	int index = -1;
	for (int i = 0; i < SERVERMAX; i++)
	{
		if (m_Member[i].GetActive() == false)
		{
			m_Member[i].SetActive(true);
			m_Member[i].SetReg(sa);
			index = i;
			break;
		}
	}
	return index;
}

void ServerManager::exit_user(int n)
{
	m_Member[n].SetActive(false);
}

int LossPacket(int packet, int memberpacket)
{
	int ret = packet - memberpacket - 1;
	if (ret < -125)
	{
		ret += 127;
	}
	if (ret > 2)
	{
		ret = 2;
	}
	return ret;
}

void CreateUUID(char* uuid)
{
	for (int i = 0; i < 32; i++)
	{
		uuid[i] = (int)rand() % 16;
	}
}
