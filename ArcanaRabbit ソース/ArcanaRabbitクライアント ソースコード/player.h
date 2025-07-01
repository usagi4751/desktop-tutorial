#pragma once
#include "Component.h"
#include "gameObject.h"
#include "draw2d_Manager.h"
#define DEFAULTHELTH (20)
#define DEFAULTDEF (0)
#define DEFAULTATTACKSPEED (100)
#define DEFAULTMOVESPEED (100)
#define DEFAULTDAMAGE (1)
class Floor;
class Enemy;
class Player :public GameObject
{
private:
	Component* m_Componentplayer{};
	Component* m_Component{};
	Component* m_audio;
	UI_Tex m_Reticl;//レティクル

	Floor* m_floor;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	bool m_fly;//飛行できるか
	float m_NowHp;//現在体力
	float m_AttackCD;//攻撃のクールタイム
	XMFLOAT3 m_oldpos;//1フレーム前の座標
	XMFLOAT3 m_vel;//慣性
	int m_haveitem;//持ってるアイテムのスロット
	float m_NomalAttackRange;//通常攻撃の射程

	//フラグ
	bool m_InventoryOpen;//インベントリを開いているか
	bool clip = true;//マウス閉じ込める用
	bool m_IsGround;//地面に接触しているか

	//デバック用
	int size = 1;//床塗り用

	//通常物理法則
	void NomalOperation();
	//地面との接触判定
	void IsGround();
	//ジャンプ処理
	void Jump();
	//移動処理
	void Move();
	//カメラの更新処理
	void CameraUpdate();
	//プレイヤーのアクション
	void Action();
	//ステータスのアップデート
	void StatusTimeUpdate();

	//===========================
	//開発用関数
	//===========================
	//開発用:マップのセーブとロード
	void DevelopSaveAndLoad();
	//開発用:床塗り
	void DevelopNuru();
	//開発用:飛行
	void DevelopFreeFly();
	//開発用:デバックコマンド
	void DevelopDebugComand();
	//開発用:開発用のUI
	void DevelopDebugUI();
	//開発用:飛行時物理法則
	void DevelopFlyOperation();
public:
	virtual void Init() ;
	virtual void Uninit() ;
	virtual void Update() ;
	virtual void Draw();



	XMFLOAT3 PlayerRay();//プレイヤーの視線
	float GetNomalAttackRange() { return m_NomalAttackRange; };//通常攻撃のレンジ
	XMFLOAT3 GetRot() { return m_Rotation; }//プレイヤーの回転情報
	void AddDamage(float damage);//プレイヤーにダメージを与える時に使う
	void Addheal(float heal);//プレイヤーに回復を与える時に使う


};

