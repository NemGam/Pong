#ifndef TEXT_H
#define TEXT_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

namespace pong {

	class Text {
	public:
		Text(TTF_Font* font, int xpos, int ypos, const std::string& = " ", int alignment = 0, SDL_Color color = {255, 255, 255, 255});

		~Text();
		
		/**
		 * @brief Set the text of this text object.
		 * @param text Text to set. Cannot be an empty string!
		*/
		void set_text(const std::string& text);
		
		/**
		 * @brief Set the text of this text object.
		 * @param text Integer to set as a text.
		*/
		void set_text(int text);

		void render() const;

	private:
		SDL_Rect rect;
		TTF_Font* font;
		SDL_Texture* text_texture;
		SDL_Color color;
		int alignment;

		void recreate(const std::string& text);
	};
}
#endif
