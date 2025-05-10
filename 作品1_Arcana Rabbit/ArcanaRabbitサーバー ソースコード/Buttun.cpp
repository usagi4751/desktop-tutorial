#include "Buttun.h"
#include "draw2d_Manager.h"
#include "material.h"
Buttun::Buttun() {
	m_ButtunTexture.Link(Draw2D_Manager::AddUI());
	m_ButtunTexture.SetTex(GetImage().m_SOUSINButuun);
	m_ButtunTexture.SetDepth(1.0f);
}

void Buttun::SetDepth(float depth)
{
	m_ButtunTexture.SetDepth(depth);
}

void Buttun::SetColer(XMFLOAT4 coler)
{
	m_ButtunTexture.SetColer(coler);
}

void Buttun::SetPosition(XMFLOAT2 position)
{
	m_ButtunTexture.SetPosition(position);
	m_Pos = { position .x,position .y,};
}

void Buttun::SetScale(XMFLOAT2 scale)
{
	m_ButtunTexture.SetScale(scale);
	m_Scale = { scale.x,scale.y, };
}

void Buttun::SetUV(XMFLOAT2 uv, XMFLOAT2 UV)
{
	m_ButtunTexture.SetUV(uv, UV);
}

void Buttun::SetActive(bool active)
{
	m_ButtunTexture.SetActive(active);
}

bool Buttun::OnMouseButtun()
{
	XMFLOAT2 mpos = MousePos();
	XMFLOAT2 p = { m_Pos.x - m_Scale.x * 0.5f ,m_Pos.y - m_Scale.y * 0.5f };
	if (p.x < mpos.x && p.y < mpos.y && p.x + m_Scale.x > mpos.x && p.y + m_Scale.y > mpos.y)
	{
		return true;
	}
	return false;
}
