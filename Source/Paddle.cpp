#include "Paddle.h"
#include "Game.h"

namespace pong {
	Paddle::Paddle(float xpos, float ypos)
	{
		rect = {
			xpos,
			ypos,
			platform_width,
			platform_height
		};
	}

	void Paddle::draw() const
	{
		SDL_RenderFillRectF(Window::get_renderer(), &rect);
	}

	void Paddle::move_up()
	{
		move(-1);
	}

	void Paddle::move_down()
	{
		move(1);
	}

	void Paddle::move(const int direction)
	{
		rect.y += platform_speed * static_cast<float>(direction) * Game::get_delta_time();

		if (rect.y < 0) rect.y = 0;
		else if (rect.y + rect.h > static_cast<float>(Window::get_height())) {
			rect.y = static_cast<float>(Window::get_height()) - rect.h;
		}
	}

	SDL_FRect* Paddle::get_rect()
	{
		return &rect;
	}
}
