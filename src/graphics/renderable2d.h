#pragma once

#include"renderer2d.h"
#include"../math/mymath.h"
#include"shader.h"

namespace GE {
	namespace graphics {

		struct VertexData
		{
			mymath::vec3 vertex;
			mymath::vec2 uv;
			unsigned int tid;
			unsigned int colour;
		};

		class Renderable2D
		{
		protected:
			mymath::vec3 m_Position;
			mymath::vec2 m_Size;
			mymath::vec4 m_Colour;
		protected:
			Renderable2D() { }
		public:
			Renderable2D(mymath::vec3 position, mymath::vec2 size, mymath::vec4 colour)
				: m_Position(position), m_Size(size), m_Colour(colour)
			{ }

			virtual ~Renderable2D(){ }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			};

			inline const mymath::vec3& getPosition() const { return m_Position; }
			inline const mymath::vec2& getSize() const { return m_Size; }
			inline const mymath::vec4& getColour() const { return m_Colour; }
		};

	}
}