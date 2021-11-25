#include "sprite.h"

namespace GE {
	namespace graphics {

		Sprite::Sprite(float x, float y, float width, float height, const mymath::vec4& colour)
			:Renderable2D(mymath::vec3(x, y, 0), mymath::vec2(width, height), colour)
		{

		}
	}
}