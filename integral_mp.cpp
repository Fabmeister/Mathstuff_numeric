/* This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <iostream>
#include <functional>
#include <mpreal.h>

using mpfr::mpreal;

mpreal integration_rechtecke(std::function<mpreal(mpreal&)> f, mpreal a, mpreal b, int n)
{
	mpreal area = 0;
	mpreal mu = (b - a) / n;
	mpreal x = a;

	for(int i = 0; i < n; i++)
	{
		mpreal xi = x + mu/2.0;
		area += f(xi) * mu;
		x += mu;
	}
	return area;
}

mpreal integration_trapez(std::function<mpreal(mpreal&)> f, mpreal a, mpreal b, int n)
{
	mpreal area = 0;
	mpreal h = (b - a) / n;
	mpreal x = a;

	for(int i = 0; i < n; i++)
	{
		mpreal x_next = x + h;
		mpreal trapez = (f(x) + f(x_next)) / 2;
		area += trapez * h;
		x = x_next;
	}
	return area;
}

mpreal my_func(mpreal& x)
{
	return x * log(x);
}

mpreal func_4_pi(mpreal& x)
{
	return sqrt(1 - x*x);
}

int main()
{
	mpreal pi = 4 * integration_trapez(func_4_pi, 0, 1, 100);
	std::cout << "Pi: " << pi << std::endl;
	std::cout << "Rechtecke: " << integration_rechtecke(my_func, 1, 2, 5) << std::endl;
	std::cout << "Trapeze: " << integration_trapez(my_func, 1, 2, 5) << std::endl;

	std::cout << "Höheres n (Rechtecke): " << integration_rechtecke(my_func, 1, 2, 10000) << std::endl;
	std::cout << "Höheres n (Trapez): " << integration_trapez(my_func, 1, 2, 10000) << std::endl;
	return 0;
}
