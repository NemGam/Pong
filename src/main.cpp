#include "asset_database.h"
#include "game.h"
#include "window.h"
#include "global_consts.h"
#include "logger.h"
#include "SDL2/SDL_image.h"

//Do not delete parameters as SDL requires them.
int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	{
		auto window = std::unique_ptr<pong::Window>(pong::Window::Create(pong::kWindowWidth, pong::kWindowHeight, "PONG", SDL_WINDOW_SHOWN));
		pong::AssetDatabase database(window->GetRenderer());

		pong::Game game(*window, database);

		game.Run();
	}

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}
