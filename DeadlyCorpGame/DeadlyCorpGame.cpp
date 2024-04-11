// DeadlyCorpGame.cpp : Defines the entry point for the application.
//

#include "DeadlyCorpGame.h"

using namespace std;

int main()
{
	//set the logger to on/off
	Logger::setActive(true);
	
	Logger::logDebug("hello world!");
	Game game = Game();
	game.newGame();
	Logger::logDebug("bye world!");
	return 0;
}
