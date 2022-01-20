#pragma once
#include "Fuzzy.h"

class Rules
{
public:

	struct RulesMatrix
	{
		double sizeTiny;
		double sizeSmall;
		double sizeModerate;
		double sizeLarge;
		double distanceClose;
		double distanceMedium;
		double distanceFar;
		double lowThreat;
		double mediumThreat;
		double highThreat;
	};

	RulesMatrix rulesMatrix;

	int Defuzzify(double t_enemySize, double t_enemyDistance);
};

