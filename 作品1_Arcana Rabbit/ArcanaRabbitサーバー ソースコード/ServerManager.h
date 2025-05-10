#pragma once
#include "ServerMember.h"
#include "ServerEnemy.h"
#include <list>

//テストで追加
#include "draw2d_Manager.h"


//=========================================
//受信ルール
//１バイト目 送信時の識別コード
//初回 操作 の判別
//２バイト目 自身の格納されてる構造体の番号
//0	～ SERVERMAXまでの番号　初回なら振り分ける
//３バイト目 パケロス復元用の番号
//４バイト目～５バイト目
//復元メッセージの先頭番号
//６バイト目～７バイト目
//今回のメッセージの先頭番号
//=========================================

#define SERVERMAX (20)
enum MassageName
{
	AcsessMassage = 1,
	Position,
	AcssesFlug_True,
	AcssesFlug_False,
	Name,
	Chat,
	EnemyMassage,
	DethEnemyMassage,
};
struct MYDATA
{
	int startdata = -1;//WSAStartupの戻り値
	char ipadress[64];//IPアドレス
	u_short port = 4751;//ポート番号
	SOCKET socket;//自身のソケット
	SOCKADDR_IN addr_in;
	WSADATA wasadata;//wasadata

	int  addr_in_size;//addrのサイズ
	int  ret;//エラー受信
	char recvmassage[1024];//Recvで受け取った文字
};
class ServerManager
{
private:
	static Member m_Member[SERVERMAX];
	static std::list<ServerEnemy*> m_EnemyList;

	static std::list<std::string> m_MassagePool;	//全ての受信データ
	
	static MYDATA m_Mydata;

	static SOCKADDR_IN m_Insockaddr;
	//全体送信
	static void AllSend(char* lpszMessage);

	//単体送信
	static void SingleSend(int n,char* lpszMessage);
	//接続
	static int register_user(SOCKADDR_IN sa);
	//切断
	static void exit_user(int n );

	//**************************************
	// テスト用
	//**************************************
	static UI_Text rettext;


public:
	ServerManager() {};
	 ~ServerManager() {};

	//更新処理
	//プレイヤー全員のパラメーターや移動などの更新
	static void Init();
	static void UnInit();
	static void Update();

	//受信機能
	//初回接続
	//チャット
	//サーバーから抜ける
	//コマンド
	//の振り分けをする
	static void RecvMassage();

	//プレイヤーの情報のゲッター
	static Member* GetMember(int n);

	static void CreateEnemy(int EnemtID,float MaxHelth,XMFLOAT3 Position , XMFLOAT3 Rotation);



	//**************************************
	// テスト用
	//**************************************
	static std::list<ServerEnemy*>* GetEnemyList() { return &m_EnemyList; }
};


