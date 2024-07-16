#ifndef PADDLE_H
#define PADDLE_H

#include "texture.h"
#include "window.h"

namespace pong {
	class Paddle
	{
	public:

		Paddle(float x_pos, float y_pos, const Texture* texture);

		void Render();

		void MoveUp();
		void MoveDown();
		SDL_FRect* GetRect();
		void Move(int direction);
		void SetPosition(float x_pos, float y_pos);

	private:
		static constexpr float platform_speed = 500;
		SDL_FRect rect_;
		const Texture* texture_;
	};
}
#endif