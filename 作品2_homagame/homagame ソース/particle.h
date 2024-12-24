#pragma once
#define PAI 3.141593f
#define MAXPARTICLE 8192 
typedef struct {
	bool use;//パーティクルを使っているか 
	float time;//現在時間 
	float lp;//[時間]パーティクルの表示時間 
	int na;//パーティクル名 
	float posx;//[座標]x 
	float posy;//[座標]y 
	float sp;//[速度]パーティクルの速さ 
	float si;//[サイズ] パーティクルの大きさ 
	float di;//[方向]0～2πの方向 
	float re;//[減速率]空気抵抗のようなもの 
	float we;//[重量]重力で落下するような再現する 
	float r;
	float g;
	float b;

}PARTICLE;	

//float dposx;//[範囲座標]x 生成したときにばらつきがあるか 
//float dposy;//[範囲座標]y 生成したときにばらつきがあるか 
//int nu;//[個数]生成する個数
//int mo;//[モード] パーティクルの広がる向き 0全方位 1上方向のみ
//float co;//[収束率]0～180° +-となる
//float lr;//[表示時間率]lpの時間が変わる
//float sir;//[サイズのランダム]0-1でサイズが変わる

void Initparticle(void);
void Uninitparticle(void);
void Updateparticle(void);
void Drawparticle(void);
void setparticle(
	int pa_na,
	float pa_x, float pa_y,   //パーティクル座標
	float pa_dx, float pa_dy,//パーティクル生成座標範囲
	float pa_sp,//パーティクル速度
	int pa_nu,//パーティクル生成個数
	float pa_si,//サイズ
	//ここまでは書く
	float pa_di = -1.0f, //方向
	float pa_co = -1.0f, //収束率
	float pa_re = -1.0f,//減速率
	float pa_we = -1.0f,//重量
	float pa_lp = -1.0f,//時間
	float pa_lr = -1.0f,//表示時間率
	float pa_spr = -1.0f,//スピードランダム
	float pa_sir = -1.0f,//サイズランダム
	float pa_r = 1.0f,//カラーR
	float pa_g = 1.0f,//カラーG
	float pa_b = 1.0f//カラーB
);
int Getparticletex(int n);
void clearparticleAll();


