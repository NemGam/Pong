#ifndef GAME_H
#define GAME_H
#include "Window.h"
#include "Ball.h"
#include "Paddle.h"
#include "Text.h"
#include "MiddleLine.h"

namespace pong {
	class Game {
	public:
		const int platform_x_offset = 18;
		static Game* self;

		Game();
		~Game();
		void run();
		static float get_delta_time();

		/**
		 * @brief Add score to the player.
		 * @param player Number of player, where 0 - left player, 1 - right player.
		*/
		void add_score(int player);

	private:

		float delta_time;
		static bool is_running;

		Window window;
		Ball ball;
		Paddle left_paddle;
		Paddle right_paddle;
		Text first_score_text;
		Text second_score_text;
		MiddleLine middle_line;
	
		void render();
		void handle_input();
		void update();
		int left_score, right_score;
		Uint32 mTicksCount;
	};
}
#endif