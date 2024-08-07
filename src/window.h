#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <memory>
#include "unique_ptrs_destructors.h"

namespace pong {

	class Window
	{
	public:
		static std::unique_ptr<Window> Create(int width, int height, const std::string& title, Uint32 flags);

		
		const SDL_Renderer* GetRenderer() const;
		int GetHeight() const;
		int GetWidth() const;

	private:
		Window(std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window,
			std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer, int width, int height);


		std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window_;
		std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer_;
		int window_height_;
		int window_width_;
	};
}
#endif