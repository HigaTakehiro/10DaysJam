#include "Particle.hlsli"

//[maxvertexcount(3)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION, 
//	inout TriangleStream< GSOutput > output
//)
//{
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos;
//		element.normal = input[i].normal;
//		element.uv = input[i].uv;
//
//		output.Append(element);
//	}
//}
//[maxvertexcount(1)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout PointStream< GSOutput > output
//)
//{
//		GSOutput element;
//		element.svpos = input[0].svpos;
//		element.normal = input[0].normal;
//		element.uv = input[0].uv;
//
//		output.Append(element);
//}

//[maxvertexcount(3)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout PointStream< GSOutput > output
//)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos;
//		element.normal = input[i].normal;
//		element.uv = input[i].uv;
//
//		output.Append(element);
//	}
//}

//[maxvertexcount(2)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout LineStream< GSOutput > output
//)
//{
//	GSOutput element;
//	element.svpos = input[0].svpos;
//	element.normal = input[0].normal;
//	element.uv = input[0].uv;
//
//	output.Append(element);
//	element.svpos = input[1].svpos;
//	element.normal = input[1].normal;
//	element.uv = input[1].uv;
//
//	output.Append(element);
//}

//[maxvertexcount(6)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout LineStream< GSOutput > output
//)
//{
//	GSOutput element;
//	for (int i = 0; i < 3; i++)
//	{
//
//		element.svpos = input[i].svpos;
//		element.normal = input[i].normal;
//		element.uv = input[i].uv;
//
//		output.Append(element);
//		if (i == 2)
//		{
//			element.svpos = input[0].svpos;
//			element.normal = input[0].normal;
//			element.uv = input[0].uv;
//			
//		}
//		else
//		{
//			element.svpos = input[i+1].svpos;
//			element.normal = input[i+1].normal;
//			element.uv = input[i+1].uv;
//		}
//		output.RestartStrip();
//	}
//
//}

//[maxvertexcount(6)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout LineStream< GSOutput > output
//)
//{
//	GSOutput element;
//	for (uint i = 0; i < 3; i++)
//	{
//
//		element.svpos = input[i].svpos;
//		element.normal = input[i].normal;
//		element.uv = input[i].uv;
//
//		output.Append(element);
//		if (i == 2)
//		{
//			element.svpos = input[0].svpos;
//			element.normal = input[0].normal;
//			element.uv = input[0].uv;
//
//		}
//		else
//		{
//			element.svpos = input[i + 1].svpos;
//			element.normal = input[i + 1].normal;
//			element.uv = input[i + 1].uv;
//		}
//		output.RestartStrip();
//	}
//
//}
//[maxvertexcount(4)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout LineStream< GSOutput > output
//)
//{
//	GSOutput element;
//	for (uint i = 0; i < 3; i++)
//	{
//
//		element.svpos = input[i].svpos;
//		element.normal = input[i].normal;
//		element.uv = input[i].uv;
//
//		output.Append(element);
//		
//	}
//	element.svpos = input[0].svpos;
//	element.normal = input[0].normal;
//	element.uv = input[0].uv;
//
//	output.Append(element);
//
//}

//[maxvertexcount(3)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout TriangleStream< GSOutput > output
//)
//{
//	
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos;
//		element.normal = input[i].normal;
//		element.uv = input[i].uv*2.0f;
//
//
//		output.Append(element);
//		
//	}
//	
//
//}

//[maxvertexcount(6)]
//void main(
//	triangle VSOutput input[3] : SV_POSITION,
//	inout TriangleStream< GSOutput > output
//)
//{
//
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos;
//		element.normal = input[i].normal;
//		element.uv = input[i].uv;
//
//
//		output.Append(element);
//
//	}
//
//	output.RestartStrip();
//
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos + float4(20.0f,0.0f,0.0f,0.0f);
//		element.normal = input[i].normal;
//		element.uv = input[i].uv*5.0f;
//
//
//		output.Append(element);
//
//	}
//
//
//}

//[maxvertexcount(3)]
//void main(
//	point VSOutput input[1] : SV_POSITION,
//	inout TriangleStream< GSOutput > output
//)
//{
//
//	GSOutput element;
//	element.normal = input[0].normal;
//	element.uv = input[0].uv;
//
//	element.svpos = input[0].svpos;
//	output.Append(element);
//	element.svpos = input[0].svpos + float4(10.0f,10.0f,0,0);
//	output.Append(element);
//	element.svpos = input[0].svpos + float4(10.0f, 0.0f, 0,0);
//
//
//	output.Append(element);
//	
//
//}

static const uint vnum = 4;

static const float2 uv_array[vnum] =
{
	float2(0,1),
	float2(0, 0),
	float2(1, 1),
	float2(1, 0)
};

static const float4 offset_array[vnum] =
{
	float4(-0.5f,-0.5f,0,0),
	float4(-0.5f,+0.5f,0,0),
	float4(+0.5f,-0.5f,0,0),
	float4(+0.5f,+0.5f,0,0)
	
};
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;
	for (int i = 0; i < vnum; i++)
	{
		//
		/*float4 offset = mul(matBillboard, offset_array[i]);*/
		float4 offset =offset_array[i] * input[0].scale;

		offset = mul(matBillboard, offset);
		//
		element.svpos = input[0].pos + offset;
		element.svpos = mul(mat,element.svpos);
		element.uv = uv_array[i];
		output.Append(element);
	}
}