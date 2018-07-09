#include"Vextex.h"

Vertex Vertex::operator+(const Vertex& v1) const
{

	Vertex v2;
	v2.color.r = color.r + v1.color.r;
	v2.color.g = color.g + v1.color.g;
	v2.color.b = color.b + v1.color.b;

	v2.pos._x = pos.GetX() + v1.pos.GetX();
	v2.pos._y = pos.GetY() + v1.pos.GetY();
	v2.pos._z = pos.GetZ() + v1.pos.GetZ();
	v2.pos._w = pos.GetW() + v1.pos.GetW();

	v2.tc.u = tc.u + v1.tc.u;
	v2.tc.v = tc.v + v1.tc.v;
	v2.rhw = rhw + v1.rhw;

	return v2;
}

// y = (v2 - v1) / w
void Vertex::Division(const Vertex& v1, const Vertex& v2, float w)
{

	color.r = (v1.color.r - v2.color.r) / w;
	color.g = (v1.color.g - v2.color.g) / w;
	color.b = (v1.color.b - v2.color.b) / w;

	tc.u = (v1.tc.u - v2.tc.u) / w;
	tc.v = (v1.tc.v - v2.tc.v) / w;
	
	pos._x = (v1.pos.GetX() - v2.pos.GetX()) / w;
	pos._y = (v1.pos.GetY() - v2.pos.GetY()) / w;
	pos._z = (v1.pos.GetZ() - v2.pos.GetZ()) / w;
	pos._w = (v1.pos.GetZ() - v2.pos.GetZ()) / w;

	rhw = (v1.rhw - v2.rhw) / w;
	
}

void Vertex::Interp(const Vertex& v1, const Vertex& v2, float t)
{
	pos = Vec<float>::LinearInterp(v1.pos, v2.pos, t);
	auto LinearInterp = [](float x1, float x2, float t){return x1 + (x2 - x1) * t; };
	color.r = LinearInterp(v1.color.r, v2.color.r, t);
	color.g = LinearInterp(v1.color.g, v2.color.g, t);
	color.b = LinearInterp(v1.color.b, v2.color.b, t);

	tc.u = LinearInterp(v1.tc.u, v2.tc.u, t);
	tc.v = LinearInterp(v1.tc.v, v2.tc.v, t);

	rhw = LinearInterp(v1.rhw, v2.rhw, t);
}

// 'color/w' and 'tc/w'
void Vertex::Init()
{
	float val = 1 / pos.GetW();
	rhw = val;
	color.r = color.r * val;
	color.g = color.g * val;
	color.b = color.b * val;

	tc.u = tc.u * val;
	tc.v = tc.v * val;
}

void Vertex::Swap(Vertex& v2)
{
	Vertex temp = v2;
	v2 = *this;
	*this = temp;
}