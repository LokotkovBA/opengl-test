#include "layer.h"

namespace GE {

	namespace graphics {

		Layer::Layer(Renderer2D* renderer, Shader* shader, mymath::mat4 projectionMatrix)
			:m_ProjectionMatrix(projectionMatrix), m_Renderer(renderer), m_Shader(shader)
		{
			m_Shader->enable();
			m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
			m_Shader->disable();
		}

		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;
			for (int i = 0; i < m_Renderables.size(); i++)
				delete m_Renderables[i];
		}

		void Layer::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_Shader->enable();

			m_Renderer->begin();
			int i = 0;
			for (const Renderable2D* renderable : m_Renderables)
				renderable->submit(m_Renderer);
			m_Renderer->end();

			m_Renderer->flush();
			m_Shader->disable();
		}
	}
}