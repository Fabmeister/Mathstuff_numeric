/* This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <iostream>
#include <functional>
#include <mpreal.h>
#include <eigen3/Eigen/Dense>

using mpfr::mpreal;
using Eigen::Vector2d;
using Eigen::Matrix2d;

mpreal one_newton_iteration(mpreal x, std::function<mpreal(mpreal&)> f, std::function<mpreal(mpreal&)>  fd)
{
	return x - (f(x) / fd(x));
}

Vector2d newton_2dim(Vector2d v, std::function<Vector2d(Vector2d)> f, std::function<Matrix2d(Vector2d)> derivate)
{
	return v - ( derivate(v).inverse() * f(v));
}

mpreal my_func(mpreal& x)
{
	return (x * x * x) - 1;
}

mpreal my_func_derivative(mpreal& x)
{
	return 3*(x * x);
}

Vector2d f2(Vector2d v)
{
	double x = v[0];
	double y = v[1];
	v[0] = x*x*x + y - 1;
	v[1] = y*y*y - x + 1;
	return v;
}

Matrix2d f2Derivat(Vector2d v)
{
	double x = v[0];
	double y = v[1];
	Matrix2d A = Matrix2d::Constant(0);
	A(0, 0) = 3 * x * x;
	A(0, 1) = 1;
	A(1, 0) = -1;
	A(1, 1) = 3 * y * y;
	return A;
}

int main()
{
	std::cout << "Aufgabe 1: \n" << "---------------------------------------" << std::endl;
	mpreal x = 8;
	for(int i = 1; i <= 8; i++)
	{
		x = one_newton_iteration(x, my_func, my_func_derivative);
		std::cout << "Newton iteration(" << i << "): " << x << std::endl;
	}

	std::cout << "Aufgabe 2: \n" << "---------------------------------------" << std::endl;
	Vector2d v;
	v[0] = 0.5;
	v[1] = 0.5;
	for(int i = 1; i <= 7; i++)
	{
		v = newton_2dim(v, f2, f2Derivat);
		std::cout << "Newton iteration(" << i << "), f(v) = \n" << f2(v) << "\n mit v = \n" << v << std::endl;
	}
	return 0;
}
