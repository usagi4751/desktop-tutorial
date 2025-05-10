#pragma once
#include "gameObject.h"
#include "draw2d_Manager.h"
//===================================
// �����̓��͋@�\
//===================================
class Buttun;
enum TextSetting
{
	NOMAL = 0,//�}���`�o�C�g�������͉�
	NOMULTI,//1�o�C�g�����̂݉�
	NUMBER,//�����̂݉�
};
class TextForm : public GameObject
{
private:
	UI_Text m_UI_Text;
	UI_Tex m_UI_Tex;

	TextSetting m_Setting;

	std::string* m_Text;

	XMFLOAT4 m_Coler = { 1.0f,1.0f,1.0f,1.0f };

	bool m_IsOpenflug = false;
	bool m_Active = true;

public:

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw() {};

	//�t�H�[���̑傫��
	virtual void SetScale(XMFLOAT3 Scale);
	//�t�H�[���̍��W
	virtual void SetPosition(XMFLOAT3 position);
	//�\�����邩
	void SetActive(bool active) { m_Active = active; }
	//�t�H�[���ɕ\������
	void SetText(std::string text) { *m_Text = text; }
	//�F{R,G,B,A}
	void SetColer(XMFLOAT4 coler) { m_Coler = coler; }
	//���͐ݒ�
	void SetTextSetting(TextSetting setting) { m_Setting = setting; };

	//�t�H�[����Rect
	XMFLOAT4 GetFormRect();
	//���͂��ꂽ������Get
	std::string* GetText() { return m_Text; };
	bool GetOpenFlug() { return m_IsOpenflug; }	//�e�L�X�g�{�b�N�X���Ђ炢�Ă��邩
	bool OnMouseButtun();//�t�H�[���ɃJ�[�\�����d�Ȃ��Ă��邩


	void OpenTextBox() { m_IsOpenflug = true; };	//�e�L�X�g�{�b�N�X���J������Ƃ���CloseTextBox()���Ă΂Ȃ��ƊJ���ꑱ����
	void CloseTextBox() { m_IsOpenflug = false; };	//�e�L�X�g�{�b�N�X�����


};
