#include "Text.h"
#include "Window.h"

namespace pong {
	Text::Text(TTF_Font* font, int xpos, int ypos, const std::string& text, const int alignment, SDL_Color color)
		: rect{0, 0, 0, 0}, font(font), color(color), alignment(alignment)
	{
		SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
		if (!surface) {
			std::cerr << "Failed to create a text: " << TTF_GetError() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to create a text!", TTF_GetError(), nullptr);
			return;
		}
		this->text_texture = SDL_CreateTextureFromSurface(Window::get_renderer(), surface);
		if (!this->text_texture){
			std::cerr << "Failed to create a texture: " << TTF_GetError() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to create a texture!", TTF_GetError(), nullptr);
			SDL_FreeSurface(surface);
			return;
		}

		TTF_SizeUTF8(font, text.c_str(), &rect.w, &rect.h);
		this->rect = {xpos - rect.w * alignment, ypos, rect.w, rect.h};
		SDL_FreeSurface(surface);
	}

	Text::~Text() {
		SDL_DestroyTexture(this->text_texture);
	}

	void Text::set_text(const std::string& text) {
		if (text.empty()) {
			std::cerr << "Text cannot be an empty string!" << std::endl;
			return;
		}
		recreate(text);
	}

	void Text::set_text(const int text) {
		recreate(std::to_string(text));
	}

	void Text::recreate(const std::string& text) {
		SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
		if (!surface) {
			std::cerr << "Failed to create a surface: " << TTF_GetError() << std::endl;
			SDL_FreeSurface(surface);	
			return;
		}
		SDL_DestroyTexture(text_texture);
		text_texture = SDL_CreateTextureFromSurface(Window::get_renderer(), surface);
		if (!text_texture) {
			std::cerr << "Failed to create a texture: " << TTF_GetError() << std::endl;
			return;
		}
		const int prev_w = rect.w;
		TTF_SizeUTF8(font, text.c_str(), &rect.w, &rect.h);
		rect = { (int)(rect.x + (prev_w - rect.w) * alignment), rect.y, rect.w, rect.h};
		SDL_FreeSurface(surface);
	}

	void Text::render() const {
		SDL_RenderCopy(Window::get_renderer(), text_texture, nullptr, &rect);
	}
}
