#include "Skill_FireBall.h"
#include "manager.h"
#include "scene.h"
#include "fireball.h"
#include "player.h"
void Fireball::Draw()
{
	NomalDraw("スキル ファイアーボール","クールタイム 2秒\n当たった敵に対してダメージを与える");
}

void Fireball::Use()
{
	FireBullet* bu =  Manager::GetScene()->AddObject<FireBullet>(1);
	Player* pl = Manager::GetScene()->GetGameObject<Player>();
	XMFLOAT3 playerpos = *pl->GetPosition();
	playerpos.y += 1.5f;
	bu->SetPosition(playerpos);
	bu->SetRotation(pl->GetRot());
}

int Fireball::CD()
{
	return 120;
}
