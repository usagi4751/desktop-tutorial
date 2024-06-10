#pragma once

void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void Setmap(int n);//マップをセットする
float GetmapMaxXpos();//最大移動座標
int Getmaptex();//bgのテクスチャ
std::string Getmapname();//ゴールの設定
float* Getgoalpos();
int Getgomap();

