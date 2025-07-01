#pragma once
typedef struct {
	bool            use;//そのヒットボックスを使っているか
	D3DXVECTOR2     pos;//ヒットボックスのポジション、エンティティの中心が0:0となる
	D3DXVECTOR2     size;//ヒットボックスのサイズ
	int             type;//弱点部位などが作れる
}HITBOX;
void Inithitbox(void);
void Drawhitbox(void);
