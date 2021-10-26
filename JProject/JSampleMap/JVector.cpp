#include "JVector.h"



JVector3::JVector3()
{
	x = y = z = 0.0f;
}

JVector3::JVector3(const JVector3& v0)
{
	x = v0.x;
	y = v0.y;
	z = v0.z;
}

JVector3::JVector3(float fX, float fY, float fZ)
{
	x = fX;
	y = fY;
	z = fZ;
}

// 연산자 재정의 
JVector3 JVector3::operator + (JVector3 const& v0)
{
	return JVector3(v0.x + x, v0.y + y, v0.z + z);
}

JVector3 JVector3::operator - (JVector3 const& v0)
{
	return JVector3(x - v0.x, y - v0.y, z - v0.z);
}

JVector3 JVector3::operator + (float const& fScala)
{
	return JVector3(fScala + x, fScala + y, fScala + z);
}
JVector3 JVector3::operator * (float const& fScala)
{
	return JVector3(fScala * x, fScala * y, fScala * z);
}
JVector3 JVector3::operator / (float const& fScala)
{
	float fInvert = 1.0f / fScala;
	return JVector3(x * fInvert, y * fInvert, z * fInvert);
}

// Dot Product
float JVector3::operator | (JVector3 const& v0)
{
	return x * v0.x + y * v0.y + z * v0.z;
}

// Cross Product
JVector3 JVector3::operator ^ (JVector3 const& v0)
{
	return JVector3((y * v0.z - z * v0.y), (z * v0.x - x * v0.z), (x * v0.y - y * v0.x));
}

bool	JVector3::operator == (JVector3 const& v0)
{
	if (fabs(x - v0.x) < JBASIS_EPSILON)
	{
		if (fabs(y - v0.y) < JBASIS_EPSILON)
		{
			if (fabs(z - v0.z) < JBASIS_EPSILON)
			{
				return true;
			}
		}
	}
	return false;
}

// 제곱
float JVector3::LengthSquared()
{
	return (x * x + y * y + z * z);
}

// 원점으로 부터의 거리
float JVector3::Length()
{
	return (float)sqrt(LengthSquared());
}

JVector3 JVector3::Normal()
{
	float invertLength = 1.0f / Length();
	return JVector3(x * invertLength, y * invertLength, z * invertLength);
}

float JVector3::Angle(JVector3& v0)
{
	float fLength1 = Length();
	float fLength2 = v0.Length();
	float fCosAngle = ((*this) | v0) / (fLength1 * fLength2);
	return (float)RadianToDegree(acos(fCosAngle));
}


JVector4::JVector4()
{
	x = y = z = w = 0.0f;
}

JVector4::JVector4(const JVector4& v0)
{
	x = v0.x;
	y = v0.y;
	z = v0.z;
	w = v0.w;
}

JVector4::JVector4(float fX, float fY, float fZ, float fW)
{
	x = fX;
	y = fY;
	z = fZ;
	w = fW;
}


JVector2::JVector2()
{
	x = y = 0.0f;
}

JVector2::JVector2(const JVector2& v0)
{
	x = v0.x;
	y = v0.y;
}

JVector2::JVector2(float fX, float fY)
{
	x = fX;
	y = fY;
}