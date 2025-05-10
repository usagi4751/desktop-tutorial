#pragma once
#include "ServerMember.h"
#include "ServerEnemy.h"
#include <list>

//�e�X�g�Œǉ�
#include "draw2d_Manager.h"


//=========================================
//��M���[��
//�P�o�C�g�� ���M���̎��ʃR�[�h
//���� ���� �̔���
//�Q�o�C�g�� ���g�̊i�[����Ă�\���̂̔ԍ�
//0	�` SERVERMAX�܂ł̔ԍ��@����Ȃ�U�蕪����
//�R�o�C�g�� �p�P���X�����p�̔ԍ�
//�S�o�C�g�ځ`�T�o�C�g��
//�������b�Z�[�W�̐擪�ԍ�
//�U�o�C�g�ځ`�V�o�C�g��
//����̃��b�Z�[�W�̐擪�ԍ�
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
	int startdata = -1;//WSAStartup�̖߂�l
	char ipadress[64];//IP�A�h���X
	u_short port = 4751;//�|�[�g�ԍ�
	SOCKET socket;//���g�̃\�P�b�g
	SOCKADDR_IN addr_in;
	WSADATA wasadata;//wasadata

	int  addr_in_size;//addr�̃T�C�Y
	int  ret;//�G���[��M
	char recvmassage[1024];//Recv�Ŏ󂯎��������
};
class ServerManager
{
private:
	static Member m_Member[SERVERMAX];
	static std::list<ServerEnemy*> m_EnemyList;

	static std::list<std::string> m_MassagePool;	//�S�Ă̎�M�f�[�^
	
	static MYDATA m_Mydata;

	static SOCKADDR_IN m_Insockaddr;
	//�S�̑��M
	static void AllSend(char* lpszMessage);

	//�P�̑��M
	static void SingleSend(int n,char* lpszMessage);
	//�ڑ�
	static int register_user(SOCKADDR_IN sa);
	//�ؒf
	static void exit_user(int n );

	//**************************************
	// �e�X�g�p
	//**************************************
	static UI_Text rettext;


public:
	ServerManager() {};
	 ~ServerManager() {};

	//�X�V����
	//�v���C���[�S���̃p�����[�^�[��ړ��Ȃǂ̍X�V
	static void Init();
	static void UnInit();
	static void Update();

	//��M�@�\
	//����ڑ�
	//�`���b�g
	//�T�[�o�[���甲����
	//�R�}���h
	//�̐U�蕪��������
	static void RecvMassage();

	//�v���C���[�̏��̃Q�b�^�[
	static Member* GetMember(int n);

	static void CreateEnemy(int EnemtID,float MaxHelth,XMFLOAT3 Position , XMFLOAT3 Rotation);



	//**************************************
	// �e�X�g�p
	//**************************************
	static std::list<ServerEnemy*>* GetEnemyList() { return &m_EnemyList; }
};


