#pragma once
#include "main.h"
class Member
{
private:
	BOOL m_IN; // �ڑ����Ă��邩
	SOCKADDR_IN m_From; 

	std::string m_Name;

	XMFLOAT3 m_Position;
	float m_Rotate;
	short m_ConnectId;//�Ō�ɐڑ����Ă���ԍ�
public:
	Member() {};
	~Member() {};

	void SetActive(bool in);
	void SetName(std::string name);
	void SetReg(SOCKADDR_IN so);
	void SetPosition(XMFLOAT3 pos) { m_Position = pos; };
	void SetRotate(float rot) { m_Rotate = rot; }
	void SetconnectID(short ID) { m_ConnectId = ID; };


	short GetConnectID() { return m_ConnectId; }
	float GetRotate() { return m_Rotate; }
	bool GetActive() {return m_IN;};
	std::string GetName() { return m_Name; };
	XMFLOAT3 GetPosition() { return m_Position; };
	SOCKADDR_IN* GetSockddr() { return &m_From; };
	

	//�X�V����
	void Update();

	//�f�[�^���M
	void SendData(SOCKET s, char* lpszMessage);

};

