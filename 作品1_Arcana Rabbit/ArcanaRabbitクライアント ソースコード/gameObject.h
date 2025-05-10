#pragma once
#include "main.h"
#include "pch.h"
class GameObject
{
protected:
	bool	m_Destroy = false;

	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	XMFLOAT3* GetPosition() { return &m_Position; }
	void SetDestroy() {m_Destroy = true;}
	virtual void SetPosition(XMFLOAT3 position){m_Position = position;}
	void SetRotation(XMFLOAT3 rotation){m_Rotation = rotation;}
	virtual void SetScale(XMFLOAT3 Scale){m_Scale = Scale;}

	bool Destoroy() {
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	
	}
};

