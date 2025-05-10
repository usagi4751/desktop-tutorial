#include "collision.h"
#include "main.h"
bool calcRaySphere(
	float lx, float ly, float lz,
	float vx, float vy, float vz,
	float px, float py, float pz,
	float r
) {
	px = px - lx;
	py = py - ly;
	pz = pz - lz;

	float A = vx * vx + vy * vy + vz * vz;
	float B = vx * px + vy * py + vz * pz;
	float C = px * px + py * py + pz * pz - r * r;

	if (A == 0.0f)
		return false; // レイの長さが0

	float s = B * B - A * C;
	if (s < 0.0f)
		return false; // 衝突していない

	s = sqrtf(s);
	float a1 = (B - s) / A;
	float a2 = (B + s) / A;

	if (a1 < 0.0f || a2 < 0.0f)
		return false; // レイの反対で衝突



	return true;
}
bool calcRaySphere(
    float lx, float ly, float lz,
    float vx, float vy, float vz,
    float px, float py, float pz,
    float r,
    float& q1x, float& q1y, float& q1z,
    float& q2x, float& q2y, float& q2z
) {
    px = px - lx;
    py = py - ly;
    pz = pz - lz;

    float A = vx * vx + vy * vy + vz * vz;
    float B = vx * px + vy * py + vz * pz;
    float C = px * px + py * py + pz * pz - r * r;

    if (A == 0.0f)
        return false; // レイの長さが0

    float s = B * B - A * C;
    if (s < 0.0f)
        return false; // 衝突していない

    s = sqrtf(s);
    float a1 = (B - s) / A;
    float a2 = (B + s) / A;

    if (a1 < 0.0f || a2 < 0.0f)
        return false; // レイの反対で衝突

    q1x = lx + a1 * vx;
    q1y = ly + a1 * vy;
    q1z = lz + a1 * vz;
    q2x = lx + a2 * vx;
    q2y = ly + a2 * vy;
    q2z = lz + a2 * vz;

    return true;
}

bool calcRaySphere(XMFLOAT3* lp, float vx, float vy, float vz, float px, float py, float pz, float r, XMFLOAT3* hitpoint)
{
    px = px - lp->x;
    py = py - lp->y;
    pz = pz - lp->z;

    float A = vx * vx + vy * vy + vz * vz;
    float B = vx * px + vy * py + vz * pz;
    float C = px * px + py * py + pz * pz - r * r;

    if (A == 0.0f)
        return false; // レイの長さが0

    float s = B * B - A * C;
    if (s < 0.0f)
        return false; // 衝突していない

    s = sqrtf(s);
    float a1 = (B - s) / A;
    float a2 = (B + s) / A;

    if (a1 < 0.0f || a2 < 0.0f)
        return false; // レイの反対で衝突

    hitpoint->x = lp->x + a1 * vx;
    hitpoint->y = lp->y + a1 * vy;
    hitpoint->z = lp->z + a1 * vz;

    return true;
}

bool IsCollision(float px, float py, float pz, float r, float px2, float py2, float pz2, float r2)
{
    //2点間の距離の2乗
    XMFLOAT3 vec = { px - px2, py - py2 , pz - pz2 };
    float dis = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;



    //半径の和が距離の2乗以下だったら
    if (dis <= powf(r + r2, 2))
        return true;
    return false;
}


