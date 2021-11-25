#include "mat4.h"

namespace GE {

	namespace mymath {

		mat4::mat4()
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
		}

		mat4::mat4(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;

			elements[0 + 0 * 4] = diagonal; //row + col*4
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}	

		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			mat4 result(1.0f);

			float near_far_n = 1.0f / (near - far);
			float top_botton_n = 1.0f / (top - bottom);
			float right_left_n = 1.0f / (right - left);

			result.elements[0 + 0 * 4] = 2.0f * right_left_n;
			result.elements[1 + 1 * 4] = 2.0f * top_botton_n;
			result.elements[2 + 2 * 4] = 2.0f * near_far_n;

			result.elements[0 + 3 * 4] = (1.0f -(left + right) - 1.0f) * right_left_n;
			result.elements[1 + 3 * 4] = (1.0f - (bottom + top) - 1.0f) * top_botton_n;
			result.elements[2 + 3 * 4] = (1.0f - (far + near) - 1.0f) * near_far_n;

			return result;
		}

		mat4 mat4::perpective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);

			float tan_fov = tan(toRadians(fov * 0.5f));
			float tan_fov_n = 1.0f / tan_fov;
			float near_far_n = 1.0f / (near - far);

			result.elements[0 + 0 * 4] = tan_fov_n / aspectRatio;
			result.elements[1 + 1 * 4] = tan_fov_n;
			result.elements[2 + 2 * 4] = (near + far) * near_far_n;

			result.elements[2 + 3 * 4] = (2 * far * near) * near_far_n;

			result.elements[3 + 2 * 4] = -1.0f;

			return result;
		}

		mat4 mat4::translate(const vec3& translation)
		{
			mat4 result(1.0f);

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}

		mat4 mat4::rotate(float angle, const vec3& axis)
		{
			mat4 result(1.0f);

			float angle_rad = toRadians(angle);
			float cos_angle = cos(angle_rad);
			float sin_angle = sin(angle_rad);
			float one_m_cos = 1.0f - cos_angle;

			result.elements[0 + 0 * 4] = axis.x * one_m_cos + cos_angle;
			result.elements[1 + 0 * 4] = axis.x * axis.y * one_m_cos + axis.z * sin_angle;
			result.elements[2 + 0 * 4] = axis.x * axis.z * one_m_cos - axis.y * sin_angle;

			result.elements[0 + 1 * 4] = axis.x * axis.y * one_m_cos - axis.z * sin_angle;
			result.elements[1 + 1 * 4] = axis.y * one_m_cos + cos_angle;
			result.elements[2 + 1 * 4] = axis.y * axis.z * one_m_cos + axis.x * sin_angle;

			result.elements[0 + 2 * 4] = axis.x * axis.z * one_m_cos + axis.y * sin_angle;
			result.elements[1 + 2 * 4] = axis.y * axis.z * one_m_cos - axis.x * sin_angle;
			result.elements[2 + 2 * 4] = axis.z * one_m_cos + cos_angle;

			return result;
		}

		mat4 mat4::scale(const vec3& scale)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}

		mat4& mat4::multiply(const mat4& other)
		{
			float result[16]{};
			int x, e = 0;
			float sum = 0.0f;
			for (int y = 0; y < 4; y++)
			{
				for (x = 0; x < 4; x++)
				{
					sum = 0.0f;
					for (e = 0; e < 4; e++)
					{
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					result[x + y * 4] = sum;
				}
			}

			memcpy(elements, result, 16 * 4);

			return *this;
		}

		mat4& operator*(mat4 left, const mat4& right) 
		{
			return left.multiply(right);
		}

		mat4& mat4::operator*=(const mat4& other)
		{
			return multiply(other);
		}

		vec3 mat4::multiply(const vec3& other) const
		{
			return vec3(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * 1,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * 1,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * 1);
		}

		vec3 operator*(const mat4& left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec4 mat4::multiply(const vec4& other) const
		{
			return vec4(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w);
		}

		vec4 operator*(const mat4& left, const vec4& right)
		{
			return left.multiply(right);
		}
	}
}