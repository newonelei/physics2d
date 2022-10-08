// physics2d.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "math_utils/matrices_utils.h"
using namespace math_utils;

int main()
{
    std::cout << "Hello World!\n";

	math::Matrix2D mat2d(1.2f, 2.2f, 3.2f, 4.2f);
	Matrix2D minor_2d = Minor(mat2d);
	cout << ToString<Matrix2D, 2, 2>(minor_2d);
	operator<<<Matrix2D, 2, 2>(cout, minor_2d);
	//std::cout << minor_2d << endl;

	math::Matrix3D mat3d(1.2f, 2.2f, 3.2f, 4.2f, 1.2f, 2.2f, 3.2f, 4.2f, 5.2f);
	//std::cout << Minor(mat3d) << endl;
	operator<<<Matrix3D, 3, 3>(cout, Minor(mat3d));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
