#pragma once
#include<math.h>
class JVector2
{
	float x;
	float y;

	JVector2 operator += (JVector2 p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}
	JVector2  operator * (float s)
	{
		JVector2 ret;
		ret.x = x * s;
		ret.y = y * s;
		return ret;
	}
	JVector2 operator / (float fValue)
	{
		JVector2 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		return ret;
	}
	JVector2 operator + (JVector2 p)
	{
		JVector2 ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		return ret;
	}
	JVector2 operator - (JVector2 p)
	{
		JVector2 ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		return ret;
	}


	float   operator | (JVector2 p);
	float   DotProduct(JVector2 a, JVector2 b);
	float   ProjectionPoint(JVector2 q1, JVector2 q2, JVector2 v);
	JVector2 Normalize();
	float    Length();
public:
	JVector2() {}
	JVector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

class JVector3
{
public:
	float x;
	float y;
	float z;
	JVector3  operator += (JVector3 p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	JVector3  operator * (float s)
	{
		JVector3 ret;
		ret.x = x * s;
		ret.y = y * s;
		ret.z = z * s;
		return ret;
	}
	JVector3  operator + (JVector3 p)
	{
		JVector3 ret;
		ret.x = x + p.x;
		ret.y = y + p.y;
		ret.z = z + p.z;
		return ret;
	}
	JVector3  operator - (JVector3 p)
	{
		JVector3 ret;
		ret.x = x - p.x;
		ret.y = y - p.y;
		ret.z = z - p.z;
		return ret;
	}
	JVector3  operator / (float fValue)
	{
		JVector3 ret;
		ret.x = x / fValue;
		ret.y = y / fValue;
		ret.z = z / fValue;
		return ret;
	}
public:
	JVector3() {}
	JVector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class JVector4
{
public:
	float x;
	float y;
	float z;
	float w;
	JVector4() {}
	JVector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};