#include "Ball.h"
#include "Game.h"
#include "Window.h"
namespace pong {
	Ball::Ball(float xpos, float ypos) 
	{
		rect = { xpos, ypos, ball_size, ball_size };
	}

	void Ball::reset_ball() {
		rect.x = static_cast<float>(Window::get_width()) / 2;
		rect.y = static_cast<float>(Window::get_height()) / 2;

		set_speed(initial_speed);
	}

	Ball::~Ball() {}
	

	void Ball::update() {
		rect.x += static_cast<float>(direction_.x) * Game::get_delta_time() * static_cast<float>(speed);
		rect.y += static_cast<float>(direction_.y) * Game::get_delta_time() * static_cast<float>(speed);
	}

	void Ball::draw() const {
		SDL_RenderFillRectF(Window::get_renderer(), &rect);
	}

	void Ball::check_collision(const SDL_FRect* left_paddle, const SDL_FRect* right_paddle) {
		//Checking for the bottom and the top wall collision
		if (rect.y <= 0 || rect.y >= static_cast<float>(Window::get_height()) - rect.h) direction_.y *= -1;


		if (collision(left_paddle)) { //Checking for collision with the left paddle
			direction_.x = x_direction_const;
		}
		else if (collision(right_paddle)) { //Checking for collision the with right paddle	 
			direction_.x = -x_direction_const;
		}

		//Checking if the ball is out of bounds on the left
		if (rect.x <= 0) {
			Game::self->add_score(0);
		}
		//Checking if the ball is out of bounds on the right
		else if (rect.x >= static_cast<float>(Window::get_width()) - rect.w) {
			Game::self->add_score(1);
		}
	}

	bool Ball::collision(const SDL_FRect* collision_target) {
		if (rect.y + rect.h < collision_target->y) return false;

		if (rect.y > collision_target->y + collision_target->h) return false;

		if (rect.x + rect.w < collision_target->x || rect.x > collision_target->x + collision_target->w) return false;

		add_speed(7);
		return true;
	}

	void Ball::set_speed(const int new_speed) {
		speed = new_speed;
	}

	void Ball::add_speed(const int amount) {
		speed = std::min(speed + amount, max_speed);
	}

}
