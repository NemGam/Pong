#include "texture.h"
#include "unique_ptrs_destructors.h"
#include <SDL2/SDL_image.h>

#include "logger.h"

namespace pong {

	Texture::Texture(const SDL_Renderer* renderer) : renderer_(renderer)
	{
		Clear();
	}

	void Texture::Clear() {
		data_ = std::make_shared<TextureData>(nullptr, 0, 0);
	}

	void Texture::Render(int x, int y, double angle) const {
		Render(x, y, data_->width, data_->height, angle);
	}

	void Texture::Render(int x, int y, int w, int h, double angle) const {

		SDL_Rect render_rect = { x, y, w, h };

		SDL_RenderCopyEx(const_cast<SDL_Renderer*>(renderer_), data_->texture, nullptr, &render_rect, angle, nullptr, SDL_FLIP_NONE);
	}

	bool Texture::LoadFromFile(const std::string& path) {
		Clear();

		SDL_Texture* tex = nullptr;

		auto surf = std::unique_ptr<SDL_Surface, SdlSurfaceDestructor>(IMG_Load(path.c_str()));

		if (surf == nullptr) {
			return false;
		}

		SDL_SetColorKey(surf.get(), SDL_TRUE, SDL_MapRGB(surf->format, 0, 255, 255));

		tex = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(renderer_), surf.get());

		if (tex == nullptr) {
			logger::LogError(SDL_GetError());
			return false;
		}

		data_->width = surf->w;
		data_->height = surf->h;

		data_->texture = tex;
		return true;
	}

	int Texture::GetWidth() const {
		return data_->width;
	}

	int Texture::GetHeight() const {
		return data_->height;
	}
}


