#ifndef MIDDLELINE_H
#define MIDDLELINE_H

#include <SDL2/SDL.h>

#include "global_consts.h"
#include "texture.h"
#include "window.h"

namespace pong {
	

	class MiddleLine {
	public:
		explicit MiddleLine(const Texture* texture);
		void Render();

	private:
		static constexpr int number_of_segments = 10;
		static constexpr int segment_width = 10;
		static constexpr float segment_height = static_cast<float>(kWindowHeight) / number_of_segments;


		const Texture* texture_;
		SDL_FRect segments_[number_of_segments] = {{0, 0, 0, 0}};
	};
}
#endif
