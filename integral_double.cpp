/* This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <iostream>
#include <functional>
#include <cmath>

double integration_rechtecke(std::function<double(double)> f, double a, double b, int n)
{
	double area = 0;
	double mu = (b - a) / n;
	double x = a;

	for(int i = 0; i < n; i++)
	{
		double xi = x + mu/2.0;
		area += f(xi) * mu;
		x += mu;
	}
	return area;
}

double integration_trapez(std::function<double(double)> f, double a, double b, int n)
{
	double area = 0;
	double h = (b - a) / n;
	double x = a;

	for(int i = 0; i < n; i++)
	{
		double x_next = x + h;
		double trapez = (f(x) + f(x_next)) / 2;
		area += trapez * h;
		x = x_next;
	}
	return area;
}

double my_func(double x)
{
	return x * log(x);
}

int main()
{
	std::cout << "Rechtecke: " << integration_rechtecke(my_func, 1, 2, 5) << std::endl;
	std::cout << "Trapeze: " << integration_trapez(my_func, 1, 2, 5) << std::endl;
	return 1;
}
