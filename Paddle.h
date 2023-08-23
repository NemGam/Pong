#ifndef PADDLE_H
#define PADDLE_H
#include "Window.h"
namespace pong {
	class Paddle
	{
	public:
		static constexpr int platform_width = 10;
		static constexpr int platform_height = 90;

		Paddle(float xpos, float ypos);
		void draw() const;
		void move_up();
		void move_down();
		SDL_FRect* get_rect();
		void move(int direction);
	private:
		static constexpr float platform_speed = 500;
		SDL_FRect rect{};
	};
}
#endif