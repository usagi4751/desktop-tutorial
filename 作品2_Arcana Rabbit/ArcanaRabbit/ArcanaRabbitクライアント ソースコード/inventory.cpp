#include "inventory.h"
#include "item.h"
#include "material.h"
#include "input.h"
#include "DictionaryItem.h"
#include "ItemDataBase.h"
#include "player.h"
#include "manager.h"
#include "dropitem.h"
Item Inventory::m_itemlist[]{};
Item Inventory::m_hand{};
bool Inventory::m_openflug{};
float Inventory::m_posY{};
float Inventory::m_size{};
int Inventory::m_haveitem{};
UI_Tex Inventory::m_Cell[36];
UI_Tex Inventory::m_Bg;
UI_Tex Inventory::m_Celect;
UI_Tex Inventory::m_SkillText;
UI_Tex Inventory::m_HotBerCell[8];
UI_Tex Inventory::m_CellOnMouse;
UI_Tex Inventory::m_Hand;

UI_Tex Inventory::m_CellItem[36];
UI_Tex Inventory::m_HotBerCellItem[8];
bool   Inventory::m_ShowUI;
ItemSkillDraw Inventory::m_ItemTextDraw;
//アイテムスロットと場所が正しいかチェック
bool ItemRightRlace(int num, SetSlot slot) {
	if (num == 32 && slot == Head)
	{
		return true;
	}
	if (num == 33 && slot == Chest)
	{
		return true;
	}
	if (num == 34 && slot == LEGGINGS)
	{
		return true;
	}
	if (num == 35 && slot == BOOTS)
	{
		return true;
	}
	return false;
}


int Inventory::Getitemno(XMFLOAT2 mousepos)
{
	float Depth = 0.5f;
	float wind = 768.0f * m_size;


	float ic = 80.0f * m_size;//セルのサイズ
	float sukima = 6.0f * m_size;//セル同士の隙間
	float iclen = ic + sukima;//描画時の間隔
	float kote = ic * 0.5f + sukima * 0.5f;//真ん中の隙間用
	float hoiver = 120.0f * m_size;//ホットバー固定移動

	//装備アイコン用
	float soubiic = ic * 1.3f;//アイコンサイズ
	float soubiver = -180.0f * m_size;//装備固定移動
	float soubisukima = 40.0f * m_size;//サイズ
	float soubilen = soubisukima + soubiic;//間隔
	float soubikote = soubiic * 0.5f + soubisukima * 0.5f;//真ん中の隙間用
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				if (960 + (float)i * iclen - (iclen * 3)- kote - ic * 0.5f < mousepos.x &&
					960 + (float)i * iclen - (iclen * 3) - kote + ic * 0.5f > mousepos.x &&
					540-  (float)j * iclen + (iclen * 2) - ic * 0.5f < mousepos.y &&
					540 - (float)j * iclen + (iclen * 2) + ic * 0.5f > mousepos.y)
				{
					return 8 + i + j * 8;
				}
		
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (960 - (float)i * iclen - kote - ic * 0.5f < mousepos.x &&
				960 - (float)i * iclen - kote + ic * 0.5f > mousepos.x &&
				540 + (float)2 * iclen + hoiver - ic * 0.5f < mousepos.y &&
				540 + (float)2 * iclen + hoiver + ic * 0.5f > mousepos.y
				)
			{
				return 3 - i;
			}
			if (960 + (float)i * iclen + kote - ic * 0.5f < mousepos.x &&
				960 + (float)i * iclen + kote + ic * 0.5f > mousepos.x &&
				540 + (float)2 * iclen + hoiver - ic * 0.5f < mousepos.y &&
				540 + (float)2 * iclen + hoiver + ic * 0.5f > mousepos.y
				)
			{
				return 4 + i;
			}

		}
		for (int i = 0; i < 2; i++)
		{
			if (960 - (float)i * soubilen - soubikote - soubiic * 0.5f < mousepos.x &&
				960 - (float)i * soubilen - soubikote + soubiic * 0.5f > mousepos.x &&
				540 + soubiver - soubiic * 0.5f < mousepos.y &&
				540 + soubiver + soubiic * 0.5f > mousepos.y)
			{
				return 33 - i;
			}
			if (960 + (float)i * soubilen + soubikote - soubiic * 0.5f < mousepos.x &&
				960 + (float)i * soubilen + soubikote + soubiic * 0.5f > mousepos.x &&
				540 + soubiver - soubiic * 0.5f < mousepos.y &&
				540 + soubiver + soubiic * 0.5f > mousepos.y)
			{
				return 34 + i;
			}

		}

	}
	return -1;
}
void Inventory::Init()
{
	for (int i = 0; i < 36; i++)
	{
		m_itemlist[i].m_ItemNo = -1;
	}
	m_itemlist[0].m_skillNo = 0;
	m_itemlist[0].m_ItemNo = 1;
	m_itemlist[0].m_ItemNum = 1;
	m_itemlist[0].m_damage = 2;
	m_itemlist[0].m_maxhelth = 0;
	m_itemlist[0].m_def = 0;
	m_itemlist[0].movespeed = 0;
	m_itemlist[0].m_attackspeed = 0;

	m_itemlist[2].m_ItemNo = 2;
	m_itemlist[2].m_ItemNum = 1;
	m_itemlist[2].m_maxhelth = 2;
	m_itemlist[2].m_def = 1;

	m_itemlist[3].m_ItemNo = 3;
	m_itemlist[3].m_ItemNum = 1;
	m_itemlist[3].m_maxhelth = 2;
	m_itemlist[3].m_def = 0;

	m_itemlist[4].m_ItemNo = 4;
	m_itemlist[4].m_ItemNum = 1;
	m_itemlist[4].m_maxhelth = 2;
	m_itemlist[4].m_def = 2;

	m_itemlist[5].m_ItemNo = 5;
	m_itemlist[5].m_ItemNum = 1;
	m_itemlist[5].m_maxhelth = 1;
	m_itemlist[5].m_def = 2;
	m_hand.m_ItemNo = -1;
	m_hand.m_skillNo = -1;
	m_hand.m_ItemNum = 0;

	m_size = 1.0f;
	float Depth = 0.5f;
	float wind = 768.0f * m_size;


	float ic = 80.0f * m_size;//セルのサイズ
	float sukima = 6.0f * m_size;//セル同士の隙間
	float iclen = ic + sukima;//描画時の間隔
	float kote = ic * 0.5f + sukima * 0.5f;//真ん中の隙間用
	float hoiver = 120.0f * m_size;//ホットバー固定移動

	//装備アイコン用
	float soubiic = ic * 1.3f;//アイコンサイズ
	float soubiver = -180.0f * m_size;//装備固定移動
	float soubisukima = 40.0f * m_size;//サイズ
	float soubilen = soubisukima + soubiic;//間隔
	float soubikote = soubiic * 0.5f + soubisukima * 0.5f;//真ん中の隙間用

	m_Bg.Link(Draw2D_Manager::AddUI());
	m_Celect.Link(Draw2D_Manager::AddUI());
	m_SkillText.Link(Draw2D_Manager::AddUI());
	m_CellOnMouse.Link(Draw2D_Manager::AddUI());

	m_ItemTextDraw.m_ItemBg.Link(Draw2D_Manager::AddUI());
	m_ItemTextDraw.m_SkillBg.Link(Draw2D_Manager::AddUI());

	m_ItemTextDraw.m_ItemTextName.Link(Draw2D_Manager::AddTEXT());
	m_ItemTextDraw.m_ItemTextdescription.Link(Draw2D_Manager::AddTEXT());
	m_ItemTextDraw.m_SkillTextName.Link(Draw2D_Manager::AddTEXT());
	m_ItemTextDraw.m_SkillTextdescription.Link(Draw2D_Manager::AddTEXT());


	m_Hand.Link(Draw2D_Manager::AddUI());
	{

		m_ItemTextDraw.m_ItemBg.SetTex(GetImage().m_UI_image3);
		m_ItemTextDraw.m_ItemBg.SetColer({ 1.0f,1.0f ,1.0f ,1.0f });
		m_ItemTextDraw.m_ItemBg.SetPosition({ 270,365 });
		m_ItemTextDraw.m_ItemBg.SetScale({ 450,550 });
		m_ItemTextDraw.m_ItemBg.SetDepth(1.0f);

		m_ItemTextDraw.m_ItemTextdescription.SetColer({ 1.0f,1.0f ,1.0f ,1.0f });
		m_ItemTextDraw.m_ItemTextdescription.SetDepth(1.1f);
		m_ItemTextDraw.m_ItemTextdescription.SetRect({ 55,200,490,640 });
		m_ItemTextDraw.m_ItemTextdescription.SetScale(15.0f);

		m_ItemTextDraw.m_ItemTextName.SetColer({ 1.0f,1.0f ,1.0f ,1.0f });
		m_ItemTextDraw.m_ItemTextName.SetDepth(1.1f);
		m_ItemTextDraw.m_ItemTextName.SetRect({ 55,140,490,190 });
		m_ItemTextDraw.m_ItemTextName.SetScale(25.0f);


		m_ItemTextDraw.m_SkillTextName.SetColer({ 1.0f,0.3f ,1.0f ,1.0f });
		m_ItemTextDraw.m_SkillTextName.SetDepth(1.1f);
		m_ItemTextDraw.m_SkillTextName.SetRect({ 55,660,490,710 });
		m_ItemTextDraw.m_SkillTextName.SetScale(25.0f);

		m_ItemTextDraw.m_SkillTextdescription.SetColer({ 1.0f,1.0f ,1.0f ,1.0f });
		m_ItemTextDraw.m_SkillTextdescription.SetDepth(1.1f);
		m_ItemTextDraw.m_SkillTextdescription.SetRect({ 55,715,490,1000 });
		m_ItemTextDraw.m_SkillTextdescription.SetScale(15.0f);


		m_ItemTextDraw.m_SkillBg.SetTex(GetImage().m_UI_image3);
		m_ItemTextDraw.m_SkillBg.SetColer({ 1.0f,1.0f ,1.0f ,1.0f });
		m_ItemTextDraw.m_SkillBg.SetPosition({ 270,820 });
		m_ItemTextDraw.m_SkillBg.SetScale({ 450,360 });
		m_ItemTextDraw.m_SkillBg.SetDepth(1.0f);

	}
	{
		for (int i = 0; i < 36; i++)
		{
			m_Cell[i].Link(Draw2D_Manager::AddUI());
			m_Cell[i].SetColer({ 1.0f,1.0f,1.0f,1.0f });
			m_Cell[i].SetDepth(1.002f);
			m_Cell[i].SetTex(GetImage().m_UI_image2);

			m_CellItem[i].Link(Draw2D_Manager::AddUI());
			m_CellItem[i].SetColer({ 1.0f,1.0f,1.0f,1.0f });
			m_CellItem[i].SetDepth(1.1f);
			m_CellItem[i].SetTex(GetImage().m_ItemTex_Stick);

		}
		for (int i = 0; i < 8; i++)
		{
			m_HotBerCell[i].Link(Draw2D_Manager::AddUI());
			m_HotBerCell[i].SetColer({ 1.0f,1.0f,1.0f,1.0f });
			m_HotBerCell[i].SetDepth(0.5f);
			m_HotBerCell[i].SetTex(GetImage().m_UI_image2);


			m_HotBerCellItem[i].Link(Draw2D_Manager::AddUI());
			m_HotBerCellItem[i].SetColer({ 1.0f,1.0f,1.0f,1.0f });
			m_HotBerCellItem[i].SetDepth(0.6f);
			m_HotBerCellItem[i].SetTex(GetImage().m_ItemTex_Stick);
		}


		m_CellOnMouse.SetColer({ 0.0f, 1.0f, 0.0f, 1.0f });
		m_CellOnMouse.SetTex(GetImage().m_UI_image2);
		m_CellOnMouse.SetDepth(1.003f);

		m_Bg.SetColer({ 1.0f,1.0f,1.0f,1.0f });
		m_Bg.SetTex(GetImage().m_UI_image1);
		m_Bg.SetDepth(1.001f);
		m_Bg.SetPosition({ 960, 540 });
		m_Bg.SetScale({ wind ,wind });

		m_Hand.SetColer({ 1.0f,1.0f,1.0f,1.0f });
		m_Hand.SetDepth(6.001f);
		m_Hand.SetScale({ ic ,ic });


		m_Celect.SetColer({ 1.0f,1.0f,1.0f,1.0f });
		m_Celect.SetTex(GetImage().m_UI_image4);
		m_Celect.SetDepth(4.0f);


		m_SkillText.SetColer({ 1.0f,1.0f,1.0f,0.5f });
		m_SkillText.SetTex(GetImage().m_UI_image3);
		m_SkillText.SetDepth(1.000f);
		m_SkillText.SetPosition({ 960, 540 });
		m_SkillText.SetScale({ 1920,1080 });

		//ホットバー
		//使いにくい直す
		for (int i = 0; i < 4; i++)
		{
			m_HotBerCell[i].SetScale({ ic,ic });
			m_HotBerCell[i].SetPosition({ 960 - (float)i * ic - ic * 0.5f,1080 - ic * 0.5f });
			m_HotBerCell[i + 4].SetScale({ ic,ic });
			m_HotBerCell[i + 4].SetPosition({ 960 + (float)i * ic + ic * 0.5f,1080 - ic * 0.5f });


			m_HotBerCellItem[i + 4].SetPosition({ 960 + (float)i * ic + ic * 0.5f,1080 - ic * 0.5f });
			m_HotBerCellItem[i + 4].SetScale({ ic,ic });
		}
		for (int i = 0; i < 8; i++)
		{
			m_HotBerCellItem[i].SetPosition({ 960 + (float)i * ic - (ic * 3) - ic * 0.5f,1080 - ic * 0.5f });
			m_HotBerCellItem[i].SetScale({ ic,ic });
		}
		//インベントリ
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				m_Cell[i + j * 8 + 8].SetScale({ ic,ic });
				m_Cell[i + j * 8 + 8].SetPosition({ 960 - (float)i * iclen - kote,540 + (float)j * iclen });
				m_Cell[i + j * 8 + 4 + 8].SetScale({ ic,ic });
				m_Cell[i + j * 8 + 4 + 8].SetPosition({ 960 + (float)i * iclen + kote,540 + (float)j * iclen });


				m_CellItem[i + j * 8 + 8].SetPosition({ 960 - (float)i * iclen - kote,540 + (float)j * iclen });
				m_CellItem[i + j * 8 + 8].SetScale({ ic,ic });
				m_CellItem[i + j * 8 + 4 + 8].SetPosition({ 960 + (float)i * iclen + kote,540 + (float)j * iclen });
				m_CellItem[i + j * 8 + 4 + 8].SetScale({ ic,ic });
			}
		}
		//ホットバー
		for (int i = 0; i < 4; i++)
		{
			m_Cell[i].SetScale({ ic,ic });
			m_Cell[i].SetPosition({ 960 - (float)i * iclen - kote,540 + (float)2 * iclen + hoiver });
			m_Cell[i + 4].SetScale({ ic,ic });
			m_Cell[i + 4].SetPosition({ 960 + (float)i * iclen + kote,540 + (float)2 * iclen + hoiver });
		}
		for (int i = 0; i < 2; i++)
		{
			m_Cell[32 + i].SetScale({ soubiic,soubiic });
			m_Cell[32 + i].SetPosition({ 960 - (float)i * soubilen - soubikote,540 + soubiver });
			m_Cell[32 + i + 2].SetScale({ soubiic,soubiic });
			m_Cell[32 + i + 2].SetPosition({ 960 + (float)i * soubilen + soubikote,540 + soubiver });
		}


		//ホットバー  アイテム
		for (int i = 0; i < 8; i++)
		{
			m_CellItem[i].SetPosition({ 960 + (float)i * iclen - (iclen * 3) - kote ,540 + (float)2 * iclen + hoiver });
			m_CellItem[i].SetScale({ ic,ic });
		}
		//インベントリ  アイテム
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				m_CellItem[i + j * 8 + 8].SetPosition({ 960 + (float)i * iclen - (iclen * 3) - kote,540 - (float)j * iclen + (iclen * 2) });
				m_CellItem[i + j * 8 + 8].SetScale({ ic,ic });
			}
		}//装備  アイテム
		for (int i = 0; i < 4; i++)
		{
			m_CellItem[32 + i].SetPosition({ 960 + (float)i * soubilen - soubilen - soubikote,540 + soubiver });
			m_CellItem[32 + i].SetScale({ soubiic,soubiic });
		}
	}
}
void Inventory::Update()
{

	float ic = 80.0f * m_size;//セルのサイズ
	float sukima = 6.0f * m_size;//セル同士の隙間
	float iclen = ic + sukima;//描画時の間隔
	float kote = ic * 0.5f + sukima * 0.5f;//真ん中の隙間用
	float hoiver = 120.0f * m_size;//ホットバー固定移動

	//装備アイコン用
	float soubiic = ic * 1.3f;//アイコンサイズ
	float soubiver = -180.0f * m_size;//装備固定移動
	float soubisukima = 40.0f * m_size;//サイズ
	float soubilen = soubisukima + soubiic;//間隔

	if (m_ShowUI == true)
	{
		m_Celect.SetActive(true);
		m_CellItem->SetActive(true);
		m_Cell->SetActive(true);
		for (int i = 0; i < 8; i++)
		{
			m_HotBerCellItem[i].SetActive(true);;
			m_HotBerCell[i].SetActive(true);;
		}
	}
	else
	{
		m_Celect.SetActive(false);
		for (int i = 0; i < 8; i++)
		{
			m_HotBerCellItem[i].SetActive(false);;
			m_HotBerCell[i].SetActive(false);;
		}
		m_CellItem->SetActive(false);
		m_Cell->SetActive(false);
	}

	float soubikote = soubiic * 0.5f + soubisukima * 0.5f;//真ん中の隙間用
	m_Celect.SetScale({ ic,ic });
	m_Celect.SetPosition({ 960 - (float)(3 - m_haveitem) * ic - ic * 0.5f,1080 - ic * 0.5f });

	
	if (m_openflug == true)
	{
		m_Bg.SetActive(true);
		m_SkillText.SetActive(true);
		for (int i = 0; i < 36; i++)
		{
			m_Cell[i].SetActive(true);
		}
	}
	if (m_openflug == false)
	{
		m_Bg.SetActive(false);
		m_SkillText.SetActive(false);
		for (int i = 0; i < 36; i++)
		{
			m_Cell[i].SetActive(false);
		}
	}

	m_CellOnMouse.SetActive(false);
	
	//アイコンにカーソルがあってると強調表示
	if(m_openflug == true && m_ShowUI == true){
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (960 - (float)i * iclen - kote - ic * 0.5f < Input::GetMousePos().x && 960 - (float)i * iclen - kote + ic * 0.5f > Input::GetMousePos().x &&
					540 + (float)j * iclen - ic * 0.5f < Input::GetMousePos().y && 540 + (float)j * iclen + ic * 0.5f > Input::GetMousePos().y)
				{
					m_CellOnMouse.SetScale({ ic,ic });
					m_CellOnMouse.SetPosition({ 960 - (float)i * iclen - kote,540 + (float)j * iclen });
					m_CellOnMouse.SetActive(true);
				}
				if (960 + (float)i * iclen + kote - ic * 0.5f < Input::GetMousePos().x && 960 + (float)i * iclen + kote + ic * 0.5f > Input::GetMousePos().x &&
					540 + (float)j * iclen - ic * 0.5f < Input::GetMousePos().y && 540 + (float)j * iclen + ic * 0.5f > Input::GetMousePos().y)
				{
					m_CellOnMouse.SetScale({ ic,ic });
					m_CellOnMouse.SetPosition({ 960 + (float)i * iclen + kote,540 + (float)j * iclen });
					m_CellOnMouse.SetActive(true);
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (960 - (float)i * iclen - kote - ic * 0.5f < Input::GetMousePos().x &&
				960 - (float)i * iclen - kote + ic * 0.5f > Input::GetMousePos().x &&
				540 + (float)2 * iclen + hoiver - ic * 0.5f < Input::GetMousePos().y &&
				540 + (float)2 * iclen + hoiver + ic * 0.5f > Input::GetMousePos().y
				)
			{
				m_CellOnMouse.SetScale({ ic,ic });
				m_CellOnMouse.SetPosition({ 960 - (float)i * iclen - kote,540 + (float)2 * iclen + hoiver });
				m_CellOnMouse.SetActive(true);
			}
			if (960 + (float)i * iclen + kote - ic * 0.5f < Input::GetMousePos().x &&
				960 + (float)i * iclen + kote + ic * 0.5f > Input::GetMousePos().x &&
				540 + (float)2 * iclen + hoiver - ic * 0.5f < Input::GetMousePos().y &&
				540 + (float)2 * iclen + hoiver + ic * 0.5f > Input::GetMousePos().y
				)
			{
				m_CellOnMouse.SetScale({ ic,ic });
				m_CellOnMouse.SetPosition({ 960 + (float)i * iclen + kote,540 + (float)2 * iclen + hoiver });
				m_CellOnMouse.SetActive(true);
			}

		}
		for (int i = 0; i < 2; i++)
		{
			if (960 - (float)i * soubilen - soubikote - soubiic * 0.5f < Input::GetMousePos().x &&
				960 - (float)i * soubilen - soubikote + soubiic * 0.5f > Input::GetMousePos().x &&
				540 + soubiver - soubiic * 0.5f < Input::GetMousePos().y &&
				540 + soubiver + soubiic * 0.5f > Input::GetMousePos().y)
			{
				m_CellOnMouse.SetScale({ soubiic,soubiic });
				m_CellOnMouse.SetPosition({ 960 - (float)i * soubilen - soubikote,540 + soubiver });
				m_CellOnMouse.SetActive(true);
			}
			if (960 + (float)i * soubilen + soubikote - soubiic * 0.5f < Input::GetMousePos().x &&
				960 + (float)i * soubilen + soubikote + soubiic * 0.5f > Input::GetMousePos().x &&
				540 + soubiver - soubiic * 0.5f < Input::GetMousePos().y &&
				540 + soubiver + soubiic * 0.5f > Input::GetMousePos().y)
			{
				m_CellOnMouse.SetScale({ soubiic,soubiic });
				m_CellOnMouse.SetPosition({ 960 + (float)i * soubilen + soubikote,540 + soubiver });
				m_CellOnMouse.SetActive(true);
			}

		}

	}

	for (int i = 0; i < 36; i++)
	{
		if (m_itemlist[i].m_ItemNo < 0 || m_openflug == false || m_ShowUI == false)
		{
			m_CellItem[i].SetActive(false);
		}
		else
		{
			m_CellItem[i].SetActive(true);
			m_CellItem[i].SetTex(DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetIcon());
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (m_itemlist[i].m_ItemNo < 0 || m_ShowUI == false)
		{
			m_HotBerCellItem[i].SetActive(false);
		}
		else
		{
			m_HotBerCellItem[i].SetActive(true);
			m_HotBerCellItem[i].SetTex(DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetIcon());
		}
	}

	if (m_hand.m_ItemNo < 0)
	{
		m_Hand.SetActive(false);
	}
	else
	{
		m_Hand.SetPosition({ (float)Input::GetMousePos().x, (float)Input::GetMousePos().y });
		m_Hand.SetTex(DictionaryItem::GetItem(m_hand.m_ItemNo)->GetIcon());
		m_Hand.SetActive(true);
	}




	float wind = 768.0f * m_size;
	m_size = 1.0f;
	for (int i = 0; i < 36; i++)
	{
		if (m_itemlist[i].m_skillCD > 0)
		{
			m_itemlist[i].m_skillCD--;
		}
	}
	//アイテムの移動処理
	if (m_openflug == true)
	{
		Input::SetMouseDraw(true);
		int itemno = Getitemno(Input::GetMousePos());
		if (itemno >= 0 && itemno < 32)
		{
			if (Input::IsMouseLeftTriggered())
			{
				//インベントリにアイテムが入ってないかつカーソルがアイテムを持ってた時
				if (m_itemlist[itemno].m_ItemNo < 0 && m_hand.m_ItemNo >= 0)
				{
					m_itemlist[itemno] = m_hand;
					m_hand.m_ItemNo = -1;
				}
				//インベントリにアイテムがありかつカーソルがアイテムを持ってた場合
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo >= 0)
				{
					//同じアイテム種だったら最大スタック数まで加算する
					if (m_itemlist[itemno].m_ItemNo == m_hand.m_ItemNo)
					{
						if (m_itemlist[itemno].m_ItemNum < DictionaryItem::GetItem(m_itemlist[itemno].m_ItemNo)->GetMaxStack())
						{
							m_itemlist[itemno].m_ItemNum += m_hand.m_ItemNum;
							m_hand.m_ItemNum = 0;
							//最大数を超えたらhandに戻す
							if (m_itemlist[itemno].m_ItemNum > DictionaryItem::GetItem(m_itemlist[itemno].m_ItemNo)->GetMaxStack())
							{
								m_hand.m_ItemNum = m_itemlist[itemno].m_ItemNum - DictionaryItem::GetItem(m_itemlist[itemno].m_ItemNo)->GetMaxStack();
								m_itemlist[itemno].m_ItemNum -= m_hand.m_ItemNum;
							}
							if (m_hand.m_ItemNum <= 0)
							{
								m_hand.m_ItemNo = -1;
							}
						}
					}
					else
					{
						Item swap = m_itemlist[itemno];
						m_itemlist[itemno] = m_hand;
						m_hand = swap;
					}

				}
				//インベントリにアイテムがありカーソルがアイテムを持ってなかった場合
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo < 0)
				{
					m_hand = m_itemlist[itemno];
					m_itemlist[itemno].m_ItemNo = -1;
				}


			}
		/*	if (DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo) != nullptr)
			{
				DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo)->Draw(m_itemlist[Getitemno(Input::GetMousePos())]);
			}*/
		}

		//装備の交換など
		if (itemno >= 32 && itemno < 36)
		{
			if (Input::IsMouseLeftTriggered())
			{
				//インベントリにアイテムが入ってないかつカーソルがアイテムを持ってた時
				if (m_itemlist[itemno].m_ItemNo < 0 && m_hand.m_ItemNo >= 0 && ItemRightRlace(itemno, DictionaryItem::GetItem(m_hand.m_ItemNo)->GetSlot()))
				{
					m_itemlist[itemno] = m_hand;
					m_hand.m_ItemNo = -1;
					m_hand.m_maxhelth = 0;
					m_hand.m_damage = 0;
					m_hand.movespeed = 0;
					m_hand.m_attackspeed = 0;
					m_hand.m_def = 0;
				}
				//インベントリにアイテムがありかつカーソルがアイテムを持ってた場合
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo >= 0 && ItemRightRlace(itemno, DictionaryItem::GetItem(m_hand.m_ItemNo)->GetSlot()))
				{
					//装備は最大スタック数が固定で１なのでswapだけでいい

					Item swap = m_itemlist[itemno];
					m_itemlist[itemno] = m_hand;
					m_hand = swap;

				}
				//インベントリにアイテムがありカーソルがアイテムを持ってなかった場合
				else if (m_itemlist[itemno].m_ItemNo >= 0 && m_hand.m_ItemNo < 0)
				{
					m_hand = m_itemlist[itemno];
					m_itemlist[itemno].m_ItemNo = -1;
					m_itemlist[itemno].m_maxhelth = 0;
					m_itemlist[itemno].m_damage = 0;
					m_itemlist[itemno].movespeed = 0;
					m_itemlist[itemno].m_attackspeed = 0;
					m_itemlist[itemno].m_def = 0;
				}


			}
	

		}

		if (Input::IsMouseLeftTriggered() && (Input::GetMousePos().x < 960 - wind * 0.5f || Input::GetMousePos().x > 960 + wind * 0.5f ||
			Input::GetMousePos().y < 540 - wind * 0.5f || Input::GetMousePos().y > 540 + wind * 0.5f) && m_hand.m_ItemNo >= 0)
		{
			Dropitem* item = Manager::GetScene()->AddObject<Dropitem>(1);
			Player* player = Manager::GetScene()->GetGameObject<Player>();
			item->SetPosition(*player->GetPosition());
			item->Setitem(m_hand);
			m_hand.m_ItemNo = -1;
			m_hand.m_ItemNum = 0;
			m_hand.m_skillNo = -1;
			item->SetDroptime(150);
		}
	}
	else { Input::SetMouseDraw(false); }



	std::string itemname;
	std::string itemsetumei;
	std::string skillname;
	std::string skillsetumei;
	if (Getitemno(Input::GetMousePos()) > -1)
	{
		if (DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo) != nullptr)
		{
			DictionaryItem::GetItem(m_itemlist[Getitemno(Input::GetMousePos())].m_ItemNo)->GetItemName(
				m_itemlist[Getitemno(Input::GetMousePos())],
				&itemname, &itemsetumei, &skillname, &skillsetumei);

		}
	}
	if (itemname.size() > 0 && m_openflug == true && m_ShowUI == true)
	{
		m_ItemTextDraw.m_ItemTextName.SetActive(true);
		m_ItemTextDraw.m_ItemTextdescription.SetActive(true);
		m_ItemTextDraw.m_ItemBg.SetActive(true);
		m_ItemTextDraw.m_SkillTextName.SetActive(true);
		m_ItemTextDraw.m_SkillTextdescription.SetActive(true);
		m_ItemTextDraw.m_SkillBg.SetActive(true);
	}
	else
	{
		m_ItemTextDraw.m_ItemTextName.SetActive(false);
		m_ItemTextDraw.m_ItemTextdescription.SetActive(false);
		m_ItemTextDraw.m_ItemBg.SetActive(false);
		m_ItemTextDraw.m_SkillTextName.SetActive(false);
		m_ItemTextDraw.m_SkillTextdescription.SetActive(false);
		m_ItemTextDraw.m_SkillBg.SetActive(false);
	}
	m_ItemTextDraw.m_ItemTextName.SetText(itemname);
	m_ItemTextDraw.m_ItemTextdescription.SetText(itemsetumei);
	m_ItemTextDraw.m_SkillTextName.SetText(skillname);
	m_ItemTextDraw.m_SkillTextdescription.SetText(skillsetumei);





}

void Inventory::DrawRect()
{
	float Depth = 0.5f;
	float wind = 768.0f * m_size;


	float ic = 80.0f * m_size;//セルのサイズ
	float sukima = 6.0f * m_size;//セル同士の隙間
	float iclen = ic + sukima;//描画時の間隔
	float kote = ic * 0.5f + sukima * 0.5f;//真ん中の隙間用
	float hoiver = 120.0f * m_size;//ホットバー固定移動

	//装備アイコン用
	float soubiic = ic * 1.3f;//アイコンサイズ
	float soubiver = -180.0f * m_size;//装備固定移動
	float soubisukima = 40.0f * m_size;//サイズ
	float soubilen = soubisukima + soubiic;//間隔
	float soubikote = soubiic * 0.5f + soubisukima * 0.5f;//真ん中の隙間用





		//==============================
		// アイテム総合のステータスの表示
		//==============================
		{
			//Draw2d::SetUI(GetImage().m_UI_image3, { 1.0f,1.0f,1.0f,1.0f }, { 1600,250 }, { 500,400 }, { 0.0f,0.0f }, { 1.0f,1.0f }, {}, 0.0f, Depth);
			std::string drawstutus;
			Status handstatus = {};
			int itemno = m_itemlist[m_haveitem].m_ItemNo;
			if (DictionaryItem::GetItem(itemno) != nullptr)
			{
				handstatus = DictionaryItem::GetItem(itemno)->GetStatus(m_itemlist[m_haveitem]);
			}
			drawstutus += "最大体力 " + std::to_string(DEFAULTHELTH + m_itemlist[32].m_maxhelth + m_itemlist[33].m_maxhelth + m_itemlist[34].m_maxhelth + m_itemlist[35].m_maxhelth + handstatus.MaxHelth) + "\n";
			drawstutus += "ダメージ " + std::to_string(DEFAULTDAMAGE + m_itemlist[32].m_damage + m_itemlist[33].m_damage + m_itemlist[34].m_damage + m_itemlist[35].m_damage + handstatus.Damage) + "\n";
			drawstutus += "移動速度 " + std::to_string(DEFAULTMOVESPEED + m_itemlist[32].movespeed + m_itemlist[33].movespeed + m_itemlist[34].movespeed + m_itemlist[35].movespeed + handstatus.MoveSpeed) + "\n";
			drawstutus += "攻撃速度 " + std::to_string(DEFAULTATTACKSPEED + m_itemlist[32].m_attackspeed + m_itemlist[33].m_attackspeed + m_itemlist[34].m_attackspeed + m_itemlist[35].m_attackspeed + handstatus.AttackSpeed) + "\n";
			drawstutus += "防御力 " + std::to_string(DEFAULTDEF + m_itemlist[32].m_def + m_itemlist[33].m_def + m_itemlist[34].m_def + m_itemlist[35].m_def + handstatus.Def);
			//Draw2d::SetText(drawstutus, { 1375,100,1850,650 }, 24, { 0.5f,1.0f ,0.5f ,1.0f }, Depth + 0.01f);
		}
	
	
	
	
}

Status Inventory::GetStayus()
{
	Status retstatus;
	Status handstatus = {};
	int itemno =  m_itemlist[m_haveitem].m_ItemNo;
	if (DictionaryItem::GetItem(itemno) != nullptr)
	{
		handstatus = DictionaryItem::GetItem(itemno)->GetStatus(m_itemlist[m_haveitem]);
	}
	retstatus.MaxHelth = DEFAULTHELTH + m_itemlist[32].m_maxhelth + m_itemlist[33].m_maxhelth + m_itemlist[34].m_maxhelth + m_itemlist[35].m_maxhelth + handstatus.MaxHelth;
	retstatus.AttackSpeed = DEFAULTATTACKSPEED + m_itemlist[32].m_attackspeed + m_itemlist[33].m_attackspeed + m_itemlist[34].m_attackspeed + m_itemlist[35].m_attackspeed + handstatus.AttackSpeed;
	retstatus.Damage = DEFAULTDAMAGE + m_itemlist[32].m_damage + m_itemlist[33].m_damage + m_itemlist[34].m_damage + m_itemlist[35].m_damage + handstatus.Damage;
	retstatus.Def = DEFAULTDEF + m_itemlist[32].m_def + m_itemlist[33].m_def + m_itemlist[34].m_def + m_itemlist[35].m_def + handstatus.Def;
	retstatus.MoveSpeed = DEFAULTMOVESPEED + m_itemlist[32].movespeed + m_itemlist[33].movespeed + m_itemlist[34].movespeed + m_itemlist[35].movespeed + handstatus.MoveSpeed;

	return retstatus;
}

void Inventory::Attack()
{
	if (m_itemlist[m_haveitem].m_ItemNo >= 0)
	{
		DictionaryItem::GetItem(m_itemlist[m_haveitem].m_ItemNo)->Attack(m_itemlist[m_haveitem]);
	}

}

void Inventory::Use()
{
	if (m_itemlist[m_haveitem].m_ItemNo >= 0 && m_itemlist[m_haveitem].m_skillCD <= 0)
	{
		DictionaryItem::GetItem(m_itemlist[m_haveitem].m_ItemNo)->Use(&m_itemlist[m_haveitem]);
	}
}

void Inventory::Getitem(Item getitem)
{
	for (int i = 0; i < 32; i++)
	{
		if (m_itemlist[i].m_ItemNo >= 0 && m_itemlist[i].m_ItemNo == getitem.m_ItemNo && m_itemlist[i].m_ItemNum < DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack())
		{
			m_itemlist[i].m_ItemNum += getitem.m_ItemNum;
			getitem.m_ItemNum = 0;
			getitem.m_ItemNo = -1;
			if (m_itemlist[i].m_ItemNum > DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack())
			{
				getitem.m_ItemNum = m_itemlist[i].m_ItemNum - DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack();
				getitem.m_ItemNo = m_itemlist[i].m_ItemNo;
				m_itemlist[i].m_ItemNum = DictionaryItem::GetItem(m_itemlist[i].m_ItemNo)->GetMaxStack();
				if (getitem.m_ItemNum > 0)
				{
					Getitem(getitem);
				}
			}
		}
	}
	if (getitem.m_ItemNum > 0)
	{
		for (int i = 0; i < 32; i++)
		{
			if (m_itemlist[i].m_ItemNo < 0)
			{
				m_itemlist[i] = getitem;
				getitem.m_ItemNo = -1;
				break;
			}
		}
	}
	if (getitem.m_ItemNo > -1)
	{
		Dropitem* item =  Manager::GetScene()->AddObject<Dropitem>(1);
		Player* player = Manager::GetScene()->GetGameObject<Player>();
		item->SetPosition(*player->GetPosition());
		item->Setitem(getitem);
		item->SetDroptime(150);
	}
}

void Inventory::ShowUI(bool flug)
{
	m_ShowUI = flug;
}
