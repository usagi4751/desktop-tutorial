#include "draw2d_Manager.h"
#include "renderer.h"
#include "material.h"
#include "Texture.h"
std::list<UI*> Draw2D_Manager::m_UIList;
std::list<UI*> Draw2D_Manager::m_DeleteList;
bool Draw2D_Manager::m_ClearFlug;
DrawTex Draw2D_Manager::m_Shader;
DirectWrite* Draw2D_Manager::m_write;

UI_Tex* Draw2D_Manager::AddUI()
{

	UI_Tex* ui = new UI_Tex();
	ui->Init();
	ui->m_Active = true;
	ui->SetColer({ 1.0f,1.0f,1.0f ,1.0f });
	m_UIList.push_back(ui);
	return ui;
}

UI_Text* Draw2D_Manager::AddTEXT()
{

	UI_Text* ui = new UI_Text(m_write);
	ui->Init();
	ui->m_Active = true;
	ui->SetColer({ 1.0f,1.0f,1.0f ,1.0f });
	ui->SetScale(30);
	m_UIList.push_back(ui);
	return ui;
}

void Draw2D_Manager::Init()
{
	//=======================================
	// 文字初期化
	//=======================================
	FontData* fodata = new  FontData();
	fodata->fontSize = 100;
	fodata->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	m_write = new DirectWrite(fodata);
	m_write->TextInit();
	delete fodata;
	//=======================================
	// 画像初期化
	//=======================================



	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_Shader.m_VertexShader, &m_Shader.m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_Shader.m_PixelShader,
		"shader\\unlitTexturePS.cso");
}

void Draw2D_Manager::Uninit()
{
	Update();
	for (UI* ui : m_UIList)
	{
		ui->UnInit();
		delete ui;
	}
	m_write->TextRelease();
	delete m_write;
	m_UIList.clear();
}

void Draw2D_Manager::Update()
{
	if (m_DeleteList.size() > 0)
	{
		for (UI* ui : m_DeleteList) {
			m_UIList.remove(ui);
		}
	}
	if (m_ClearFlug == true)
	{
		for (UI* ui : m_UIList)
		{
			ui->UnInit();
			delete ui;
		}
		m_UIList.clear();
	}
	for (UI* ui : m_UIList)
	{
		ui->Update();
	}
}

void Draw2D_Manager::Draw()
{
	m_UIList.sort([](UI* y, UI* n) {return y->m_Depth< n->m_Depth; });
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_Shader.m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_Shader.m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_Shader.m_PixelShader, NULL, 0);
	Renderer::SetWorldViewProjection2D();
	// 2D描画なので深度無効
	Renderer::SetDepthEnable(false);
	for (UI* ui : m_UIList)
	{
			ui->Draw();//描画処理
	}
	//Z比較あり
	Renderer::SetDepthEnable(true);
}

void Draw2D_Manager::Clear()
{
	m_ClearFlug = true;
}

void Draw2D_Manager::DeleateUI(UI* ui)
{
	ui->UnInit();
	m_DeleteList.push_back(ui);
	delete ui;
}


void UI_Text::UnInit()
{
	m_text->clear();
	delete  m_text;
	 if (m_Object != nullptr) {
		 m_Object->m_text->clear();
		 delete  m_Object->m_text;
		 delete m_Object;}
}

void UI_Text::Draw()
{
	if (m_Active == true)
	{
		m_write->SetTextColer(m_Color);
		m_write->SetTextSize(m_scale);
		m_write->DrawString(*m_text, m_rect);
	}
}

void UI_Tex::Init()
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	VERTEX_3D vertex[4];

	float sX = m_Texdata.m_Scale.x * 0.5f;
	float sY = m_Texdata.m_Scale.y * 0.5f;
	float srot = sinf(m_Texdata.m_Rotation);
	float crot= cosf(m_Texdata.m_Rotation);


	vertex[0].Position.x = -sX * crot - -sY * srot + m_Texdata.m_Position.x;
	vertex[0].Position.y = -sX * srot + -sY * crot + m_Texdata.m_Position.y;
	vertex[1].Position.x =  sX * crot - -sY * srot + m_Texdata.m_Position.x;
	vertex[1].Position.y =  sX * srot + -sY * crot + m_Texdata.m_Position.y;
	vertex[2].Position.x = -sX * crot -  sY * srot + m_Texdata.m_Position.x;
	vertex[2].Position.y = -sX * srot +  sY * crot + m_Texdata.m_Position.y;
	vertex[3].Position.x =  sX * crot -  sY * srot + m_Texdata.m_Position.x;
	vertex[3].Position.y =  sX * srot +  sY * crot + m_Texdata.m_Position.y;

	vertex[0].Position.z = 0;
	vertex[1].Position.z = 0;
	vertex[2].Position.z = 0;
	vertex[3].Position.z = 0;

	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
	
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);


	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void UI_Tex::UnInit()
{
	delete m_Object;
	m_VertexBuffer->Release();
}

void UI_Tex::Update()
{
	if (m_Texdata.m_UpdateFlug == true)
	{
		m_Texdata.m_UpdateFlug = false;
		m_VertexBuffer->Release();
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		VERTEX_3D vertex[4];
		float sX = m_Texdata.m_Scale.x * 0.5f;
		float sY = m_Texdata.m_Scale.y * 0.5f;
		float srot = sinf(m_Texdata.m_Rotation);
		float crot = cosf(m_Texdata.m_Rotation);

		vertex[0].Position.x = -sX * crot - -sY * srot + m_Texdata.m_Position.x;
		vertex[0].Position.y = -sX * srot + -sY * crot + m_Texdata.m_Position.y;
		vertex[1].Position.x = sX * crot - -sY * srot + m_Texdata.m_Position.x;
		vertex[1].Position.y = sX * srot + -sY * crot + m_Texdata.m_Position.y;
		vertex[2].Position.x = -sX * crot - sY * srot + m_Texdata.m_Position.x;
		vertex[2].Position.y = -sX * srot + sY * crot + m_Texdata.m_Position.y;
		vertex[3].Position.x = sX * crot - sY * srot + m_Texdata.m_Position.x;
		vertex[3].Position.y = sX * srot + sY * crot + m_Texdata.m_Position.y;

		vertex[0].Position.z = 0;
		vertex[1].Position.z = 0;
		vertex[2].Position.z = 0;
		vertex[3].Position.z = 0;

		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}
}

void UI_Tex::Draw()
{
	if (m_Active == true)
	{
		// 頂点バッファ設定
		UINT	 stride = sizeof(VERTEX_3D);
		UINT	 offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		// マテリアルのセット
		MATERIAL mtl;
		ZeroMemory(&mtl, sizeof(mtl));

		mtl.Diffuse = { m_Texdata.m_Color.x,m_Texdata.m_Color.y,m_Texdata.m_Color.z,m_Texdata.m_Color.w };
		mtl.Ambient = { 0.0f,0.0f,0.0f,1.0f };
		mtl.Emission = { 1.0f,1.0f,1.0f,1.0f };
		mtl.TextureEnable = true;
		Renderer::SetMaterial(mtl);
		// テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_Texdata.m_Tex));
		// プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

