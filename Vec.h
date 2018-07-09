#include<iostream>
#include"Mat.h"
#ifndef VEC_H
#define VEC_H

template<typename T>
class Vec
{
public:
	Vec():_x(0),_y(0),_z(0),_w(1){}
	Vec(const T x, const T y, const T z, const T w = 1) :_x(x), _y(y), _z(z), _w(w){}
	inline Vec(const Vec & rhs)
	{
		if (&rhs != this)
		{
			_x = rhs._x;
			_y = rhs._y;
			_z = rhs._z;
			_w = rhs._w;
		}
	}

	inline Vec& operator=(const Vec & rhs)
	{
		if (&rhs != this)
		{
			_x = rhs._x;
			_y = rhs._y;
			_z = rhs._z;
		}
		return *this;
	}
	~Vec(){}

	Vec operator+(const Vec & rhs) const;
	Vec operator-(const Vec & rhs) const;
	Vec operator*(const Vec & rhs) const;
	T DotMultiply(const Vec & rhs) const;
	inline T GetX() const{ return _x; }
	inline T GetY() const{ return _y; }
	inline T GetZ() const{ return _z; }
	inline T GetW() const{ return _w; }
	void Normalize();
	float length() const;
	static Vec LinearInterp(const Vec & x1, const Vec & x2, const float & t) ;
	friend std::ostream& operator<<(std::ostream& out, const Vec<T> & rhs)
	{
		out << "vec = " << "( " << rhs._x << ","
		<< rhs._y << ","
		<< rhs._z << ","
		<< rhs._w << ")" << std::endl;
		return out;
	}
protected:
	friend class Mat;
	friend class Vertex;
private:
	T _x, _y, _z, _w;
};

//template<typename T>
//std::ostream& operator<<(std::ostream& out, const Vec<T> & rhs){
//	out << "vec = " << "( " << rhs._x << ","
//		<< rhs._y << ","
//		<< rhs._z << ","
//		<< rhs._w << "," << ")" << std::endl;
//	return out;
//}

// a - b
template<typename T>
Vec<T> Vec<T>::operator+(const Vec & rhs) const
{
	Vec<T> vec;
	vec._x = rhs._x + _x;
	vec._y = rhs._y + _y;
	vec._z = rhs._z + _z;
	vec._w = 1;
	return vec;
}

// a + b
template<typename T>
Vec<T> Vec<T>::operator-(const Vec & rhs) const
{
	Vec<T> vec;
	vec._x = _x - rhs._x;
	vec._y = _y - rhs._y;
	vec._z = _z - rhs._z;
	vec._w = 1;
	return vec;
}

// a X b = | i   j   k  |		
//         | Ax  Ay  Az |
//         | Bx  By  Bz |
template<typename T>
Vec<T> Vec<T>::operator*(const Vec & rhs) const
{
	Vec<T> vec;
	vec._x = _y * rhs._z - _z * rhs._y;
	vec._y = _x * rhs._z - _z * rhs._x;
	vec._z = _x * rhs._y - _y * rhs._x;
	vec._w = 1;
	return vec;
}

// a . b = (Ax*Bx + Ay*By + Az*By)
template<typename T>
T Vec<T>::DotMultiply(const Vec & rhs) const
{
	return _x * rhs._x + _y * rhs._y + _z * rhs._z;
}


template<typename T>
void Vec<T>::Normalize()
{
	float nearToZero = 0.00000001f;
	const float len = length();
	if (len > (-nearToZero) && len < nearToZero)
	{
		return;
	}
	_x = static_cast<T>((float)_x / len);
	_y = static_cast<T>((float)_y / len);
	_z = static_cast<T>((float)_z / len);
}

template<typename T>
float Vec<T>::length() const
{
	return (float)std::sqrtf(float(_x * _x + _y * _y + _z * _z));
}

// c = a + (b - a) * t (t = bc/ac)
template<typename T>
Vec<T> Vec<T>::LinearInterp(const Vec & x1, const Vec & x2, const float & t)
{
	Vec<T> vec;
	auto InterpFun = [](float x1, float x2, float t){return x1 + (x2 - x1) * t; };
	vec._x = InterpFun(x1._x, x2._x, t);
	vec._y = InterpFun(x1._y, x2._y, t);
	vec._z = InterpFun(x1._z, x2._z, t);
	vec._w = 1;
	return vec;
}

#endif