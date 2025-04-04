#pragma once

struct Image_Material
{
	int m_textbox;//テキストBox背景
	int m_yuka;//床
	int m_testimage;
	int m_particle_Ster;
	int m_particle_Flame;//炎パーティクル
	int m_reticle_1;//1人称視点のレティクル
	int m_UI_image1;//インベントリ
	int m_UI_image2;//インベントリ
	int m_UI_image3;//skillせつめい
	int m_UI_image4;//持ってるアイテムアイコン
	int m_UI_image5;//攻撃のｃｔ表示用
	int m_UI_image6;//Titol
	int m_fade;//フェード
	int m_System_Cursor;//カーソル
	int m_ItemTex_Stick;//アイテム：棒
	int m_ItemTex_wand;//アイテム：杖
	int m_ItemTex_SlagHelmet;//アイテム：
	int m_ItemTex_SlagChest;//アイテム：
	int m_ItemTex_Slagwaistband;//アイテム：
	int m_ItemTex_SlagBoots;//アイテム：
	int m_ItemTex_SlagSword;//アイテム：
	int m_titol;//タイトル：
	int m_SOUSINButuun;//送信ボタン：
};
void LoadMaterial(void);
Image_Material& GetImage(void);