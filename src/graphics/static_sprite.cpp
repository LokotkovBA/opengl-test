#include "static_sprite.h"

namespace GE {
	namespace graphics {

		StaticSprite::StaticSprite(float x, float y, float width, float height, const mymath::vec4& colour, Shader& shader)
			: Renderable2D(mymath::vec3(x, y, 0), mymath::vec2(width, height), colour), m_Shader(shader)
		{
			m_VertexArray = new VertexArray();
			GLfloat vertices[] =
			{
				0, 0, 0,
				0, height, 0,
				width, height, 0,
				width, 0, 0
			};

			GLfloat colours[] =
			{
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w
			};

			m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colours, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			m_IndexBuffer = new IndexBuffer(indices, 6);
		}
		StaticSprite::~StaticSprite()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}
	}
}
