//=============================================================================
//
// �J�[�h���C������ [card.cpp]
// Author : 
//
//=============================================================================
#include "carddatamanager.h"
#include "cardmenumanager.h"
#include "cardplaypdeckmanager.h"
#include "cardplayuse_manager.h"
#include "card_base.h"
#include "cardplaygetcardh.h"

#include "input.h"
#include "cardmanuget.h"
#include "camera.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CardDataManager			g_CardData;//�Q�[���J�[�h�f�[�^�ۊ�
CardMenu_Manager		g_CardMenu(&g_CardData);//���j���[��ʂ̃J�[�h�f�[�^�ۊ�
CardPlay_Manager		g_CardPlayDeck;//�Q�[�����J�[�h�f�[�^�ۊ�
Card_GetCard			g_CardGet;//�J�[�h�擾����
CardPlayUse_Manager		g_CardPlayUse;//�Q�[�����̃J�[�h�̑���
DropCardManager			g_DropCard(&g_CardData, &g_CardGet,&g_CardPlayDeck);
CardMenu_Get			g_CardMenuGet(&g_CardMenu, &g_CardData);
void InitCard() {
	g_CardData.InitCard();
	g_CardPlayUse.InitLink(&g_CardPlayDeck);
	
	g_CardGet.LinkData(&g_CardPlayDeck, &g_DropCard);

	g_CardPlayDeck.GetDeck(&g_CardMenu);

}
void UninitCard() {
	g_DropCard.Uninit();
	g_CardPlayUse.Uninit();
	g_CardGet.Uninit();
}
void UpdateCard() {


	if (g_CardGet.InData() == false)
	{
		g_CardPlayUse.Update();
	}
	g_DropCard.Update();
	g_CardGet.Update();
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_V))
	{
		g_DropCard.NoHaveCardDrop(GetCamera()->pos, 0.5f);
	}
#endif // _DEBUG


	
}
void DrawCard() {

	g_DropCard.Draw();
	
}
void DrawCard2D() {

	//�Q�[���v���C��ʂ̂t�h�\��
	g_CardPlayUse.Draw();

	//Tab���������̉�ʕ\��
	if (g_CardGet.InData() == false)
	{
		g_CardPlayDeck.TabDraw();
	}
	

	//�J�[�h�擾�����\��
	g_CardGet.DrawUI();
	//���j���[�̃J�[�h�\��
  //  g_CardMenu.DrawCard();
}
void Update_Menu_deck(void) {
	g_CardMenuGet.Update();
}
void Draw_Menu_deck(void) {
	g_CardMenuGet.DrawUI();
}
bool GetCardflug() {
	if (g_CardGet.InData())
	{
		return true;
	}
	return false;
}
DropCardManager* PGetDropCard() {
	return &g_DropCard;
}
void CardDropChance(D3DXVECTOR3 droppos,float rank2Weight) {
	g_DropCard.NoHaveCardDrop(droppos, rank2Weight);
}