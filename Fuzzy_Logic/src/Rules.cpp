#include "Rules.h"

int Rules::Defuzzify(double t_enemySize, double t_enemyDistance)
{
	rulesMatrix.sizeTiny = Fuzzy::Triangle(t_enemySize, -10, 0, 10);
	rulesMatrix.sizeSmall = Fuzzy::Trapezoid(t_enemySize, 2.5, 10, 15, 20);
	rulesMatrix.sizeModerate = Fuzzy::Trapezoid(t_enemySize, 15, 20, 25, 30);
	rulesMatrix.sizeLarge = Fuzzy::Grade(t_enemySize, 25, 30);

	rulesMatrix.distanceClose = Fuzzy::Triangle(t_enemyDistance, -30, 0, 30);
	rulesMatrix.distanceMedium = Fuzzy::Trapezoid(t_enemyDistance, 10, 30, 50, 70);
	rulesMatrix.distanceFar = Fuzzy::Grade(t_enemyDistance, 50, 70);

	rulesMatrix.lowThreat = Fuzzy::OR(
		Fuzzy::OR(Fuzzy::AND(rulesMatrix.distanceMedium, rulesMatrix.sizeTiny),
			Fuzzy::AND(rulesMatrix.distanceMedium, rulesMatrix.sizeSmall)),
		Fuzzy::AND(rulesMatrix.distanceFar, Fuzzy::NOT(rulesMatrix.sizeLarge)));

	rulesMatrix.mediumThreat = Fuzzy::OR(
		Fuzzy::OR(Fuzzy::AND(rulesMatrix.distanceClose, rulesMatrix.sizeTiny),
			Fuzzy::AND(rulesMatrix.distanceMedium, rulesMatrix.sizeModerate)),
		Fuzzy::AND(rulesMatrix.distanceFar, rulesMatrix.sizeLarge));

	rulesMatrix.highThreat = Fuzzy::OR(
		Fuzzy::AND(rulesMatrix.distanceClose, Fuzzy::NOT(rulesMatrix.sizeTiny)),
		Fuzzy::AND(rulesMatrix.distanceMedium, rulesMatrix.sizeLarge));

	std::cout << rulesMatrix.lowThreat << std::endl;
	std::cout << rulesMatrix.mediumThreat << std::endl;
	std::cout << rulesMatrix.highThreat << std::endl;
	
	return  std::ceil((rulesMatrix.lowThreat * 10.0 + rulesMatrix.mediumThreat * 30.0 + rulesMatrix.highThreat * 50.0) /
		(rulesMatrix.lowThreat + rulesMatrix.mediumThreat + rulesMatrix.highThreat));
}
