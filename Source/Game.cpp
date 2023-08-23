#include <iostream>
#include "Game.h"

namespace pong {
	SDL_Event event;
	bool Game::is_running;
	Game* Game::self;

	Game::Game()
	: window( "PONG", 640, 480, "./GILB____.TTF", SDL_WINDOW_SHOWN ),
	ball(static_cast<float>(Window::get_width()) * 0.5f, static_cast<float>(Window::get_height()) * 0.5f),
	left_paddle(static_cast<float>(platform_x_offset), static_cast<float>(Window::get_height() - Paddle::platform_height) / 2),
	right_paddle(static_cast<float>(Window::get_width() - platform_x_offset) - Paddle::platform_width,
		static_cast<float>(Window::get_height() - Paddle::platform_height) / 2),
	first_score_text(Window::get_font(), Window::get_width() / 4 - 100, Window::get_height() / 4, "0", 0, { 50, 50, 50, 255 }),
	second_score_text(Window::get_font(), Window::get_width() / 4 * 3 + 100, Window::get_height() / 4, "0", 1, { 50, 50, 50, 255 })
	{
		mTicksCount = 0;

		self = this;

		delta_time = 0;

		left_score = 0;
		right_score = 0;
	}

	Game::~Game() = default;

	void Game::run() {
		is_running = true;
		static uint32_t next_ticks = 0;
		static uint32_t last_ticks = 0;

		while (is_running){
			
			while (SDL_GetTicks() < next_ticks)
				;

			const uint32_t current_ticks = SDL_GetTicks();
			next_ticks = current_ticks + 16;

			const uint32_t delta_ticks = current_ticks - last_ticks;

			delta_time = static_cast<float>(delta_ticks) * 0.001f;

			last_ticks = current_ticks;

			if (delta_time > 0.05f) delta_time = 0.05f;

			if (delta_time < 0.0f) delta_time = 0.0f;

			mTicksCount = SDL_GetTicks();

			handle_input();

			update();

			render();
		}
		SDL_Quit();
	}


	void Game::render() {
		SDL_SetRenderDrawColor(Window::get_renderer(), 0, 0, 0, 255);
		SDL_RenderClear(Window::get_renderer());

		//Render score texts
		first_score_text.render();
		second_score_text.render();

		//Render paddles
		SDL_SetRenderDrawColor(Window::get_renderer(), 255, 255, 255, 255);
		left_paddle.draw();
		right_paddle.draw();

		//Render middle line
		SDL_SetRenderDrawColor(Window::get_renderer(), 0, 50, 50, 255);
		middle_line.draw();

		//Render ball
		SDL_SetRenderDrawColor(Window::get_renderer(), 0, 255, 0, 255);
		ball.draw();


		SDL_RenderPresent(Window::get_renderer());
	}

	void Game::handle_input() {
		const Uint8* keystate = SDL_GetKeyboardState(nullptr);

		//Handling right platform
		if (keystate[SDL_SCANCODE_UP]) right_paddle.move_up();
		else if (keystate[SDL_SCANCODE_DOWN]) right_paddle.move_down();


		//Handling left platform
		if (keystate[SDL_SCANCODE_W]) left_paddle.move_up();
		else if (keystate[SDL_SCANCODE_S]) left_paddle.move_down();


		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				is_running = false;
				break;
			default:
				break;
			}
		}
	}

	void Game::update() {
		ball.update();
		ball.check_collision(left_paddle.get_rect(), right_paddle.get_rect());
	}


	void Game::add_score(const int player) {
		if (!player) {
			right_score = static_cast<int>(fmin(99, ++right_score));
			second_score_text.set_text(right_score);
		}
		else {
			left_score = static_cast<int>(fmin(99, ++left_score));
			first_score_text.set_text(left_score);
		}
		ball.reset_ball();
	}

	float Game::get_delta_time() {
		return self->delta_time;
	}
}
