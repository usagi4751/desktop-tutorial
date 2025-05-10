#pragma once
#include "main.h"
// lx, ly, lz : レイの始点
// vx, vy, vz : レイの方向ベクトル
// px, py, pz : 球の中心点の座標
// r : 球の半径
bool calcRaySphere(
	float lx, float ly, float lz,
	float vx, float vy, float vz,
	float px, float py, float pz,
	float r
);
// lx, ly, lz : レイの始点
// vx, vy, vz : レイの方向ベクトル
// px, py, pz : 球の中心点の座標
// r : 球の半径
// q1x, q1y, q1z: 衝突開始点（戻り値）
// q2x, q2y, q2z: 衝突終了点（戻り値）
bool calcRaySphere(
    float lx, float ly, float lz,
    float vx, float vy, float vz,
    float px, float py, float pz,
    float r,
    float& q1x, float& q1y, float& q1z,
    float& q2x, float& q2y, float& q2z
);

// lx, ly, lz : レイの始点
// vx, vy, vz : レイの方向ベクトル
// px, py, pz : 球の中心点の座標
// r : 球の半径
// q1x, q1y, q1z: 衝突開始点（戻り値）
bool calcRaySphere(
    XMFLOAT3* lp,
    float vx, float vy, float vz,
    float px, float py, float pz,
    float r,XMFLOAT3* hitpoint
);

bool IsCollision(float px, float py, float pz, float r, float px2, float py2, float pz2, float r2);
