#include "paddle.h"
#include "game.h"
#include "texture.h"
#include "global_consts.h"

namespace pong {
	Paddle::Paddle(float x_pos, float y_pos, const Texture* texture) :
		rect_({x_pos, y_pos, static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight())}), texture_(texture)
	{}

	void Paddle::Render() {
		texture_->Render(rect_.x, rect_.y);
	}


	void Paddle::MoveUp()
	{
		Move(-1);
	}

	void Paddle::MoveDown() 
	{
		Move(1);
	}

	void Paddle::Move(const int direction)
	{
		rect_.y += platform_speed * static_cast<float>(direction) * Game::GetDeltaTime();

		if (rect_.y < 0) rect_.y = 0;
		else if (rect_.y + rect_.h > static_cast<float>(kWindowHeight)) {
			rect_.y = static_cast<float>(kWindowHeight) - rect_.h;
		}
	}

	void Paddle::SetPosition(float x_pos, float y_pos) {
		rect_.x = x_pos;
		rect_.y = y_pos;
	}


	SDL_FRect* Paddle::GetRect()
	{
		return &rect_;
	}
}
