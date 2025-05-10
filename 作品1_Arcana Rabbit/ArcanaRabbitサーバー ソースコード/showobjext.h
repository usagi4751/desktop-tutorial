#pragma once
//モデルを読み込んで表示するだけのクラス
#include "Component.h"
#include "gameObject.h"
enum ShaderSetting
{
	Nomal,
	hemisphereLighting
};
class ShowObject :public GameObject
{
private:
	Component* m_Component{};

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;

	ID3D11InputLayout* m_VertexLayout;

public:
	ShowObject() { m_Component = nullptr; }
	virtual void Init() ;
	virtual void Uninit() ;
	virtual void Update() ;
	virtual void Draw() ;
	void SetObject(const char* Loadonject) ;
	void SetShader(ShaderSetting setting);
};

