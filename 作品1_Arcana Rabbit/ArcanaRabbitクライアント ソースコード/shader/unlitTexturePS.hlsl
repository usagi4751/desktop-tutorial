
#include "common.hlsl"


Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	if (Material.TextureEnable)
	{
		
       // float4 coler0 = g_Texture.Sample(g_SamplerState, In.TexCoord);
       // float4 coler1 = g_Texture.Sample(g_SamplerState, In.TexCoord + float2(0.0, -1.0 / 600));
       // float4 coler2 = g_Texture.Sample(g_SamplerState, In.TexCoord + float2(1.0 / 600.0,0.0));
       // float4 coler3 = g_Texture.Sample(g_SamplerState, In.TexCoord + float2(-1.0 / 600.0,0.0));;
       // float4 coler4 = g_Texture.Sample(g_SamplerState, In.TexCoord + float2(1.0 / 600.0, 0.0));;
		
       // outDiffuse.rgb = (coler1.rgb + coler2.rgb + coler3.rgb + coler4.rgb) - coler1.rgb * 4.0f;
       // outDiffuse.a = 1.0f;
		
		outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
		outDiffuse *= In.Diffuse;
	}
	else
	{
		outDiffuse = In.Diffuse;
	}


}
