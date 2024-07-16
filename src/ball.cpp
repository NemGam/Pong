#include "ball.h"
#include "game.h"
#include "global_consts.h"

namespace pong {
	Ball::Ball(float x_pos, float y_pos, const Texture* texture) :
		rect_({ x_pos, y_pos, static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight())}),
		texture_(texture)
	{}

	void Ball::ResetBall() {
		rect_.x = static_cast<float>(kWindowWidth) / 2;
		rect_.y = static_cast<float>(kWindowHeight) / 2;

		SetSpeed(initial_speed);
	}

	

	void Ball::Update() {
		rect_.x += static_cast<float>(direction_.x * speed_) * Game::GetDeltaTime();
		rect_.y += static_cast<float>(direction_.y * speed_) * Game::GetDeltaTime();
	}

	void Ball::Render() const {
		texture_->Render(rect_.x, rect_.y);
	}


	void Ball::CheckCollision(const SDL_FRect& left_paddle, const SDL_FRect& right_paddle) {
		//Checking for the bottom and the top wall collision
		if (rect_.y <= 0 || rect_.y >= static_cast<float>(kWindowHeight) - rect_.h) direction_.y *= -1;


		if (Collision(left_paddle)) { //Checking for collision with the left paddle
			direction_.x = x_direction;
		}
		else if (Collision(right_paddle)) { //Checking for collision the with right paddle	 
			direction_.x = -x_direction;
		}

		//Checking if the ball is out of bounds on the left
		if (rect_.x <= 0) {
			Game::self->AddScore(0);
		}
		//Checking if the ball is out of bounds on the right
		else if (rect_.x >= static_cast<float>(kWindowWidth) - rect_.w) {
			Game::self->AddScore(1);
		}
	}

	bool Ball::Collision(const SDL_FRect& collision_target) {
		if (rect_.y + rect_.h < collision_target.y) return false;

		if (rect_.y > collision_target.y + collision_target.h) return false;

		if (rect_.x + rect_.w < collision_target.x || rect_.x > collision_target.x + collision_target.w) return false;

		AddSpeed(7);
		return true;
	}

	void Ball::SetSpeed(const int new_speed) {
		speed_ = new_speed;
	}

	void Ball::AddSpeed(const int amount) {
		speed_ = std::min(speed_ + amount, max_speed);
	}

}
