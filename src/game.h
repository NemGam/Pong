#ifndef GAME_H
#define GAME_H
#include <vector>

#include "asset_database.h"
#include "window.h"
#include "ball.h"
#include "paddle.h"
#include "text.h"
#include "middle_line.h"

namespace pong {
	class Game {
	public:

		Game(const Window& window, const AssetDatabase& database);
		Game(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;


		~Game() = default;


		//Add score to the player, where 0 - left player, 1 - right player.
		void AddScore(int player);
		void Run();
		static float GetDeltaTime();

		static Game* self;

	private:
		void Render();
		void HandleInput();
		void Update();


		float delta_time_;
		static bool is_running_;

		const Window& window_;
		Ball ball_;
		Paddle left_paddle_, right_paddle_;
		std::unique_ptr<Text> first_score_text_;
		std::unique_ptr<Text> second_score_text_;
		MiddleLine middle_line_;
		int left_score_, right_score_;
		Uint32 ticks_count_;
	};
}
#endif