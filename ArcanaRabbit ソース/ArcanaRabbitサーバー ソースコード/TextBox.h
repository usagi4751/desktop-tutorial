#pragma once
//チャット機能用のテキストボックス
#include "gameObject.h"
#include "draw2d_Manager.h"
class UDP;
class Buttun;
class TextBox : public GameObject
{
private:
	UI_Text m_UI_Text;
	UI_Tex m_UI_Tex;
	Buttun* m_Buttun;


	std::string* m_Text;
	std::string* m_NameText;

	XMFLOAT4 m_Coler = { 1.0f,1.0f,1.0f,1.0f };

	bool m_IsOpenflug = false;

	void SetScaleTextBox(XMFLOAT3 Scale);
	void SetPositionTextBox(XMFLOAT3 position);
public:
	virtual void SetScale(XMFLOAT3 Scale) {};
	virtual void SetPosition(XMFLOAT3 position) {};
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw() {};



	void SetText(std::string text) { *m_Text = text; }
	std::string* GetText() { return m_Text; };
	void SetColer(XMFLOAT4 coler) { m_Coler = coler; }
	bool GetOpenFlug() { return m_IsOpenflug; }

	//テキストボックスを開く
	//閉じるときはCloseTextBox()を呼ばないと開かれ続ける
	void OpenTextBox() { m_IsOpenflug = true; };

	//テキストボックスを閉じる
	void CloseTextBox() { m_IsOpenflug = false; };

	//void SetName(std::string name) { *m_NameText = name; };

};
