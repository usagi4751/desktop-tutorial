#pragma once
#include "gameObject.h"
class Camera : public GameObject
{
private:
	bool m_TagetEnable;//ターゲットで描画するか
	XMFLOAT3 m_Target ;
	XMFLOAT4X4 m_ViewMatrix;
	float m_camera_up;

	XMFLOAT2 mousepos;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void addCameraUp(float up);
	void settarget(XMFLOAT3 Target) { m_Target = Target; };
	XMMATRIX GetViewmatrix() { return XMLoadFloat4x4(&m_ViewMatrix); }
	void SetTagetEnable(bool Enable) { m_TagetEnable = Enable; }
};

