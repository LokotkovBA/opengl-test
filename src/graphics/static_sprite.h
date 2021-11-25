#pragma once

#include "renderable2d.h"

namespace GE {
	namespace graphics {

		class StaticSprite : public Renderable2D
		{
		private:
			mymath::vec3 m_Position;
			mymath::vec2 m_Size;
			mymath::vec4 m_Colour;

			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			Shader& m_Shader;
		public:
			StaticSprite(float x, float y, float width, float height, const mymath::vec4& color, Shader& shader);
			~StaticSprite();
			inline const VertexArray* getVAO() const { return m_VertexArray; };
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; };

			inline Shader& getShader() const { return m_Shader; };
		};
	}
}
