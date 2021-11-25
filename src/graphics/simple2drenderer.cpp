#include "simple2drenderer.h"

namespace GE {
	namespace graphics {

		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			m_RenderQueue.push_back((StaticSprite*)renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_RenderQueue.empty())
			{
				const StaticSprite* renderable = m_RenderQueue.front();
				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", mymath::mat4::translate(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getIBO()->unbind();
				renderable->getVAO()->unbind();

				m_RenderQueue.pop_front();
			}
		}

	}
}