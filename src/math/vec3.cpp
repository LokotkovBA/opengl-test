#include "vec3.h"

namespace GE {

	namespace mymath {



		vec3::vec3()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}


		vec3::vec3(const float& x, const float& y, const float& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3& vec3::add(const vec3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::multiply(const vec3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::divide(const vec3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		vec3& operator+(vec3 left, const vec3& right)
		{
			return left.add(right);
		}

		vec3& operator-(vec3 left, const vec3& right)
		{
			return left.subtract(right);
		}

		vec3& operator*(vec3 left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec3& operator/(vec3 left, const vec3& right)
		{
			return left.divide(right);
		}

		vec3& vec3::operator+=(const vec3& other)
		{
			return add(other);
		}

		vec3& vec3::operator-=(const vec3& other)
		{
			return subtract(other);
		}

		vec3& vec3::operator*=(const vec3& other)
		{
			return multiply(other);
		}

		vec3& vec3::operator/=(const vec3& other)
		{
			return divide(other);
		}

		bool vec3::operator==(const vec3& other)
		{
			return this->x == other.x && this->y == other.y && this->z == other.z;
		}
		
		bool vec3::operator!=(const vec3& other)
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector)
		{
			return stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		}
	}
}