#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include"../utils/fileutils.h"
#include"../math/mymath.h"

namespace GE {
	namespace graphics {
		
		class Shader 
		{
		private:
			GLuint m_ShaderID;
			const char* m_VertPath;
			const char* m_FragPath;

		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();


			void setUniform1f(const GLchar* name, float value);
			void setUnfirm1i(const GLchar* name, int value);
			void setUnfirm2f(const GLchar* name, const mymath::vec2& value);
			void setUnfirm3f(const GLchar* name, const mymath::vec3& value);
			void setUnfirm4f(const GLchar* name, const mymath::vec4& value);
			void setUniformMat4(const GLchar* name, const mymath::mat4& matrix);

			void enable() const;
			void disable() const;
		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};

	}
}