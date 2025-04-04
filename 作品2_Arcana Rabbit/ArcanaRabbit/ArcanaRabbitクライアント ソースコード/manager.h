#pragma once
#include "scene.h"
class UDPManager;
class Manager
{
private:
	static Scene* m_scene;
	static Scene* m_nextscene;
	static UDPManager* m_UdpManager;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static Scene* GetScene() {return m_scene;}
	static void setscene(int scene);
	static UDPManager* GetUdpManager();
};
