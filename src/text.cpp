#include "text.h"

#include "logger.h"
#include "window.h"

namespace pong {

	Text::Text(const SDL_Renderer* renderer, std::string text, const TTF_Font* font, int x_pos, int y_pos,
	           TextAlignment alignment, SDL_Color color) :
		x_pos_(x_pos),
		y_pos_(y_pos),
		text_(std::move(text)),
		rect_{ 0, 0, 0, 0 },
		font_(font),
		color_(color),
		alignment_(alignment),
		texture_(renderer)
	{
		Regenerate();
	}

	void Text::SetText(const std::string& text) {
		text_ = text;
		Regenerate();
	}

	void Text::Regenerate() {

		texture_.CreateFromText(text_, const_cast<TTF_Font*>(font_), color_);

		rect_.w = texture_.GetWidth();
		rect_.h = texture_.GetHeight();
		
		rect_ = GetAlignedRect(rect_, alignment_);
	}

	SDL_Rect Text::GetAlignedRect(SDL_Rect rect, TextAlignment alignment) const {

		rect.y = y_pos_;

		switch (alignment) {
			case TextAlignment::kLeft:
				rect.x = x_pos_;
				break;
			case TextAlignment::kMiddle:
				rect.x = x_pos_ - rect.w / 2;
				break;
			case TextAlignment::kRight:
				rect.x = x_pos_ - rect.w;
				break;
		}

		return rect;
	}

	void Text::Render() const {

		texture_.Render(rect_.x, rect_.y);
	}
}
