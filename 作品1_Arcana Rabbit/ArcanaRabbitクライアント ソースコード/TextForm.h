#pragma once
#include "gameObject.h"
#include "draw2d_Manager.h"
//===================================
// 文字の入力機能
//===================================
class Buttun;
enum TextSetting
{
	NOMAL = 0,//マルチバイト文字入力可
	NOMULTI,//1バイト文字のみ可
	NUMBER,//数字のみ可
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

	//フォームの大きさ
	virtual void SetScale(XMFLOAT3 Scale);
	//フォームの座標
	virtual void SetPosition(XMFLOAT3 position);
	//表示するか
	void SetActive(bool active) { m_Active = active; }
	//フォームに表示する
	void SetText(std::string text) { *m_Text = text; }
	//色{R,G,B,A}
	void SetColer(XMFLOAT4 coler) { m_Coler = coler; }
	//入力設定
	void SetTextSetting(TextSetting setting) { m_Setting = setting; };

	//フォームのRect
	XMFLOAT4 GetFormRect();
	//入力された文字のGet
	std::string* GetText() { return m_Text; };
	bool GetOpenFlug() { return m_IsOpenflug; }	//テキストボックスがひらいているか
	bool OnMouseButtun();//フォームにカーソルが重なっているか


	void OpenTextBox() { m_IsOpenflug = true; };	//テキストボックスを開く閉じるときはCloseTextBox()を呼ばないと開かれ続ける
	void CloseTextBox() { m_IsOpenflug = false; };	//テキストボックスを閉じる


};
