#pragma once
#include "Component.h"
#include "gameObject.h"
#include "item.h"
class Dropitem :public GameObject
{
private:
	//int m_AnimationFrame;
	Component* m_Component{};
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	int m_droptime = 0;//—‚Æ‚µ‚½‚Æ‚«‚ÉÄ‚ÑE‚¤‚Ü‚Å‚ÌŠÔ
	Item m_DropItem;//‹ß‚Ã‚¢‚½‚ÉE‚¤ƒAƒCƒeƒ€
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void Setitem(Item dropitemdata) {m_DropItem = dropitemdata;};
	virtual void SetDroptime(int time) { m_droptime = time; };
};

