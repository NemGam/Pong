#include "MiddleLine.h"
#include "Window.h"

namespace pong {
	MiddleLine::MiddleLine() {
		float segment_size = Window::get_height() / (float)segments_amount;
		for (int i = 0; i < segments_amount; i++) {
			segments[i] = { Window::get_width() / 2.0f, i * segment_size, segment_width, segment_size - 15 };
		}
	}
	
	void MiddleLine::draw() {
		for (int i = 0; i < segments_amount; i++) {
			SDL_RenderFillRectF(Window::get_renderer(), &segments[i]);
		}
	}
}