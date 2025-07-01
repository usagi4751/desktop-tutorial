#pragma once
#include "main.h"
// lx, ly, lz : ���C�̎n�_
// vx, vy, vz : ���C�̕����x�N�g��
// px, py, pz : ���̒��S�_�̍��W
// r : ���̔��a
bool calcRaySphere(
	float lx, float ly, float lz,
	float vx, float vy, float vz,
	float px, float py, float pz,
	float r
);
// lx, ly, lz : ���C�̎n�_
// vx, vy, vz : ���C�̕����x�N�g��
// px, py, pz : ���̒��S�_�̍��W
// r : ���̔��a
// q1x, q1y, q1z: �ՓˊJ�n�_�i�߂�l�j
// q2x, q2y, q2z: �ՓˏI���_�i�߂�l�j
bool calcRaySphere(
    float lx, float ly, float lz,
    float vx, float vy, float vz,
    float px, float py, float pz,
    float r,
    float& q1x, float& q1y, float& q1z,
    float& q2x, float& q2y, float& q2z
);

// lx, ly, lz : ���C�̎n�_
// vx, vy, vz : ���C�̕����x�N�g��
// px, py, pz : ���̒��S�_�̍��W
// r : ���̔��a
// q1x, q1y, q1z: �ՓˊJ�n�_�i�߂�l�j
bool calcRaySphere(
    XMFLOAT3* lp,
    float vx, float vy, float vz,
    float px, float py, float pz,
    float r,XMFLOAT3* hitpoint
);

bool IsCollision(float px, float py, float pz, float r, float px2, float py2, float pz2, float r2);
