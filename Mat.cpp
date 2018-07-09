#include"Mat.h"

Mat::Mat(const float x[])
{

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			m[i][j] = x[i*row + j];
		}
	}
}

void Mat::Scale(float f)
{

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			m[i][j] = m[i][j] * f;
		}
	}
}

// Mat1 + Mat2
Mat Mat::operator+(const Mat& rhs) const
{
	Mat mat;
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			mat.m[i][j] = m[i][j] + rhs.m[i][j];
		}
	}
	return mat;
}

// Mat1 - Mat2
Mat Mat::operator-(const Mat& rhs) const
{
	Mat mat;
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			mat.m[i][j] = m[i][j] - rhs.m[i][j];
		}
	}
	return mat;
}

// Mat1 * Mat2
Mat Mat::operator*(const Mat& rhs) const
{
	Mat mat;
	mat.ToZeroMat();
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			for (size_t k = 0; k < row; k++)
			{
				mat.m[i][j] += m[i][k] * rhs.m[k][j];
			}			
		}
	}
	return mat;
}

void Mat::Scale(float x, float y, float z)
{
	ToIdentityMat();
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
}

void Mat::Translate(float x, float y, float z)
{
	ToIdentityMat();
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
}

// how to implement rotation with any axis
void Mat::Rotate(const Vec<float>& vec, float theta)
{

}

// y = x * Mat
Vec<float> Mat::Apply(const Vec<float>& x)
{
	Vec<float> y;
	y._x = m[0][0] * x._x + m[1][0] * x._y + m[2][0] * x._z + m[3][0] * x._w; // ?????
	y._y = m[0][1] * x._x + m[1][1] * x._y + m[2][1] * x._z + m[3][1] * x._w;
	y._z = m[0][2] * x._x + m[1][2] * x._y + m[2][2] * x._z + m[3][2] * x._w;
	y._w = m[0][3] * x._x + m[1][3] * x._y + m[2][3] * x._z + m[3][3] * x._w;
	return y;
}
	
void Mat::ToIdentityMat()
{

	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			m[i][j] = 0.0f;
		}
	}
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

void Mat::ToZeroMat()
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			m[i][j] = 0.0f;
		}
	}
}

// set the camera position
Mat Mat::SetLookAt(const Vec<float>& eye, const Vec<float>& at, const Vec<float>& up) const
{
	Vec<float> x_axis, y_axis, z_axis;
	z_axis = at - eye;
	z_axis.Normalize();

	x_axis = up * z_axis;
	x_axis.Normalize();
	
	y_axis = z_axis * x_axis;

	Mat mat;
	mat.ToIdentityMat();
	mat.m[0][0] = x_axis._x;
	mat.m[1][0] = x_axis._y;
	mat.m[2][0] = x_axis._z;
	mat.m[3][0] = -x_axis.DotMultiply(eye);

	mat.m[0][1] = y_axis._x;
	mat.m[1][1] = y_axis._y;
	mat.m[2][1] = y_axis._z;
	mat.m[3][1] = -y_axis.DotMultiply(eye);

	mat.m[0][2] = z_axis._x;
	mat.m[1][2] = z_axis._y;
	mat.m[2][2] = z_axis._z;
	mat.m[3][2] = -z_axis.DotMultiply(eye);

	return mat;
}

// D3DXMatrixPerspectiveFovLH
Mat Mat::SetPerspetive(float fovy, float aspect, float zn, float zf) const
{
	Mat mat;
	mat.ToZeroMat();
	float fax = 1.0f / std::tanf(0.5f * fovy);
	mat.m[0][0] = fax/aspect;
	mat.m[1][1] = fax;
	mat.m[2][2] = zf / (zf - zn);
	mat.m[3][2] = (zf*zn) / (zn - zf);
	mat.m[2][3] = 1;

	return mat;
}