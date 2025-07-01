#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
static float g_Min_Distance = 3.0f;//最小カメラ距離
static float g_Max_Distance = 30.0f;//最大カメラ距離
static float g_Default_Distance = 5.0f;//初期カメラ距離
//wasd移動

void Camera::Init() {
	m_Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_camera_up = g_Default_Distance;
}
void Camera::Uninit() {

}
void Camera::Update() {
	//float movespeed = 0.1f;
	////*m_Target = *Manager::GetScene()->GetGameObject<Player>()->GetPosition();

	//if (Input::GetKeyPress(VK_LEFT))
	//{
	//	m_Rotation.y -= 0.03f;
	//
	//}
	//if (Input::GetKeyPress(VK_RIGHT))
	//{
	//	m_Rotation.y += 0.03f;

	//}
	//if (Input::GetKeyPress(VK_DOWN))
	//{
	//	m_Rotation.x -= 0.03f;
	//	if (m_Rotation.x < (-XM_PIDIV2 + 0.01f))
	//	{
	//		m_Rotation.x = (-XM_PIDIV2 + 0.01f);
	//	}
	//}
	//if (Input::GetKeyPress(VK_UP))
	//{
	//	m_Rotation.x += 0.03f;
	//	if (m_Rotation.x > (XM_PIDIV2 - 0.01f))
	//	{
	//		m_Rotation.x = (XM_PIDIV2 - 0.01f);
	//	}
	//}
	//XMFLOAT2 movevel = { 0.0f,0.0f };
	//movevel.x = 0.0f;
	//movevel.y = 0.0f;
	//if (Input::GetKeyPress(0x57))//w
	//{
	//	movevel.y += 1.0f;
	//}
	//if (Input::GetKeyPress(0x53))//s
	//{
	//	movevel.y -= 1.0f;
	//}
	//if (Input::GetKeyPress(0x41))//a
	//{
	//	movevel.x -= 1.0f;
	//}
	//if (Input::GetKeyPress(0x44))//d
	//{
	//	movevel.x += 1.0f;
	//}
	//float nom = sqrtf(movevel.x * movevel.x + movevel.y * movevel.y);
	//if (nom != 0)
	//{
	//	nom = 1 / nom;
	//	movevel.x *= nom;
	//	movevel.y *= nom;
	//}


	//if (Input::GetKeyPress(0x57))//w
	//{
	//	m_Position.x += sinf(m_Rotation.y) * movespeed * movevel.y;
	//	m_Position.z += cosf(m_Rotation.y) * movespeed * movevel.y;
	//}
	//if (Input::GetKeyPress(0x53))//s
	//{
	//	m_Position.x += sinf(m_Rotation.y) * movespeed * movevel.y;
	//	m_Position.z += cosf(m_Rotation.y) * movespeed * movevel.y;
	//}
	//if (Input::GetKeyPress(0x41))//a
	//{
	//	m_Position.x += sinf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x;
	//	m_Position.z += cosf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x;
	//}
	//if (Input::GetKeyPress(0x44))//d
	//{
	//	m_Position.x += sinf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x;
	//	m_Position.z += cosf(m_Rotation.y + XM_PIDIV2) * movespeed * movevel.x;
	//}
}
void Camera::Draw() {
	XMFLOAT3 taget = { m_Position .x,m_Position.y,m_Position .z};
	
	XMFLOAT3 Rock = m_Target;
	if (m_TagetEnable)
	{
		Rock.x = taget.x + sinf(m_Rotation.y) * cosf(m_Rotation.x) * 1.0f;
		Rock.z = taget.z + cosf(m_Rotation.y) * cosf(m_Rotation.x) * 1.0f;
		Rock.y = taget.y + sinf(m_Rotation.x) * 1.0f;
	}

	XMFLOAT3 up{ 0.0f,1.0f,0.0f };
	XMMATRIX viewMatix = XMMatrixLookAtLH(XMLoadFloat3(&taget), XMLoadFloat3(&Rock), XMLoadFloat3(&up));

	Renderer::SetViewMatrix(viewMatix);

	XMStoreFloat4x4(&m_ViewMatrix, viewMatix);

	//プロジェクションマトリックス設定
	XMMATRIX projectionmatrix;
	projectionmatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 40000.0f);

	Renderer::SetProjectionMatrix(projectionmatrix);
}

void Camera::addCameraUp(float up)
{
	m_camera_up += up;
	if (m_camera_up + up < g_Min_Distance)
		m_camera_up = g_Min_Distance;

	if (m_camera_up + up > g_Max_Distance)
		m_camera_up = g_Max_Distance;

}


