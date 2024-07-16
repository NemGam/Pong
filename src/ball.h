#ifndef BALL_H
#define BALL_H
#include <SDL2/SDL.h>

#include "texture.h"
#include "window.h"


namespace pong {
	class Ball{
	public:

		Ball(float x_pos, float y_pos, const Texture* texture);

		//Set the ball position to the middle of the screen and slow it down.
		void ResetBall();

		void SetSpeed(int new_speed);

		void AddSpeed(int amount);

		//Update position of the ball.
		void Update();

		void Render() const;

		void CheckCollision(const SDL_FRect& left_paddle, const SDL_FRect& right_paddle);


	private:
		static constexpr int x_direction = 10;
		static constexpr int y_direction = 5;
		static constexpr int initial_speed = 20;
		static constexpr int max_speed = 100;


		bool Collision(const SDL_FRect& collision_target);


		int speed_ = 20;
		SDL_FRect rect_;
		const Texture* texture_;

		struct MovementDirection {
			int x = x_direction;
			int y = y_direction;
		};

		MovementDirection direction_;

	};
}
#endif
