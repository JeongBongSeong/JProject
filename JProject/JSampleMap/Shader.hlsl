struct VS_OUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
};


cbuffer cbData
{
	matrix g_matWorld	:	packoffset(c0);
	matrix g_matView	:	packoffset(c4);
	matrix g_matProj	:	packoffset(c8);
};


VS_OUT VS(float3 p : POSITION, float4 c : COLOR)
{
	VS_OUT ouput = (VS_OUT)0;
	float4 vLocal = float4(p, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
}


float4 PS(VS_OUT v) : SV_TARGET
{
	return v.c;
}