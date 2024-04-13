#include "AbstractMoon.h"
#include "Game.h"

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

void AbstractMoon::displayWeather()
{
	
	switch (_weather)
	{
	
	case MoonWeather::FLOODED:
		std::cout << "Proceed with caution as the moon is currently flooded\n\n";
		break;
	case MoonWeather::STORMY:
		std::cout << "Proceed with caution as the moon is currently stormy\n\n";
		break;
	case MoonWeather::ECLIPSED:
		std::cout << "Proceed with caution as the moon is currently eclipsed\n\n";
		break;
	default:
		std::cout << std::endl;
		break;
	}
}