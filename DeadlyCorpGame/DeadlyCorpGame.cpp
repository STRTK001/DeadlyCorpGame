// DeadlyCorpGame.cpp : Defines the entry point for the application.
//

///
/// Author: Travis Strawbridge
/// Email: strtk001@mymail.unisa.edu.au
/// student id: 110340713
///

#include "DeadlyCorpGame.h"

using namespace std;

int main()
{
	//set the logger to on/off
	Logger::setActive(false);
	
	Logger::logDebug("hello world!");
	Game game = Game();
	game.play();
	Logger::logDebug("bye world!");
	return 0;
}
