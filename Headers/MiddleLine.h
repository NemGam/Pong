#ifndef MIDDLELINE_H
#define MIDDLELINE_H

#include <SDL.h>

namespace pong {
	constexpr int segments_amount = 10;
	constexpr int segment_width = 10;

	class MiddleLine {
	public:
		MiddleLine();
		void draw();

	private:
		SDL_FRect segments[segments_amount] = { 0, 0, 0, 0 };
	};
}
#endif
