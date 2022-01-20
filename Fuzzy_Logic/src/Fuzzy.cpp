#include "Fuzzy.h"

double Fuzzy::Grade(double value, double t_x0, double t_x1)
{
	if (value <= t_x0)
		return 0.0;
	else if (value > t_x1)
		return 1.0;
	else
		return ((value - t_x0) / (t_x1 - t_x0));

}

double Fuzzy::Triangle(double value, double t_x0, double t_x1, double t_x2)
{
	if (value <= t_x1 || value >= t_x2)
		return 0.0;
	else if (value == t_x1)
		return 1.0;
	else if (value > t_x0 && value < t_x1)
		return ((value - t_x0) / (t_x1 - t_x0));
	else
		return ((t_x2 - value) / (t_x2 - t_x1));

}

double Fuzzy::Trapezoid(double value, double t_x0, double t_x1, double t_x2, double t_x3)
{
	if (value <= t_x0 || value >= t_x3)
		return 0.0;
	else if (value >= t_x1 && value <= t_x2)
		return 1.0;
	else if (value > t_x0 && value < t_x1)
		return ((value - t_x0) / (t_x1 - t_x0));
	else
		return ((t_x3 - value) / (t_x3 - t_x2));
}

double Fuzzy::AND(double t_a, double t_b)
{
	return std::min(t_a, t_b);
}

double Fuzzy::OR(double t_a, double t_b)
{
	return std::max(t_a, t_b);
}

double Fuzzy::NOT(double t_a)
{
	return 1.0 - t_a;
}
