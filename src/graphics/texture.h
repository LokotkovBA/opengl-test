#pragma once

#include <string>
#include <GL/glew.h>
#include <FreeImage.h>
#include "../utils/imageloader.h"

namespace GE {
	namespace graphics {

		class Texture
		{
		private:
			std::string m_Filename;
			GLuint m_TID;
			GLsizei m_Width, m_Height;
		public:
			Texture(const std::string& filename);
			~Texture();
			void bind() const;
			void unbind() const;

			inline GLsizei getWidth() const { return m_Width; }
			inline GLsizei getHeight() const { return m_Height; }
		private:
			GLuint load();
		};
	}
}