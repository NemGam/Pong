#include "window.h"
#include <string>

#include "logger.h"


namespace pong {

	Window::Window(std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window, 
		std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer, int width, int height)
		: sdl_window_(std::move(sdl_window)),
		sdl_renderer_(std::move(sdl_renderer)),
		window_height_(height), window_width_(width)
	{
		
	}


	std::unique_ptr<Window> Window::Create(int width, int height, const std::string& title, Uint32 flags) {

		auto window = 
			std::unique_ptr<SDL_Window, SdlWindowDestructor>(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags));

		if (window == nullptr) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}

		auto renderer = 
			std::unique_ptr<SDL_Renderer, SdlRendererDestructor>(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

		if (renderer == nullptr) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}


		SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
		SDL_RenderClear(renderer.get());
		SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

		return std::unique_ptr<Window>(new Window(std::move(window), std::move(renderer), width, height));
	}


	int Window::GetHeight() const {
		return window_height_;
	}

	int Window::GetWidth() const {
		return window_width_;
	}

	const SDL_Renderer* Window::GetRenderer() const {
		return sdl_renderer_.get();
	}
}
