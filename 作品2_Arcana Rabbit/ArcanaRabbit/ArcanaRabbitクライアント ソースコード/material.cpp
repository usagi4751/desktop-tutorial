#include "material.h"
#include "Texture.h"

Image_Material g_Image_Material;
void LoadMaterial(void) {
	g_Image_Material.m_yuka = LoadTexture(L"asset\\texture\\sibafu.jpg");
	g_Image_Material.m_fade = LoadTexture(L"asset\\texture\\fade.png");
	g_Image_Material.m_testimage = LoadTexture(L"asset\\texture\\gameicon.png");
	g_Image_Material.m_particle_Ster = LoadTexture(L"asset\\texture\\glint.png");
	g_Image_Material.m_particle_Flame = LoadTexture(L"asset\\texture\\flame.png");
	g_Image_Material.m_reticle_1 = LoadTexture(L"asset\\texture\\reticler.png");
	g_Image_Material.m_UI_image1 = LoadTexture(L"asset\\texture\\inventory_ui1.png");
	g_Image_Material.m_UI_image2 = LoadTexture(L"asset\\texture\\inventory_ui2.png");
	g_Image_Material.m_UI_image3 = LoadTexture(L"asset\\texture\\skillwindow.png");
	g_Image_Material.m_UI_image4 = LoadTexture(L"asset\\texture\\gui3.png");
	g_Image_Material.m_UI_image5 = LoadTexture(L"asset\\texture\\attackCT.png");
	g_Image_Material.m_UI_image6 = LoadTexture(L"asset\\texture\\titol.png");
	g_Image_Material.m_System_Cursor = LoadTexture(L"asset\\texture\\cursor.png");
	g_Image_Material.m_ItemTex_Stick = LoadTexture(L"asset\\texture\\stick.png");
	g_Image_Material.m_ItemTex_wand = LoadTexture(L"asset\\texture\\magic wand.png");
	g_Image_Material.m_ItemTex_SlagHelmet = LoadTexture(L"asset\\texture\\slaghelmet.png");
	g_Image_Material.m_ItemTex_SlagChest = LoadTexture(L"asset\\texture\\cloth.png");
	g_Image_Material.m_ItemTex_Slagwaistband = LoadTexture(L"asset\\texture\\Cloth waistband.png");
	g_Image_Material.m_ItemTex_SlagBoots = LoadTexture(L"asset\\texture\\slagboots.png");
	g_Image_Material.m_ItemTex_SlagSword = LoadTexture(L"asset\\texture\\slugsword.png");
	g_Image_Material.m_titol = LoadTexture(L"asset\\texture\\arcana.png");
	g_Image_Material.m_textbox = LoadTexture(L"asset\\texture\\textber.png");
	g_Image_Material.m_SOUSINButuun = LoadTexture(L"asset\\texture\\sousin.png");
	g_Image_Material.m_Mozi  = LoadTexture(L"asset\\texture\\mozi4.png");
}
Image_Material& GetImage(void)
{
	return g_Image_Material;
}