#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H
#include <SDL2/SDL_render.h>

namespace pong {
	struct TextureData {
		TextureData(SDL_Texture* texture, int width, int height);
		~TextureData();

		SDL_Texture* texture;

		int width;
		int height;
	};
}


#endif // TEXTURE_DATA_H
