#include "texture_data.h"

namespace pong {
	TextureData::TextureData(SDL_Texture* texture, int width, int height) :
		texture(texture),
		width(width),
		height(height)
	{}

	TextureData::~TextureData() {
		if (texture != nullptr)
			SDL_DestroyTexture(texture);
	}
}



