#pragma once
#include"JStd.h"
#include <math.h>

#define JBASIS_EPSILON		((FLOAT)  0.001f)
#define JBASIS_PI			((FLOAT)  3.141592654f)
#define DegreeToRadian( degree ) ((degree) * (JBASIS_PI / 180.0f))
#define RadianToDegree( radian ) ((radian) * (180.0f / JBASIS_PI))
#define MAKECOLOR_ARGB(a, r, g, b)			(((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)
#define IS_IN_RANGE(value,r0,r1) (( ((r0) <= (value)) && ((value) <= (r1)) ) ? 1 : 0)


namespace JBASIS_VECTOR {

	struct float2
	{
		union
		{
			struct { float x, y; };
			float v[2];
		};
	};

	struct float3
	{
		union
		{
			struct { float x, y, z; };
			float v[3];
		};
	};
	struct float4
	{
		union
		{
			struct { float x, y, z, w; };
			float v[4];
		};
	};
	class JVector3 : public float3
	{
	public:
		JVector3();
		JVector3(const JVector3& v0);
		JVector3(float fX, float fY, float fZ);
		// 연산자 재정의 
		JVector3 operator + (JVector3 const& v0);
		JVector3 operator - (JVector3 const& v0);
		JVector3 operator * (float const& fScala);
		JVector3 operator + (float const& fScala);
		JVector3 operator / (float const& fScala);
		// Dot Product
		float operator | (JVector3 const& v0);
		// Cross Product
		JVector3 operator ^ (JVector3 const& v0);
		bool	operator == (JVector3 const& v0);
		// 제곱
		float LengthSquared();
		// 원점으로 부터의 거리
		float Length();
		JVector3 Normal();
		float Angle(JVector3& v0);
	};
	class JVector4 : public float4
	{
	public:
		JVector4();
		JVector4(const JVector4& v0);
		JVector4(float fX, float fY, float fZ, float fW);
	};

	class JVector2 : public float2
	{
	public:
		JVector2();
		JVector2(const JVector2& v0);
		JVector2(float fX, float fY);
	};
}

using namespace JBASIS_VECTOR;