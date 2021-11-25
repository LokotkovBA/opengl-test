#pragma once

#include "renderable2d.h"

namespace GE {
	namespace graphics {

		class Sprite : public Renderable2D
		{
		public:
			Sprite(float x, float y, float width, float height, const mymath::vec4& colour);
		};
	}
}