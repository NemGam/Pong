#include "Game.h"

//Do not delete parameters as SDL requires them.
int main(int argc, char* args[])
{
	auto game = pong::Game();

	game.run();

	return 0;
}
