#pragma once

#include<GL/glew.h>
#include"../math/mymath.h"
#include"buffers/allbuffers.h"
#include"shader.h"

namespace GE {
	namespace graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<mymath::mat4> m_TransgormationStack;
			const mymath::mat4* m_TransformationBack;
		protected:
			Renderer2D()
			{
				m_TransgormationStack.push_back(mymath::mat4::identity());
				m_TransformationBack = &m_TransgormationStack.back();
			}
		public:
			void push(mymath::mat4 matrix, bool override = false)
			{
				if(override)
					m_TransgormationStack.push_back(matrix);
				else
					m_TransgormationStack.push_back(m_TransgormationStack.back() * matrix);
				m_TransformationBack = &m_TransgormationStack.back();
			}

			void pop()
			{
				//TODO: log this!
				if (m_TransgormationStack.size() > 1)
					m_TransgormationStack.pop_back();
				m_TransformationBack = &m_TransgormationStack.back();
			}

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void end() {}
			virtual void flush() = 0;
		};

	}
}