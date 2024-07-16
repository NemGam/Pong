#include <iostream>
#include "game.h"

#include "logger.h"
#include "text.h"

namespace pong {
	SDL_Event event;
	bool Game::is_running_;
	Game* Game::self;

	Game::Game(const Window& window, const AssetDatabase& database)
		: delta_time_(0), window_(window),
		ball_(static_cast<float>(window.GetWidth()) * 0.5f, static_cast<float>(window.GetHeight()) * 0.5f, database.GetTexture("ball.png")),
		left_paddle_(0, 0, database.GetTexture("paddle.png")),
		right_paddle_(0, 0, database.GetTexture("paddle.png")),
		middle_line_(database.GetTexture("middle_line.png")),
		left_score_(0),
		right_score_(0),
		ticks_count_(0)
	{
		
		
		float platform_x_offset = 18;

		left_paddle_.SetPosition(platform_x_offset, static_cast<float>(window.GetHeight() / 2.0 - left_paddle_.GetRect()->h));
		right_paddle_.SetPosition(static_cast<float>(window.GetWidth()) - platform_x_offset - right_paddle_.GetRect()->w, static_cast<float>(window.GetHeight() / 2.0 - left_paddle_.GetRect()->h));

		first_score_text_ = Text::Create(window, window.GetFont("GILB____.TTF", 90), window.GetWidth() / 4 - 100, window.GetHeight() / 4, "0", Text::TextAlignment::kLeft, { 50, 50, 50, 255 });
		second_score_text_ = Text::Create(window, window.GetFont("GILB____.TTF", 90), window.GetWidth() / 4 * 3 + 100, window.GetHeight() / 4, "0", Text::TextAlignment::kRight, { 50, 50, 50, 255 });
		
		self = this;
	}


	void Game::Run() {
		is_running_ = true;
		static uint32_t next_ticks = 0;
		static uint32_t last_ticks = 0;

		while (is_running_){
			
			while (SDL_GetTicks() < next_ticks)
				;

			const uint32_t current_ticks = SDL_GetTicks();
			next_ticks = current_ticks + 16;

			const uint32_t delta_ticks = current_ticks - last_ticks;

			delta_time_ = static_cast<float>(delta_ticks) * 0.001f;

			last_ticks = current_ticks;

			if (delta_time_ > 0.05f) delta_time_ = 0.05f;

			if (delta_time_ < 0.0f) delta_time_ = 0.0f;

			ticks_count_ = SDL_GetTicks();

			HandleInput();

			Update();

			Render();
		}
		SDL_Quit();
	}


	void Game::Render() {
		SDL_Renderer* renderer = const_cast<SDL_Renderer*>(window_.GetRenderer());

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Render score texts
		first_score_text_->Render();
		second_score_text_->Render();


		//Render middle line
		middle_line_.Render();

		ball_.Render();

		left_paddle_.Render();
		right_paddle_.Render();


		SDL_RenderPresent(renderer);
	}

	void Game::HandleInput() {
		const Uint8* keystate = SDL_GetKeyboardState(nullptr);

		//Handling right platform
		if (keystate[SDL_SCANCODE_UP]) right_paddle_.MoveUp();
		else if (keystate[SDL_SCANCODE_DOWN]) right_paddle_.MoveDown();


		//Handling left platform
		if (keystate[SDL_SCANCODE_W]) left_paddle_.MoveUp();
		else if (keystate[SDL_SCANCODE_S]) left_paddle_.MoveDown();


		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				is_running_ = false;
				break;
			default:
				break;
			}
		}
	}

	void Game::Update() {
		ball_.Update();
		ball_.CheckCollision(*left_paddle_.GetRect(), *right_paddle_.GetRect());
	}


	void Game::AddScore(const int player) {
		if (!player) {
			right_score_ = static_cast<int>(fmin(99, ++right_score_));
			second_score_text_->SetText(std::to_string(right_score_));
		}
		else {
			left_score_ = static_cast<int>(fmin(99, ++left_score_));
			first_score_text_->SetText(std::to_string(left_score_));
		}
		ball_.ResetBall();
	}

	float Game::GetDeltaTime() {
		return self->delta_time_;
	}
}
