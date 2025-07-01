#include "renderer.h"
#include "TextForm.h"
#include "input.h"
#include "Texture.h"
#include "material.h"
#include "Buttun.h"



void TextForm::Init()
{
	m_Scale = { 100.0f,100.0f,0.0f };
	m_Text = new std::string();
	*m_Text = "11";

	m_UI_Text.Link( Draw2D_Manager::AddTEXT());
	m_UI_Text.SetColer({ 1.0f,1.0f,1.0f,1.0f });
	m_UI_Text.SetDepth(2.0f + 0.01f);

	m_UI_Tex.Link(Draw2D_Manager::AddUI());
	m_UI_Tex.SetColer({ 0.3f,0.3f,0.3f,0.5f });
	m_UI_Tex.SetTex(GetImage().m_fade);
	m_UI_Tex.SetDepth(2.0f);



}

void TextForm::Uninit()
{
	m_Text->clear();
	delete m_Text;

}
void TextForm::Update()
{
	MouseClip(false);
	if (m_IsOpenflug) {
		GetInputTextString(m_Text);
	
		if (m_Setting == NOMULTI || m_Setting == NUMBER)
		{
			std::string text;
			while (m_Text->size() > 0)
			{
				if (m_Text->at(0) < 0)
				{
					m_Text->erase(0, 2);
				}
				else
				{
					text += m_Text->at(0);
					m_Text->erase(0, 1);
				}
			}
			*m_Text = text;
		}
		if (m_Setting == NUMBER)
		{
			std::string text;
			while (m_Text->size() > 0)
			{
				if ((m_Text->at(0) < 0x30 || m_Text->at(0) > 0x39) && 0x2E != m_Text->at(0))
				{
					m_Text->erase(0, 1);
				}
				else
				{
					text += m_Text->at(0);
					m_Text->erase(0, 1);
				}
			}
			*m_Text = text;
		}
		

		//フォーム以外を押したら入力できないように
		if (Input::IsMouseLeftTriggered() && !OnMouseButtun())
		{
			m_IsOpenflug = false;
			CloseInputTextString();
		}
	}

	m_UI_Text.SetText(*m_Text);
	if (m_Active == true)
	{
		m_UI_Text.SetActive(true);
		m_UI_Tex.SetActive(true);
	}
	else
	{
		m_UI_Text.SetActive(false);
		m_UI_Tex.SetActive(false);
	}
}


XMFLOAT4 TextForm::GetFormRect()
{
	return {
		m_Position.x - m_Scale.x * 0.5f,
		m_Position.y - m_Scale.y * 0.5f,
		m_Position.x + m_Scale.x * 0.5f,
		m_Position.y + m_Scale.y * 0.5f };
}


void TextForm::SetScale(XMFLOAT3 Scale)
{
	m_Scale = Scale;
	m_UI_Tex.SetScale({ m_Scale.x,m_Scale.y });
	m_UI_Text.SetRect({
		m_Position.x - m_Scale.x * 0.5f,
		m_Position.y - m_Scale.y * 0.5f,
		m_Position.x + m_Scale.x * 0.5f,
		m_Position.y + m_Scale.y * 0.5f });
}

void TextForm::SetPosition(XMFLOAT3 position)
{
	m_Position = position;
m_UI_Tex.SetPosition({ m_Position.x,m_Position.y });
	m_UI_Text.SetRect({
	m_Position.x - m_Scale.x * 0.5f,
	m_Position.y - m_Scale.y * 0.5f,
	m_Position.x + m_Scale.x * 0.5f,
	m_Position.y + m_Scale.y * 0.5f });
}

bool TextForm::OnMouseButtun()
{
	XMFLOAT2 mpos = MousePos();
	XMFLOAT2 p = { m_Position.x - m_Scale.x * 0.5f ,m_Position.y - m_Scale.y * 0.5f };
	if (p.x < mpos.x && p.y < mpos.y && p.x + m_Scale.x > mpos.x && p.y + m_Scale.y > mpos.y)
	{
		return true;
	}
	return false;
}