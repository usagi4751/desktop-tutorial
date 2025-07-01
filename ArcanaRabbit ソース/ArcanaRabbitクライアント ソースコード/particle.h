#pragma once


#pragma once
#include "Component.h"
#include "gameObject.h"
class particleEmitter;
//�Z�����邽�߂ɂ܂Ƃ߂�
struct Shader_Layout {
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* VertexLayout;
};
//�T�[�N����Ƀp�[�e�B�N�����o�����߂ɍ����
struct Sorcletime {//�T�[�N���p�[�e�B�N��
	bool issorcle;//�T�[�N�����g����
	bool isEmitter;//�G�~�b�^�[�̍��W���g����
	bool isNoVel;//�x�N�g�����󂯂邩�󂯂Ȃ���
	XMFLOAT2 Rotate;//���W�̉�]��
	XMFLOAT2 RotateVel;//���W�̉�]��
	float distance;//�G�~�b�^�[���痣��Ă鋗��
};
struct Particle_data
{
	XMFLOAT3 m_Vel;
	int m_life;
	XMFLOAT3 pos;//���W
	XMFLOAT2 scale;
	XMFLOAT4 coler;
	XMFLOAT4 endcoler;
	int tex;
	XMFLOAT2 uv_u;
	XMFLOAT2 uv_v;
};
class particle 
{
private:
	Particle_data m_data;
	int maxlife;//���̃��C�t
	XMFLOAT3 m_drawpos;//�\���ʒu
	Sorcletime m_sorcler;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	Shader_Layout m_SL;
	particleEmitter* m_emitter = nullptr;//�������̃G�~�b�^�[
public:
	virtual void crete(ID3D11PixelShader* pixelshader, ID3D11VertexShader* vertexshader, ID3D11InputLayout* vertexlayout);
	virtual void Release();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void SetParticle(Particle_data data, particleEmitter* emitter) {
		m_data = data; m_emitter = emitter; m_sorcler = {}; maxlife = data.m_life;
		Update();
	};
	virtual void SetParticle(Particle_data data, particleEmitter* emitter , Sorcletime sorcle) {
		m_data = data; m_emitter = emitter; m_sorcler = sorcle; maxlife = data.m_life;
		Update();
	};
	
	int Getlife() { return m_data.m_life; };
};

