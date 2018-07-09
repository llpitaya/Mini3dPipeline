#include"Transform.h"
Transform::Transform(float w, float h)
{
	width = w;
	height = h;
	aspect = w / h;
	Init();
}

void Transform::Init()
{
	world.ToIdentityMat();
	view.ToIdentityMat();
	projection.SetPerspetive(3.1415926f * 0.5, aspect, 1.0f, 100.0f);
}

Mat Transform::GetTransformMat()
{
	return world*view*projection;
}

// projection
// y = x * Transform 
Vec<float> Transform::Apply(const Vec<float>& x)
{
	Mat tranform = GetTransformMat();
	return tranform.Apply(x);
}

Vec<float> Transform::ToScreenPos(const Vec<float> & x)
{
	float rhw = 1.0f / x.GetW();
	float x_screen = (1 + x.GetX()) * width * rhw * 0.5f;
	float y_screen = (1 - x.GetY()) * height * rhw * 0.5f;
	float z_screen = x.GetZ() * rhw; // ????
	return Vec<float>(x_screen, y_screen, z_screen, 1.0f);
}