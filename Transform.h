#ifndef TRANSFORM_H
#define TRANSFORM_H
#include"Mat.h"
#include"Vec.h"

class Transform
{
public:
	Transform(float w, float h);
	Mat GetTransformMat();
	Vec<float> Apply(const Vec<float>& x);
	Vec<float> ToScreenPos(const Vec<float> & x);
private:
	void Init();
	Mat world;
	Mat view;
	Mat projection;
	float width, height, aspect;
};
#endif