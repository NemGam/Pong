#include "middle_line.h"

#include "global_consts.h"
#include "logger.h"
#include "texture.h"
#include "window.h"

namespace pong {
	MiddleLine::MiddleLine(const Texture* texture) : texture_(texture)
	{
		for (int i = 0; i < number_of_segments; i++) {
			segments_[i] = { static_cast<float>(kWindowWidth) / 2.0f, i * segment_height, segment_width, segment_height};
		}
	}
	
	void MiddleLine::Render() {
		for (const auto& segment : segments_) {
			texture_->Render(segment.x, segment.y, segment_width, static_cast<int>(segment_height - 15));
		}
	}
}