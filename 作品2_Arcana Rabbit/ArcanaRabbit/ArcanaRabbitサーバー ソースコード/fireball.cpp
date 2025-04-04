#include "main.h"
#include "fireball.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "enemy.h"

void FireBullet::Init() {

}
void FireBullet::Uninit() {

}

void FireBullet::Update()
{
	float bullet_speed = 0.4f;
	m_Position.x += sinf(m_Rotation.y) * cosf(m_Rotation.x) * bullet_speed;
	m_Position.z += cosf(m_Rotation.y) * cosf(m_Rotation.x) * bullet_speed;
	m_Position.y += sinf(m_Rotation.x) * bullet_speed;
	m_life--;


	std::list<Enemy*> enemylist;
	enemylist = Manager::GetScene()->GetEntitylist<Enemy>();
	for (Enemy* enemy : enemylist)
	{
		XMFLOAT3 vec;
		vec.x = enemy->GetPosition()->x - m_Position.x;
		vec.y = enemy->GetPosition()->y - m_Position.y;
		vec.z = enemy->GetPosition()->z - m_Position.z;
		float len = D3DXVec3LengthSq(&vec);

		if (len < 1)
		{
			enemy->AddDamage(2.0f);
			this->SetDestroy();
			break;
		}
	}
	if (m_life <= 0)
	{
		SetDestroy();
	}

}

void FireBullet::Draw()
{

}
