#ifndef BALL_H
#define BALL_H
#include <SDL.h>

namespace pong {
	class Ball {
	public:

		Ball(float xpos, float ypos);
		~Ball();

		/**
		 * @brief Set the ball position to the middle of the screen and slow it down.
		*/
		void reset_ball();

		/**
		 * @brief Set speed of the ball.
		 * @param new_speed Speed to set.
		*/
		void set_speed(int new_speed);

		void add_speed(int amount);

		/**
		 * @brief Update position of the ball.
		*/
		void update();

		void check_collision(const SDL_FRect* left_paddle, const SDL_FRect* right_paddle);

		void draw() const;

	private:
		static constexpr int x_direction_const = 10;
		static constexpr int y_direction_const = 5;
		static constexpr unsigned int ball_size = 10;
		static constexpr unsigned int initial_speed = 20;
		static constexpr unsigned int max_speed = 100;
		unsigned int speed = 20;
		SDL_FRect rect{ 0,0,0,0 };

		struct MovementDirection {
			int x = x_direction_const;
			int y = y_direction_const;
		};

		MovementDirection direction_;

		bool collision(const SDL_FRect* collision_target);
	};
}
#endif
