#pragma once
#include "main.h"
class ParticleManager;
class particleEmitter;
//=============================================
//�p�[�e�B�N���}�l�[�W���̃C���^�[�t�F�[�X
//=============================================
class ParticleInerface {
private:
	static ParticleManager* m_manager;
public:
	//�}�l�[�W���̐ڑ�
	static void Link(ParticleManager* manager);
	//������
	static void Init();
	//���
	static void Uninit();
	//�G�~�b�^�[�̍쐬
	static void SetEmitter(particleEmitter* emitter);
};

