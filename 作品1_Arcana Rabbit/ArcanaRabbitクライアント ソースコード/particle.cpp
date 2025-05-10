#include "particle.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "manager.h"
#include "particleEmitter.h"
#include "Texture.h"
#include "material.h"

void particle::Release()
{
	m_VertexBuffer->Release();
}
void particle::Init()
{
	m_data.m_life = 0;
	m_emitter = nullptr;
}

void particle::Uninit()
{
	m_data.m_life = 0;
	m_emitter = nullptr;
}

void particle::Update()
{
	XMFLOAT3 rotatepos = {};

	if (m_data.m_life > 0)m_data.m_life--;
	if (m_data.m_life <= 0)
	{
		m_emitter = nullptr;
		return;
	}
	if (m_sorcler.issorcle)
	{
		m_sorcler.Rotate.y += m_sorcler.RotateVel.y;
		m_sorcler.Rotate.x += m_sorcler.RotateVel.x;

		rotatepos.x = sinf(m_sorcler.Rotate.y) * cosf(m_sorcler.Rotate.x) * m_sorcler.distance;
		rotatepos.z = cosf(m_sorcler.Rotate.y) * cosf(m_sorcler.Rotate.x) * m_sorcler.distance;
		rotatepos.y = sinf(m_sorcler.Rotate.x) * m_sorcler.distance;
		if (m_sorcler.isEmitter ==true)
		{
			rotatepos.x += m_emitter->GetPos().x;
			rotatepos.y += m_emitter->GetPos().y;
			rotatepos.z += m_emitter->GetPos().z;
		}
	}


	if (m_sorcler.issorcle == false || m_sorcler.isNoVel == false)
	{
		//ベクトルの加算
		m_data.pos.x = m_data.pos.x + m_data.m_Vel.x;
		m_data.pos.y = m_data.pos.y + m_data.m_Vel.y;
		m_data.pos.z = m_data.pos.z + m_data.m_Vel.z;
	}
		//表示位置更新
		m_drawpos.x = m_data.pos.x + rotatepos.x;
		m_drawpos.y = m_data.pos.y + rotatepos.y;
		m_drawpos.z = m_data.pos.z + rotatepos.z;
}

void particle::Draw()
{
	Renderer::SetAlphaTestEnable(true);
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].TexCoord = XMFLOAT2(m_data.uv_u.x, m_data.uv_u.y);
	
	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].TexCoord = XMFLOAT2(m_data.uv_u.x + m_data.uv_v.x, m_data.uv_u.y);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].TexCoord = XMFLOAT2(m_data.uv_u.x, m_data.uv_u.y + m_data.uv_v.y);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].TexCoord = XMFLOAT2(m_data.uv_u.x + m_data.uv_v.x, m_data.uv_u.y + m_data.uv_v.y);
	float startrate = (float)m_data.m_life / (float)maxlife;
	float startend = 1.0f - (float)m_data.m_life / (float)maxlife;
	XMFLOAT4 coler;
	coler.x = { m_data.coler.x * startrate + m_data.endcoler.x * startend };
	coler.y = { m_data.coler.y * startrate + m_data.endcoler.y * startend };
	coler.z = { m_data.coler.z * startrate + m_data.endcoler.z * startend };
	coler.w = { m_data.coler.w * startrate + m_data.endcoler.w * startend };
	vertex[0].Diffuse = XMFLOAT4(coler.x, coler.y, coler.z, coler.w);
	vertex[1].Diffuse = XMFLOAT4(coler.x, coler.y, coler.z, coler.w);
	vertex[2].Diffuse = XMFLOAT4(coler.x, coler.y, coler.z, coler.w);
	vertex[3].Diffuse = XMFLOAT4(coler.x, coler.y, coler.z, coler.w);
	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_SL.VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_SL.VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_SL.PixelShader, NULL, 0);

	//カメラのビューマトリックス取得
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewmatrix();


	//ビューの逆行列
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	//ワールドマトリックス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_data.scale.x, m_data.scale.y,0);
	//rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.x);
	trans = XMMatrixTranslation(m_drawpos.x, m_drawpos.y, m_drawpos.z);
	world = scale * invView * trans;
	Renderer::SetWorldMatrix(world);


	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(coler.x,coler.y,coler.z, coler.w);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_data.tex));

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	Renderer::SetAlphaTestEnable(false);
}	

void particle::crete(ID3D11PixelShader* pixelshader, ID3D11VertexShader* vertexshader, ID3D11InputLayout* vertexlayout)
{
	m_SL.PixelShader = pixelshader;
	m_SL.VertexLayout = vertexlayout;
	m_SL.VertexShader = vertexshader;

	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(100.0f, 0.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 100.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(100.0f, 100.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

