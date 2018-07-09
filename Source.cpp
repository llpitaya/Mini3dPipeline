#include"Vec.h"
#include<iostream>

void test_Vec()
{
	Vec<float> vec(1, 2, 3,1);
	Vec<float> vec1(2, 0, 3, 1);
	std::cout << "vec: " << vec << std::endl;
	std::cout << "vec1: " << vec1 << std::endl;
	std::cout << (vec + vec1) << std::endl;
	std::cout << vec.DotMultiply(vec1) << std::endl;
	std::cout << (vec * vec1) << std:: endl;
	std::cout << vec.length() << std::endl;
	Vec<float> vec3 = Vec<float>::LinearInterp(vec, vec1, 0.2f);
	vec.Normalize();
	std::cout << vec;
}

int main()
{
	char c = 0xff;
	std::cout << (int)c << std::endl;
	
	unsigned int x[10];
	memset(x, 0x3f, 10);
	
	return 0;
}