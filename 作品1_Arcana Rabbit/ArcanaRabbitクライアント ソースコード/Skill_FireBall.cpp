#include "Skill_FireBall.h"
#include "manager.h"
#include "scene.h"
#include "fireball.h"
#include "player.h"


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

void Fireball::GetSkillTextData(std::string* name, std::string* description)
{
	*name = "スキル ファイアーボール";
	*description = "クールタイム 2秒\n当たった敵に対してダメージを与える";
}
