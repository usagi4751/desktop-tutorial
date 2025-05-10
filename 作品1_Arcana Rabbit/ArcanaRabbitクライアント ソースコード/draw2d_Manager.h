//*****************************************************************************
//	draw2d_Manager.h 
// Draw2D_Manager2....�������A�I���A�X�V�A�`�揈���B����������
// 
// �ȉ��N���X�}
// 
//         UI(�p����)
//     ����������
//     ��      ��
// UI_Text   UI_Tex
// �����`��  �摜�`��
//*****************************************************************************
#pragma once
#include "main.h"
#include "font.h"
#include "gameObject.h"
#include <list>
#define DEPTH_NOMAL (0.1f) //��{�[�x
//*****************************************************************************
//�O���錾
//*****************************************************************************

class UI;
class UI_Tex;
class UI_Text;
//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct DrawTex //�o�b�t�@�[��V�F�[�_�[�֘A�̍\����
{
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
};

struct  UITexData //�摜2D�`��Ŏg�p����
{
	bool m_UpdateFlug = false;//�摜�̍X�V�����������̊m�F�p�|���S���̍Đ������邽�߂Ɏg��
	bool m_DrawFlug = true;//�|���S���̕\�������邩
	XMFLOAT4   m_Color = { 1.0f,1.0f ,1.0f ,1.0f };
	XMFLOAT2   m_Position = {50.0f,50.0f};
	XMFLOAT2   m_Scale = { 100.0f,100.0f };;
	XMFLOAT2   m_UV_uv = {0.0f,0.0f};	// UV�l�� : ��
	XMFLOAT2   m_UV_UV = { 1.0f,1.0f };;	// UV�l�E : ��
	float   m_Rotation = 0.0f;
	int     m_Tex = 0;
};
//2D�`��̊Ǘ��@
//�d�l
//�@�\�F�������A�X�V�A�`��AUI�I�u�W�F�N�g�̒ǉ�
//UI���g�������ꍇDraw2D_Manager���g�p���č�������łȂ��ƕ\������Ȃ�
//�ύX�͐������Ɏ󂯎�����|�C���^�ŃZ�b�g�֐����ĂԂ��ƂŕύX�\

class Draw2D_Manager {
private:
	static bool m_ClearFlug;//�e�L�X�g���N���A����邩�̃t���O
	static std::list<UI*> m_DeleteList;//�폜�����UI
	static std::list<UI*> m_UIList;

	static DrawTex m_Shader;//�V�F�[�_
	static DirectWrite* m_write;//�����\���N���X
public:
	static UI_Tex* AddUI();//�摜�̕`��ǉ�
	static UI_Text* AddTEXT();//�e�L�X�g�̒ǉ�
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	//���݂���UI�����ׂč폜����
	static void Clear();
	//�w���UI���폜����
	static void DeleateUI(UI* ui);
};



//===============================
//���N���X
//===============================
class UI {	

public:
	float  m_Depth;	//UI�̐[�x
	bool   m_Active;//�\�����邩
	virtual ~UI() = default;

	virtual void   Init() = 0;
	virtual void   UnInit() = 0;
	virtual void   Update() = 0;
	virtual void   Draw() = 0;
};

//====================
// �����\���p�̃N���X
//====================
class UI_Text : public UI{
private:
	UI_Text* m_Object;//set�ŕύX�����Text
	XMFLOAT4   m_Color = {1.0f,1.0f ,1.0f ,1.0f };		// �����̃J���[
	D2D1_RECT_F m_rect;		//�`��͈͔͈̔͂𒴂���Ɖ��s�����
	float m_scale;			//�����T�C�Y
	std::string* m_text;		//�`�悳��镶��
	DirectWrite* m_write;	//�`��N���X
public: 
	UI_Text(DirectWrite* write) : m_write(write) { m_scale = 30; m_text = new std::string; };
	UI_Text() { m_scale = 30; };
	void Link(UI_Text* link) { m_Object = link; };

	void SetRect(XMFLOAT4 Rect) { if (m_Object != nullptr) { m_Object ->m_rect = { Rect.x,Rect.y,Rect.z,Rect.w };}  }
	void SetColer(XMFLOAT4 coler) { if (m_Object != nullptr) { m_Object->m_Color = coler; } }
	void SetText(std::string text) { 
		if (m_Object != nullptr) { *m_Object->m_text = text; } 
	};
	void SetScale(float scale) { if (m_Object != nullptr) { m_Object->m_scale = scale; } };
	void  SetDepth(float Depth) { if (m_Object != nullptr) { m_Object->m_Depth = Depth; }; }
	void SetActive(bool active) { if (m_Object != nullptr) { m_Object->m_Active = active; }; };
	UI_Text* GetObjectData() {return m_Object;};
	void Init() {};
	void UnInit() ;
	void Update() {};
	void Draw() override;
};
//====================
// �摜�\���p�̃N���X
//====================
class UI_Tex : public UI
{
private:
	UI_Tex* m_Object;//set�ŕύX�����UI
	//�|���S���̐����ɕK�v�ȃf�[�^
	UITexData m_Texdata;

	ID3D11Buffer* m_VertexBuffer = nullptr;
public:
	void Init() ;
	void UnInit();
	void Update();
	void Draw() override;

	void Link(UI_Tex* link) { m_Object = link; };

	//�Z�b�^�[
	void SetColer(XMFLOAT4 coler) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Color = coler; } };
	void SetPosition(XMFLOAT2 position) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Position = position;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetScale(XMFLOAT2 scale) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Scale = scale;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetUV(XMFLOAT2   uv, XMFLOAT2   UV) { if (m_Object != nullptr) { m_Object->m_Texdata.m_UV_uv = uv; m_Object->m_Texdata.m_UV_UV = UV;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetRotation(float rotation) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Rotation = rotation;  m_Object->m_Texdata.m_UpdateFlug = true; } };
	void SetTex(int tex) { if (m_Object != nullptr) { m_Object->m_Texdata.m_Tex = tex; } };
	void SetDrawFlug(bool flug) { if (m_Object != nullptr) { m_Object->m_Texdata.m_DrawFlug = flug; } };
	void SetDepth(float Depth) { if (m_Object != nullptr) { m_Object->m_Depth = Depth; }; }
	void SetActive(bool active) { if (m_Object != nullptr) { m_Object->m_Active = active; }; };
	UI_Tex* GetObjectData() { return m_Object; };
	UITexData GetUITexData() { return m_Texdata; }
};


