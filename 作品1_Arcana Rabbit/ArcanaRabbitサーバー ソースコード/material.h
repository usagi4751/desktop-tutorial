#pragma once

struct Image_Material
{
	int m_textbox;//�e�L�X�gBox�w�i
	int m_yuka;//��
	int m_testimage;
	int m_particle_Ster;
	int m_particle_Flame;//���p�[�e�B�N��
	int m_reticle_1;//1�l�̎��_�̃��e�B�N��
	int m_UI_image1;//�C���x���g��
	int m_UI_image2;//�C���x���g��
	int m_UI_image3;//skill���߂�
	int m_UI_image4;//�����Ă�A�C�e���A�C�R��
	int m_UI_image5;//�U���̂����\���p
	int m_UI_image6;//Titol
	int m_fade;//�t�F�[�h
	int m_System_Cursor;//�J�[�\��
	int m_ItemTex_Stick;//�A�C�e���F�_
	int m_ItemTex_wand;//�A�C�e���F��
	int m_ItemTex_SlagHelmet;//�A�C�e���F
	int m_ItemTex_SlagChest;//�A�C�e���F
	int m_ItemTex_Slagwaistband;//�A�C�e���F
	int m_ItemTex_SlagBoots;//�A�C�e���F
	int m_ItemTex_SlagSword;//�A�C�e���F
	int m_titol;//�^�C�g���F
	int m_SOUSINButuun;//���M�{�^���F
};
void LoadMaterial(void);
Image_Material& GetImage(void);