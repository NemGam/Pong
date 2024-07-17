#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "texture.h"

namespace pong {


	class Text {
	public:
		enum class TextAlignment { kLeft = 0, kMiddle = 1, kRight = 2 };


		Text(const SDL_Renderer* renderer, std::string text, const TTF_Font* font, int x_pos, int y_pos,
			TextAlignment alignment, SDL_Color color);
		Text(const Text&) = default;
		Text(Text&& t) = default;
		Text& operator=(const Text&) = default;
		Text&& operator=(Text&& t) = default;
		

		~Text() = default;


		void SetText(const std::string& text);
		void Render() const;


	private:

		//Regenerates text, must be called on any text change. Relatively expensive.
		void Regenerate();
		SDL_Rect GetAlignedRect(SDL_Rect rect, TextAlignment alignment) const; //Modifies provided rect to be of a given alignment

		int x_pos_;
		int y_pos_;
		std::string text_;
		SDL_Rect rect_;
		const TTF_Font* font_;
		SDL_Color color_;
		TextAlignment alignment_;
		Texture texture_;
	};
}
#endif
