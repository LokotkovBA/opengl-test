#pragma once

#include "../renderable2d.h"

namespace GE {
	namespace graphics {

		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_Renderables;
			mymath::mat4 m_TransformationMatrix;
		public:
			Group(const mymath::mat4& transform);
			void add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;
		};
	}
}