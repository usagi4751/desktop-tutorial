#include "renderer.h"
#include "TextBox.h"
#include "input.h"
#include "Texture.h"
#include "material.h"
#include "Buttun.h"
void TextBox::Init()
{
	m_Scale = {100.0f,100.0f,0.0f};
	m_Text = new std::string();
	m_NameText = new std::string();
	*m_Text = "aaa";

	m_UI_Text.Link(Draw2D_Manager::AddTEXT());
	m_UI_Text.SetColer({1.0f,1.0f,1.0f,1.0f});
	m_UI_Text.SetDepth(2.0f + 0.01f);

	m_UI_Tex.Link(Draw2D_Manager::AddUI());
	m_UI_Tex.SetColer({ 0.3f,0.3f,0.3f,0.5f });
	m_UI_Tex.SetTex(GetImage().m_fade);
	m_UI_Tex.SetDepth(2.0f);

	SetScaleTextBox({ SCREEN_WIDTH - 120.0f, 100,0.0f });
	SetPositionTextBox({ SCREEN_WIDTH * 0.5f - 60.0f,SCREEN_HEIGHT - 50.0f,0 });

	m_Buttun = new Buttun;
	m_Buttun->SetPosition({SCREEN_WIDTH - 60,SCREEN_HEIGHT - 50});
	m_Buttun->SetScale({120,100});
	m_Buttun->SetDepth(2.0f + 0.02f);

	//初期化では表示しない
	MouseClip(false);
	m_Buttun->SetActive(false);
	m_UI_Text.SetActive(false);
	m_UI_Tex.SetActive(false);

}

void TextBox::Uninit()
{
	m_Text->clear();
	delete m_Text;
	m_NameText->clear();
	delete m_NameText;
	delete m_Buttun;
	
}
void TextBox::Update()
{

	if (m_IsOpenflug) {
		m_Buttun->SetActive(true);
		m_UI_Text.SetActive(true);
		m_UI_Tex.SetActive(true);
		GetInputTextString(m_Text);
		m_UI_Text.SetText(*m_Text);

		//マウスがボタンに重なった時色を明るくする
		if (m_Buttun->OnMouseButtun())
			m_Buttun->SetColer({ 1.0f,1.0f ,1.0f ,1.0f });
		else
			m_Buttun->SetColer({ 0.8f,0.8f ,0.8f ,1.0f });


		//送信ボタンを押す機能
		if (Input::IsMouseLeftTriggered() && m_Buttun->OnMouseButtun() )
		{
			m_IsOpenflug = false;
			*m_Text = "";
			MouseClip(false);
			m_Buttun->SetActive(false);
			m_UI_Text.SetActive(false);
			m_UI_Tex.SetActive(false);
			CloseInputTextString();

		}
	}



	
	//デバック用
	if (Input::GetKeyTrigger('T'))
	{
		m_IsOpenflug = true;
		MouseClip(false);
	}
}

void TextBox::SetScaleTextBox(XMFLOAT3 Scale)
{
	m_Scale = Scale;
	m_UI_Tex.SetScale({ m_Scale.x,m_Scale.y });
	m_UI_Text.SetRect({
		m_Position.x - m_Scale.x * 0.5f,
		m_Position.y - m_Scale.y * 0.5f,
		m_Position.x + m_Scale.x * 0.5f,
		m_Position.y + m_Scale.y * 0.5f });
}
void TextBox::SetPositionTextBox(XMFLOAT3 position)
{
	m_Position = position;
	m_UI_Tex.SetPosition({ m_Position.x,m_Position.y });
	m_UI_Text.SetRect({
	m_Position.x - m_Scale.x * 0.5f,
	m_Position.y - m_Scale.y * 0.5f,
	m_Position.x + m_Scale.x * 0.5f,
	m_Position.y + m_Scale.y * 0.5f });
}