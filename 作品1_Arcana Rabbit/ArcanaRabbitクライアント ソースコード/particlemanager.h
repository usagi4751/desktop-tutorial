#pragma once
#include <list>
#include "Component.h"
#include "gameObject.h"
#include "particle.h"
#define MAXPARTICLE (4096)
//============================
// �p�[�e�B�N�����Ǘ�����}�l�[�W��
//============================
class particleEmitter;
class ParticleManager :public GameObject
{
private:
	particle m_particle[MAXPARTICLE];
	std::list<particleEmitter*> m_Emitterlist;
	Component* m_Component{};
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
public:
	//������
	virtual void Init();
	//���
	virtual void Uninit();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���\�[�X�̐���1�񂾂��Ă�
	virtual void Create();
	//�I���@�Ō�ɌĂ�
	virtual void Release();
	//�p�[�e�B�N���̍쐬
	virtual void Addperticle(Particle_data data, particleEmitter* emitter = nullptr, Sorcletime sorcle = {});
	//�p�[�e�B�N���G�~�b�^�[�̍쐬
	virtual void AddEmitter(particleEmitter* emitter);
//	void AddEmitter(particleEmitter* emitter) { m_EmitterList.push_back(emitter); };
	

};

