#pragma once
#include <iostream>

namespace Fuzzy
{
	double Grade(double value, double t_x0, double t_x1);
	double Triangle(double value, double t_x0, double t_x1, double t_x2);
	double Trapezoid(double value, double t_x0, double t_x1, double t_x2, double t_x3);

	double AND(double t_a, double t_b);
	double OR(double t_a, double t_b);
	double NOT(double t_a);
};

