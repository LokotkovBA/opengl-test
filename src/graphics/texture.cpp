#include "texture.h"
namespace GE {
	namespace graphics {

		Texture::Texture(const std::string& filename)
			:m_Filename(filename)
		{
			m_TID = load();
		}

		Texture::~Texture()
		{

		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_TID);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::load()
		{
			BYTE* pixels = load_image(m_Filename.c_str(), &m_Width, &m_Height);

			GLuint output;
			glGenTextures(1, &output);
			glBindTexture(GL_TEXTURE_2D, output);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			//delete[] pixels;
			return output;
		}
	}
}