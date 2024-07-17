#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL_render.h>
#include <string>
#include <memory>
#include <SDL2/SDL_ttf.h>

#include "texture_data.h"

namespace pong {


	class Texture
	{
	public:
		explicit Texture(const SDL_Renderer* renderer);
		Texture(const Texture&) = default;
		Texture(Texture&&) = default;
		Texture& operator=(const Texture&) = default;
		Texture& operator=(Texture&&) = default;

		~Texture() = default;

		void Render(int x, int y, double angle = 0) const;
		void Render(int x, int y, int w, int h, double angle = 0) const;

		//Loads and creates texture from the given file.
		bool CreateFromFile(const std::string& path);
		//Creates texture from the given string.
		bool CreateFromText(const std::string& text, TTF_Font* font, SDL_Color color);

		int GetWidth() const;
		int GetHeight() const;

	private:
		//Clear texture and assign a new one
		void Clear();

		const SDL_Renderer* renderer_;
		std::shared_ptr<TextureData> data_;
	};
}
#endif // TEXTURE_H
