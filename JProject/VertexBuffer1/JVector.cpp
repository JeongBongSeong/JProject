#include "JVector.h"


float   JVector2::operator | (JVector2 p)
{
	return x * p.x + y * p.y;
}
float   JVector2::DotProduct(JVector2 a, JVector2 b)
{
	return a.x * b.x + a.y * b.y;
}
float   JVector2::ProjectionPoint(JVector2 q1, JVector2 q2, JVector2 v)
{
	JVector2 a = q2 - q1;
	JVector2 b = v - q1;
	JVector2 p = a * ((b | a) / (a | a));
	JVector2 w = b - p;
	return w.Length();

}
JVector2 JVector2::Normalize()
{
	JVector2 d;
	float length = 1.0f / Length();
	d.x = d.x * length;
	d.y = d.y * length;
	return d;

}
float    JVector2::Length()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}

