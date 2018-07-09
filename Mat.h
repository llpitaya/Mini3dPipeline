#ifndef MAT_H
#define MAT_H
#include"Vec.h"

class Mat
{
public:
	Mat(){}
	Mat(const float x[]);
	Mat operator+(const Mat& rhs) const;
	Mat operator-(const Mat& rhs) const;
	Mat operator*(const Mat& rhs) const;
	void Scale(float f) ;
	void Scale(float x, float y, float z) ;
	void Translate(float x, float y ,float z) ;
	void Rotate(const Vec<float>& vec, float theta) ;
	Vec<float> Apply(const Vec<float>& vec);
	void ToIdentityMat();
	void ToZeroMat();
	Mat SetLookAt(const Vec<float>& eye, const Vec<float>& at, const Vec<float>& up) const;
	Mat SetPerspetive(float fovy, float aspect, float zn, float zf) const;
private:
	float m[4][4];
	static const size_t row = 4;
	static const size_t col = 4;
};
#endif