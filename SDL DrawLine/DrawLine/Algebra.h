#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>

namespace algebra
{
	template <typename T>
	class Vec4;

	template <typename T>
	class Vec2
	{
	public:
		Vec2(T x, T y) : x(x), y(y) {}
		bool operator==(const Vec2<T>& vec) const
		{
			return (x == vec.x && y == vec.y);
		}
		bool operator!=(const Vec2<T>& vec) const
		{
			return (x != vec.x || y != vec.y);
		}
		bool operator>(const Vec2<T>& vec) const
		{
			return double_length() > vec.double_length();
		}
		bool operator<(const Vec2<T>& vec) const
		{
			return double_length() < vec.double_length();
		}
		bool operator>=(const Vec2<T>& vec) const
		{
			return double_length() >= vec.double_length();
		}
		bool operator<=(const Vec2<T>& vec) const
		{
			return double_length() <= vec.double_length();
		}
		Vec2<T> operator=(const Vec2<T>& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}
		Vec2<T> operator+(T s) const
		{
			Vec2<T> vec(x, y);
			vec += s;
			return vec;
		}
		Vec2<T> operator-(T s) const
		{
			Vec2<T> vec(x, y);
			vec -= s;
			return vec;
		}
		Vec2<T> operator*(T s) const
		{
			Vec2<T> vec(x, y);
			vec *= s;
			return vec;
		}
		Vec2<T> operator/(T s) const
		{
			Vec2<T> vec(x, y);
			vec /= s;
			return vec;
		}
		Vec2<T> operator+=(T s)
		{
			x += s;
			y += s;
			return *this;
		}
		Vec2<T> operator-=(T s)
		{
			x -= s;
			y -= s;
			return *this;
		}
		Vec2<T> operator*=(T s)
		{
			x *= s;
			y *= s;
			return *this;
		}
		Vec2<T> operator/=(T s)
		{
			x /= s;
			y /= s;
			return *this;
		}
		Vec2<T> operator+(const Vec2<T>& vec) const
		{
			Vec2<T> v(x, y);
			v.x += vec.x;
			v.y += vec.y;
			return v;
		}
		Vec2<T> operator-(const Vec2<T>& vec) const
		{
			Vec2<T> v(x, y);
			v.x -= vec.x;
			v.y -= vec.y;
			return v;
		}
		T operator*(const Vec2<T>& vec) const
		{
			return x * vec.x + y * vec.y;
		}


		T length() const
		{
			return std::sqrt(double_length());
		}

		T double_length() const
		{
			return x * x + y * y;
		}

		Vec2<T> normalize() const
		{
			Vec2<T> n(x, y);
			const T len = length();
			n.x /= len;
			n.y /= len;
			return n;
		}

		friend std::ostream& operator<<(std::ostream& out, const Vec2<T>& v)
		{
			out << "{" << v.x << ", " << v.y << "}\n";
			return out;
		}
		T x;
		T y;
	};

	template <typename T>
	class Vec3
	{
	public:
		Vec3() : x(0), y(0), z(0) {}
		Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
		Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}
		Vec3(const Vec4<T>& v) : x(v.x), y(v.y), z(v.z) {}

		bool operator==(const Vec3<T>& vec) const
		{
			return (x == vec.x && y == vec.y &&
				z == vec.z);
		}
		bool operator!=(const Vec3<T>& vec) const
		{
			return (x != vec.x || y != vec.y ||
				z != vec.z);
		}
		bool operator>(const Vec3<T>& vec) const
		{
			return double_length() > vec.double_length();
		}
		bool operator<(const Vec3<T>& vec) const
		{
			return double_length() < vec.double_length();
		}
		bool operator>=(const Vec3<T>& vec) const
		{
			return double_length() >= vec.double_length();
		}
		bool operator<=(const Vec3<T>& vec) const
		{
			return double_length() <= vec.double_length();
		}

		Vec3<T> operator=(const Vec3<T>& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}
		Vec3<T> operator+(T s) const
		{
			Vec3<T> vec(x, y, z);
			vec += s;
			return vec;
		}

		Vec3<T> operator-(T s) const
		{
			Vec3<T> vec(x, y, z);
			vec -= s;
			return vec;
		}

		Vec3<T> operator*(T s) const
		{
			Vec3<T> vec(x, y, z);
			vec *= s;
			return vec;
		}
		Vec3<T> operator/(T s) const
		{
			Vec3<T> vec(x, y, z);
			vec /= s;
			return vec;
		}
		Vec3<T> operator+=(T s)
		{
			x += s;
			y += s;
			z += s;
			return *this;
		}
		Vec3<T> operator-=(T s)
		{
			x -= s;
			y -= s;
			z -= s;
			return *this;
		}
		Vec3<T> operator*=(T s)
		{
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		Vec3<T> operator/=(T s)
		{
			x /= s;
			y /= s;
			z /= s;
			return *this;
		}
		Vec3<T> operator+(const Vec3<T>& vec) const
		{
			Vec3<T> v(x, y, z);
			v.x += vec.x;
			v.y += vec.y;
			v.z += vec.z;
			return v;
		}
		Vec3<T> operator-(const Vec3<T>& vec) const
		{
			Vec3<T> v(x, y, z);
			v.x -= vec.x;
			v.y -= vec.y;
			v.z -= vec.z;
			return v;
		}
		T operator*(const Vec3<T>& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}
		Vec3<T> operator^(const Vec3<T>& vec) const
		{
			return Vec3<T>(
				y * vec.z - z * vec.y,
				z * vec.x - x * vec.z,
				x * vec.y - y * vec.x);
		}


		T length() const
		{
			return std::sqrt(double_length());
		}

		T double_length() const
		{
			return x * x + y * y + z * z;
		}

		Vec3<T> normalize() const
		{
			Vec3<T> n(x, y, z);
			const T len = length();
			n.x /= len;
			n.y /= len;
			n.z /= len;
			return n;
		}


		friend std::ostream& operator<<(std::ostream& out, const Vec3<T>& v)
		{
			out << "{" << v.x << ", " << v.y << ", " << v.z << "}\n";
			return out;
		}

		T x;
		T y;
		T z;
	};


	template <typename T>
	class Vec4
	{
	public:
		Vec4() : x(0), y(0), z(0), w(255) {}
		Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		Vec4(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z), w(1) {}
		bool operator==(const Vec4<T>& vec) const
		{
			return (x == vec.x && y == vec.y &&
				z == vec.z && w == vec.w);
		}
		bool operator!=(const Vec4<T>& vec) const
		{
			return (x != vec.x || y != vec.y ||
				z != vec.z || w != vec.w);
		}
		bool operator>(const Vec4<T>& vec) const 
		{ 
			return double_length() > vec.double_length(); 
		}
		bool operator<(const Vec4<T>& vec) const 
		{ 
			return double_length() < vec.double_length(); 
		}
		bool operator>=(const Vec4<T>& vec) const 
		{ 
			return double_length() >= vec.double_length(); 
		}
		bool operator<=(const Vec4<T>& vec) const 
		{ 
			return double_length() <= vec.double_length(); 
		}
		Vec4<T> operator=(const Vec4<T>& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
			return *this;
		}
		Vec4<T> operator+(T s) const
		{
			Vec4<T> vec(x, y, z, w);
			vec += s;
			return vec;
		}
		Vec4<T> operator-(T s) const
		{
			Vec4<T> vec(x, y, z, w);
			vec -= s;
			return vec;
		}
		Vec4<T> operator*(T s) const
		{
			Vec4<T> vec(x, y, z, w);
			vec *= s;
			return vec;
		}
		Vec4<T> operator/(T s) const
		{
			Vec4<T> vec(x, y, z, w);
			vec /= s;
			return vec;
		}
		Vec4<T> operator+=(T s)
		{
			x += s;
			y += s;
			z += s;
			w += s;
			return *this;
		}
		Vec4<T> operator-=(T s)
		{
			x -= s;
			y -= s;
			z -= s;
			w -= s;
			return *this;
		}
		Vec4<T> operator*=(T s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}
		Vec4<T> operator/=(T s)
		{
			x /= s;
			y /= s;
			z /= s;
			w /= s;
			return *this;
		}
		Vec4<T> operator+(const Vec4<T>& vec) const
		{
			Vec4<T> v(x, y, z, w);
			v.x += vec.x;
			v.y += vec.y;
			v.z += vec.z;
			v.w += vec.w;
			return v;
		}
		Vec4<T> operator-(const Vec4<T>& vec) const
		{
			Vec4<T> v(x, y, z, w);
			v.x -= vec.x;
			v.y -= vec.y;
			v.z -= vec.z;
			v.w -= vec.w;
			return v;
		}
		T operator*(const Vec4<T>& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
		}

		T length() const 
		{
			return std::sqrt(double_length());
		}

		T double_length() const
		{
			return x * x + y * y + z * z + w * w;
		}

		Vec4<T> normalize() const
		{
			Vec4<T> n(x, y, z, w);
			const T len = length();
			n.x /= len;
			n.y /= len;
			n.z /= len;
			n.w /= len;
			return n;
		}


		friend std::ostream& operator<<(std::ostream& out, const Vec4<T>& v)
		{
			out << "{" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "}\n";
			return out;
		}

		T x;
		T y;
		T z;
		T w;
	};

	

	template <typename T>
	class Matrix2
	{
	public:
		Matrix2(T m11, T m12, T m21, T m22) : m11(m11), m12(m12), m21(m21), m22(m22){}
		Matrix2(const Matrix2<T>& mat) 
		{
			m11 = mat.m11;
			m12 = mat.m12;
			m21 = mat.m21;
			m22 = mat.m22;
		}

		Matrix2<T> operator+(const Matrix2<T>& mat)
		{
			Matrix2<T> newMat(*this);
			newMat.m11 += mat.m11;
			newMat.m12 += mat.m12;
			newMat.m21 += mat.m21;
			newMat.m22 += mat.m22;
			return newMat;
		}
		Matrix2<T> operator-(const Matrix2<T>& mat)
		{
			Matrix2<T> newMat(*this);
			newMat.m11 -= mat.m11;
			newMat.m12 -= mat.m12;
			newMat.m21 -= mat.m21;
			newMat.m22 -= mat.m22;
			return newMat;
		}
		Matrix2<T> operator*(T s)
		{
			Matrix2<T> newMat(*this);
			newMat.m11 *= s;
			newMat.m12 *= s;
			newMat.m21 *= s;
			newMat.m22 *= s;
			return newMat;
		}
		Matrix2<T> operator/(T s)
		{
			Matrix2<T> newMat(*this);
			newMat.m11 /= s;
			newMat.m12 /= s;
			newMat.m21 /= s;
			newMat.m22 /= s;
			return newMat;
		}
		Matrix2<T> transpose() const
		{
			Matrix2<T> mat(*this);
			mat.m12 = m21;
			mat.m21 = m12;
			return mat;
		}
		Matrix2<T> operator*(const Matrix2<T>& m) const 
		{
			Matrix2<T> newMat(*this);
			newMat.m11 = Vec2<T>(m11, m12)*Vec2<T>(m.m11, m.m21);
			newMat.m12 = Vec2<T>(m11, m12)*Vec2<T>(m.m12, m.m22);
			newMat.m21 = Vec2<T>(m21, m22)*Vec2<T>(m.m11, m.m21);
			newMat.m22 = Vec2<T>(m21, m22)*Vec2<T>(m.m12, m.m22);

			return newMat;
		}
		T det() const
		{
			return m11 * m22 - m12 * m21;
		}

		Matrix2<T> minor() const
		{
			Matrix2<T> mat(*this);
			mat.m11 = m22;
			mat.m12 = m21;
			mat.m21 = m12;
			mat.m22 = m11;

			return mat;
		}

		Matrix2<T> cofactor() const
		{
			Matrix2<T> mat = minor();
			return Matrix2<T>(mat.m11, -mat.m12,
						      -mat.m21, mat.m22);
		}

		Matrix2<T> adj() const
		{
			return Matrix2<T>(*this).cofactor().transpose();
		}

		Matrix2<T> inv() const
		{
			return adj() * (1 / det());
		}


		friend std::ostream& operator<<(std::ostream& out, const Matrix2<T>& m)
		{
			out << "[" << m.m11 << ", " << m.m12 << "\n";
			out << m.m21 << ", " << m.m22 << "]\n";
			return out;
		}

		T m11;
		T m12;
		T m21;
		T m22;
	};


	template <typename T>
	class Matrix3
	{
	public:
		Matrix3(T m11, T m12, T m13,
			T m21, T m22, T m23,
			T m31, T m32, T m33) :
			m11(m11), m12(m12), m13(m13),
			m21(m21), m22(m22), m23(m23),
			m31(m31), m32(m32), m33(m33) {}

		Matrix3(const Matrix3<T>& mat)
		{
			m11 = mat.m11;
			m12 = mat.m12;
			m13 = mat.m13;
			m21 = mat.m21;
			m22 = mat.m22;
			m23 = mat.m23;
			m31 = mat.m31;
			m32 = mat.m32;
			m33 = mat.m33;
		}

		Matrix3<T> operator+(const Matrix3<T>& mat)
		{
			Matrix3<T> newMat(*this);
			newMat.m11 += mat.m11;
			newMat.m12 += mat.m12;
			newMat.m13 += mat.m13;
			newMat.m21 += mat.m21;
			newMat.m22 += mat.m22;
			newMat.m23 += mat.m23;
			newMat.m31 += mat.m31;
			newMat.m32 += mat.m32;
			newMat.m33 += mat.m33;
			return newMat;
		}
		Matrix3<T> operator-(const Matrix3<T>& mat)
		{
			Matrix3<T> newMat(*this);
			newMat.m11 -= mat.m11;
			newMat.m12 -= mat.m12;
			newMat.m13 -= mat.m13;
			newMat.m21 -= mat.m21;
			newMat.m22 -= mat.m22;
			newMat.m23 -= mat.m23;
			newMat.m31 -= mat.m31;
			newMat.m32 -= mat.m32;
			newMat.m33 -= mat.m33;
			return newMat;
		}

		Matrix3<T> operator*(T s)
		{
			Matrix3<T> newMat(*this);
			newMat.m11 *= s;
			newMat.m12 *= s;
			newMat.m13 *= s;
			newMat.m21 *= s;
			newMat.m22 *= s;
			newMat.m23 *= s;
			newMat.m31 *= s;
			newMat.m32 *= s;
			newMat.m33 *= s;
			return newMat;
		}

		Matrix3<T> operator/(T s)
		{
			Matrix3<T> newMat(*this);
			newMat.m11 /= s;
			newMat.m12 /= s;
			newMat.m13 /= s;
			newMat.m21 /= s;
			newMat.m22 /= s;
			newMat.m23 /= s;
			newMat.m31 /= s;
			newMat.m32 /= s;
			newMat.m33 /= s;
			return newMat;
		}

		Matrix3<T> transpose() const
		{
			Matrix3<T> mat(*this);
			mat.m12 = m21;
			mat.m13 = m31;
			mat.m21 = m12;
			mat.m23 = m32;
			mat.m31 = m13;
			mat.m32 = m23;
			return mat;
		}

		Matrix3<T> operator*(const Matrix3<T>& m) const
		{
			Matrix3<T> newMat(*this);
			newMat.m11 = Vec3<T>(m11, m12, m13)*Vec3<T>(m.m11, m.m21, m.m31);
			newMat.m12 = Vec3<T>(m11, m12, m13)*Vec3<T>(m.m12, m.m22, m.m32);
			newMat.m13 = Vec3<T>(m11, m12, m13)*Vec3<T>(m.m13, m.m23, m.m33);

			newMat.m21 = Vec3<T>(m21, m22, m23)*Vec3<T>(m.m11, m.m21, m.m31);
			newMat.m22 = Vec3<T>(m21, m22, m23)*Vec3<T>(m.m12, m.m22, m.m32);
			newMat.m23 = Vec3<T>(m21, m22, m23)*Vec3<T>(m.m13, m.m23, m.m33);

			newMat.m31 = Vec3<T>(m31, m32, m33)*Vec3<T>(m.m11, m.m21, m.m31);
			newMat.m32 = Vec3<T>(m31, m32, m33)*Vec3<T>(m.m12, m.m22, m.m32);
			newMat.m33 = Vec3<T>(m31, m32, m33)*Vec3<T>(m.m13, m.m23, m.m33);

			return newMat;
		}

		T det() const
		{
			Matrix2<T> mat1 (m22, m23, m32, m33);
			Matrix2<T> mat2 (m21, m23, m31, m33);
			Matrix2<T> mat3 (m21, m22, m31, m32);

			return m11 * mat1.det() -
				   m12 * mat2.det() +
				   m13 * mat3.det();
		}

		Matrix3<T> minor() const
		{
			Matrix3<T> mat(*this);
			mat.m11 = Matrix2<T>(m22, m23, m32, m33).det();
			mat.m12 = Matrix2<T>(m21, m23, m31, m33).det();
			mat.m13 = Matrix2<T>(m21, m22, m31, m32).det();

			mat.m21 = Matrix2<T>(m12, m13, m32, m33).det();
			mat.m22 = Matrix2<T>(m11, m13, m31, m33).det();
			mat.m23 = Matrix2<T>(m11, m12, m31, m32).det();

			mat.m31 = Matrix2<T>(m12, m13, m22, m23).det();
			mat.m32 = Matrix2<T>(m11, m13, m21, m23).det();
			mat.m33 = Matrix2<T>(m11, m12, m21, m22).det();

			return mat;
		}

		Matrix3<T> cofactor() const
		{
			Matrix3<T> mat = minor();
			return Matrix3<T>(mat.m11, -mat.m12, mat.m13,
							  -mat.m21, mat.m22, -mat.m23,
							  mat.m31, -mat.m32, mat.m33);
		}

		Matrix3<T> adj() const
		{
			return Matrix3<T>(*this).cofactor().transpose();
		}

		Matrix3<T> inv() const 
		{
			return adj() * (1 / det());
		}


		friend std::ostream& operator<<(std::ostream& out, const Matrix3<T>& m)
		{
			out << "[" << m.m11 << ", " << m.m12 << ", " << m.m13 << "\n";
			out << m.m21 << ", " << m.m22 << ", " << m.m23 << "\n";
			out << m.m31 << ", " << m.m32 << ", " << m.m33 << "]\n";
			return out;
		}

		static Matrix3<T> rotateMatrixX(T degree) {
			T rad = degree * M_PI / 180;
			return Matrix3(1, 0, 0,
				0, std::cos(rad), -std::sin(rad),
				0, std::sin(rad), std::cos(rad));
		}

		static Matrix3<T> rotateMatrixY(T degree) {
			T rad = degree * M_PI / 180;
			return Matrix3(std::cos(rad), 0, std::sin(rad),
				0, 1, 0,
				-std::sin(rad), 0, std::cos(rad));
		}

		static Matrix3<T> rotateMatrixZ(T degree) {
			T rad = degree * M_PI / 180;
			return Matrix3(std::cos(rad), -std::sin(rad), 0,
				std::sin(rad), std::cos(rad), 0,
				0, 0, 1);
		}

		T m11;
		T m12;
		T m13;
		T m21;
		T m22;
		T m23;
		T m31;
		T m32;
		T m33;

	};

	template <typename T>
	class Matrix4
	{
	public:
		Matrix4(T m11, T m12, T m13, T m14,
			T m21, T m22, T m23, T m24,
			T m31, T m32, T m33, T m34,
			T m41, T m42, T m43, T m44) :
			m11(m11), m12(m12), m13(m13), m14(m14),
			m21(m21), m22(m22), m23(m23), m24(m24),
			m31(m31), m32(m32), m33(m33), m34(m34),
			m41(m41), m42(m42), m43(m43), m44(m44) {}

		Matrix4(const Matrix4<T>& mat)
		{
			m11 = mat.m11;
			m12 = mat.m12;
			m13 = mat.m13;
			m14 = mat.m14;
			m21 = mat.m21;
			m22 = mat.m22;
			m23 = mat.m23;
			m24 = mat.m24;
			m31 = mat.m31;
			m32 = mat.m32;
			m33 = mat.m33;
			m34 = mat.m34;
			m41 = mat.m41;
			m42 = mat.m42;
			m43 = mat.m43;
			m44 = mat.m44;
		}

		Matrix4<T> operator+(const Matrix4<T>& mat)
		{
			Matrix4<T> newMat(*this);
			newMat.m11 += mat.m11;
			newMat.m12 += mat.m12;
			newMat.m13 += mat.m13;
			newMat.m14 += mat.m14;
			newMat.m21 += mat.m21;
			newMat.m22 += mat.m22;
			newMat.m23 += mat.m23;
			newMat.m24 += mat.m24;
			newMat.m31 += mat.m31;
			newMat.m32 += mat.m32;
			newMat.m33 += mat.m33;
			newMat.m34 += mat.m34;
			newMat.m41 += mat.m41;
			newMat.m42 += mat.m42;
			newMat.m43 += mat.m43;
			newMat.m44 += mat.m44;
			return newMat;
		}

		Matrix4<T> operator-(const Matrix4<T>& mat)
		{
			Matrix4<T> newMat(*this);
			newMat.m11 -= mat.m11;
			newMat.m12 -= mat.m12;
			newMat.m13 -= mat.m13;
			newMat.m14 -= mat.m14;
			newMat.m21 -= mat.m21;
			newMat.m22 -= mat.m22;
			newMat.m23 -= mat.m23;
			newMat.m24 -= mat.m24;
			newMat.m31 -= mat.m31;
			newMat.m32 -= mat.m32;
			newMat.m33 -= mat.m33;
			newMat.m34 -= mat.m34;
			newMat.m41 -= mat.m41;
			newMat.m42 -= mat.m42;
			newMat.m43 -= mat.m43;
			newMat.m44 -= mat.m44;
			return newMat;
		}

		Matrix4<T> operator*(T s)
		{
			Matrix4<T> newMat(*this);
			newMat.m11 *= s;
			newMat.m12 *= s;
			newMat.m13 *= s;
			newMat.m14 *= s;
			newMat.m21 *= s;
			newMat.m22 *= s;
			newMat.m23 *= s;
			newMat.m24 *= s;
			newMat.m31 *= s;
			newMat.m32 *= s;
			newMat.m33 *= s;
			newMat.m34 *= s;
			newMat.m41 *= s;
			newMat.m42 *= s;
			newMat.m43 *= s;
			newMat.m44 *= s;
			return newMat;
		}

		Matrix4<T> operator/(T s)
		{
			Matrix4<T> newMat(*this);
			newMat.m11 /= s;
			newMat.m12 /= s;
			newMat.m13 /= s;
			newMat.m14 /= s;
			newMat.m21 /= s;
			newMat.m22 /= s;
			newMat.m23 /= s;
			newMat.m24 /= s;
			newMat.m31 /= s;
			newMat.m32 /= s;
			newMat.m33 /= s;
			newMat.m34 /= s;
			newMat.m41 /= s;
			newMat.m42 /= s;
			newMat.m43 /= s;
			newMat.m44 /= s;
			return newMat;
		}

		Matrix4<T> transpose() const
		{
			Matrix4<T> mat(*this);
			mat.m12 = m21;
			mat.m13 = m31;
			mat.m14 = m41;
			mat.m21 = m12;
			mat.m23 = m32;
			mat.m24 = m42;
			mat.m31 = m13;
			mat.m32 = m23;
			mat.m34 = m43;
			mat.m41 = m14;
			mat.m42 = m24;
			mat.m43 = m34;
			return mat;
		}

		Matrix4<T> operator*(const Matrix4<T>& m) const
		{
			Matrix4<T> newMat(*this);

			newMat.m11 = Vec4<T>(m11, m12, m13, m14)*Vec4<T>(m.m11, m.m21, m.m31, m.m41);
			newMat.m12 = Vec4<T>(m11, m12, m13, m14)*Vec4<T>(m.m12, m.m22, m.m32, m.m42);
			newMat.m13 = Vec4<T>(m11, m12, m13, m14)*Vec4<T>(m.m13, m.m23, m.m33, m.m43);
			newMat.m14 = Vec4<T>(m11, m12, m13, m14)*Vec4<T>(m.m14, m.m24, m.m34, m.m44);

			newMat.m21 = Vec4<T>(m21, m22, m23, m24)*Vec4<T>(m.m11, m.m21, m.m31, m.m41);
			newMat.m22 = Vec4<T>(m21, m22, m23, m24)*Vec4<T>(m.m12, m.m22, m.m32, m.m42);
			newMat.m23 = Vec4<T>(m21, m22, m23, m24)*Vec4<T>(m.m13, m.m23, m.m33, m.m43);
			newMat.m24 = Vec4<T>(m21, m22, m23, m24)*Vec4<T>(m.m14, m.m24, m.m34, m.m44);

			newMat.m31 = Vec4<T>(m31, m32, m33, m34)*Vec4<T>(m.m11, m.m21, m.m31, m.m41);
			newMat.m32 = Vec4<T>(m31, m32, m33, m34)*Vec4<T>(m.m12, m.m22, m.m32, m.m42);
			newMat.m33 = Vec4<T>(m31, m32, m33, m34)*Vec4<T>(m.m13, m.m23, m.m33, m.m43);
			newMat.m34 = Vec4<T>(m31, m32, m33, m34)*Vec4<T>(m.m14, m.m24, m.m34, m.m44);

			newMat.m41 = Vec4<T>(m41, m42, m43, m44)*Vec4<T>(m.m11, m.m21, m.m31, m.m41);
			newMat.m42 = Vec4<T>(m41, m42, m43, m44)*Vec4<T>(m.m12, m.m22, m.m32, m.m42);
			newMat.m43 = Vec4<T>(m41, m42, m43, m44)*Vec4<T>(m.m13, m.m23, m.m33, m.m43);
			newMat.m44 = Vec4<T>(m41, m42, m43, m44)*Vec4<T>(m.m14, m.m24, m.m34, m.m44);

			return newMat;
		}

		T det() const
		{
			Matrix3<T> mat1(m22, m23, m24,
				m32, m33, m34,
				m42, m43, m44);

			Matrix3<T> mat2(m21, m23, m24,
				m31, m33, m34,
				m41, m43, m44);

			Matrix3<T> mat3(m21, m22, m24,
				m31, m32, m34,
				m41, m42, m44);

			Matrix3<T> mat4(m21, m22, m23,
				m31, m32, m33,
				m41, m42, m43);

			return m11 * mat1.det() - m12 * mat2.det() +
				m13 * mat3.det() - m14 * mat4.det();
		}

		Matrix4<T> minor() const
		{
			Matrix4<T> mat(*this);

			mat.m11 = Matrix3<T>(m22, m23, m24,
								  m32, m33, m34,
								  m42, m43, m44).det();
			mat.m12 = Matrix3<T>(m21, m23, m24,
								  m31, m33, m34,
								  m41, m43, m44).det();
			mat.m13 = Matrix3<T>(m21, m22, m24,
								  m31, m32, m34,
								  m41, m42, m44).det();
			mat.m14 = Matrix3<T>(m21, m22, m23,
								  m31, m32, m33,
								  m41, m42, m43).det();
			
			mat.m21 = Matrix3<T>(m12, m13, m14,
								  m32, m33, m34,
								  m42, m43, m44).det();
			mat.m22 = Matrix3<T>(m11, m13, m14,
								  m31, m33, m34,
								  m41, m43, m44).det();
			mat.m23 = Matrix3<T>(m11, m12, m14,
								  m31, m32, m34,
								  m41, m42, m44).det();
			mat.m24 = Matrix3<T>(m11, m12, m13,
								  m31, m32, m33,
								  m41, m42, m43).det();
			
			mat.m31 = Matrix3<T>(m12, m13, m14,
								  m22, m23, m24,
								  m42, m43, m44).det();
			mat.m32 = Matrix3<T>(m11, m13, m14,
								  m21, m23, m24,
								  m41, m43, m44).det();
			mat.m33 = Matrix3<T>(m11, m12, m14,
								  m21, m22, m24,
								  m41, m42, m44).det();
			mat.m34 = Matrix3<T>(m11, m12, m13,
								  m21, m22, m23,
								  m41, m42, m43).det();
			
			mat.m41 = Matrix3<T>(m12, m13, m14,
								  m22, m23, m24,
								  m32, m33, m34).det();
			mat.m42 = Matrix3<T>(m11, m13, m14,
								  m21, m23, m24,
								  m31, m33, m34).det();
			mat.m43 = Matrix3<T>(m11, m12, m14,
								  m21, m22, m24,
								  m31, m32, m34).det();
			mat.m44 = Matrix3<T>(m11, m12, m13,
								  m21, m22, m23,
								  m31, m32, m33).det();

			return mat;
		}

		Matrix4<T> cofactor() const
		{
			Matrix4<T> mat = minor();
			return Matrix4<T>(mat.m11, -mat.m12, mat.m13, -mat.m14,
							 -mat.m21, mat.m22, -mat.m23, mat.m24,
							 mat.m31, -mat.m32, mat.m33, mat.m34,
							 -mat.m41, mat.m42, -mat.m43, mat.m44);
		}

		Matrix4<T> adj() const
		{
			return Matrix4<T>(*this).cofactor().transpose();
		}

		Matrix4<T> inv() const
		{
			return adj() * (1 / det());
		}

		friend std::ostream& operator<<(std::ostream& out, const Matrix4<T>& m)
		{
			out << "[" << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " << m.m14 << "\n";
			out << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " << m.m24 << "\n";
			out << m.m31 << ", " << m.m32 << ", " << m.m33 << ", " << m.m34 << "\n";
			out << m.m41 << ", " << m.m42 << ", " << m.m43 << ", " << m.m44 << "]\n";
			return out;
		}

		static Matrix4<T> projectionMatrix(T w, T h, T zn, T zf, T fov) {
			return Matrix4((h/w)*1/ std::tan(fov/2), 0, 0, 0,
				            0, 1/ std::tan(fov/2), 0, 0,
				            0, 0, zf/(zf-zn), 1,
				            0, 0, -zf*zn/(zf-zn), 0);
		}

		static Matrix4<T> perspectiveMatrix(T w, T h, T zn, T zf, T fov) {
			return Matrix4((h / w) * 1 / std::tan(fov / 2), 0, 0, 0,
				0, 1 / std::tan(fov / 2), 0, 0,
				0, 0, -(zf + zn) / (zf - zn), -1,
				0, 0, -(2* zf * zn) / (zf - zn), 0);
		}

		static Matrix4<T> rotateMatrixX(T degree) {
			T rad = degree * M_PI / 180;
			return Matrix4(1, 0, 0,0,
				0, std::cos(rad), -std::sin(rad),0,
				0, std::sin(rad), std::cos(rad),0,
				0,0,0,1);
		}

		static Matrix4<T> rotateMatrixY(T degree) {
			T rad = degree * M_PI / 180;
			return Matrix4(std::cos(rad), 0, std::sin(rad), 0,
				0, 1, 0, 0,
				-std::sin(rad), 0, std::cos(rad), 0,
			0,0,0,1);
		}

		static Matrix4<T> rotateMatrixZ(T degree) {
			T rad = degree * M_PI / 180;
			return Matrix4(std::cos(rad), -std::sin(rad), 0,0,
				std::sin(rad), std::cos(rad), 0,0,
				0, 0, 1,0,
				0,0,0,1);
		}

		T m11;
		T m12;
		T m13;
		T m14;
		T m21;
		T m22;
		T m23;
		T m24;
		T m31;
		T m32;
		T m33;
		T m34;
		T m41;
		T m42;
		T m43;
		T m44;
	};

	template <typename T>
	class Quaternion {

	public:
		Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		Quaternion(const Quaternion<T>& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
		Quaternion(const Vec3<T>& v) // yaw (Z), pitch (Y), roll (X)
		{
			double cy = cos(v.z * 0.5);
			double sy = sin(v.z * 0.5);
			double cp = cos(v.y * 0.5);
			double sp = sin(v.y * 0.5);
			double cr = cos(v.x * 0.5);
			double sr = sin(v.x * 0.5);

			w = cy * cp * cr + sy * sp * sr;
			x = cy * cp * sr - sy * sp * cr;
			y = sy * cp * sr + cy * sp * cr;
			z = sy * cp * cr - cy * sp * sr;

		}
		Vec3<T> ToVec3(const Quaternion<T>& q) const
		{
			Vec3<T> vec(0,0,0);
			// roll (x-axis rotation)
			double sinr_cosp = +2.0 * (q.w * q.x + q.y * q.z);
			double cosr_cosp = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
			vec.x = atan2(sinr_cosp, cosr_cosp);

			// pitch (y-axis rotation)
			double sinp = +2.0 * (q.w * q.y - q.z * q.x);
			if (fabs(sinp) >= 1)
				vec.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
			else
				vec.y = asin(sinp);

			// yaw (z-axis rotation)
			double sinycosp = +2.0 * (q.w * q.z + q.x * q.y);
			double cosycosp = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
			vec.z = atan2(sinycosp, cosycosp);

			return vec;
		}

		Quaternion<T> operator+(const Quaternion<T>& q) const
		{
			Quaternion<T> qua(*this);
			qua.x += q.x;
			qua.y += q.y;
			qua.z += q.z;
			qua.w += q.w;

			return qua;
		}

		Quaternion<T> operator*(const Quaternion<T>& q) const
		{
			return Quaternion<T>(x * q.x - y * q.y - z * q.z - w * q.w,
				                 x * q.y + y * q.x + z * q.w - w * q.z,
				                 x * q.z - y * q.w + z * q.x + w * q.y,
				                 x * q.w + y * q.z - z * q.y + w * q.x);
		}

		Quaternion<T> inv() const
		{
			return Quaternion<T>(x, -y, -z, -w);
		}

		Vec3<T> rotate(const Vec3<T>& v) const
		{
			Quaternion<T> q(*this);
			Quaternion<T> q2(v);
			Quaternion<T> q3 = q * q2*inv();
			return ToVec3(q3);
		}

		friend std::ostream& operator<<(std::ostream& out, const Quaternion<T>& v)
		{
			out << "{" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "}\n";
			return out;
		}
		
		T x;
		T y;
		T z;
		T w;

	};


	template <typename T>
	Vec2<T> operator*(const Vec2<T>& v, const Matrix2<T>& m)
	{
		Vec2<T> newVec(v);
		newVec.x = Vec2<T>(m.m11, m.m21)*v;
		newVec.y = Vec2<T>(m.m12, m.m22)*v;

		return newVec;
	}

	template <typename T>
	Vec3<T> operator*(const Vec3<T>& v, const Matrix3<T>& m)
	{
		Vec3<T> newVec(v);
		newVec.x = Vec3<T>(m.m11, m.m21, m.m31)*v;
		newVec.y = Vec3<T>(m.m12, m.m22, m.m32)*v;
		newVec.z = Vec3<T>(m.m13, m.m23, m.m33)*v;

		return newVec;
	}

	template <typename T>
	Vec4<T> operator*(const Vec4<T>& v, const Matrix4<T>& m)
	{
		Vec4<T> newVec(v);
		
		newVec.x = Vec4<T>(m.m11, m.m21, m.m31, m.m41)*v;
		newVec.y = Vec4<T>(m.m12, m.m22, m.m32, m.m42)*v;
		newVec.z = Vec4<T>(m.m13, m.m23, m.m33, m.m43)*v;
		newVec.w = Vec4<T>(m.m14, m.m24, m.m34, m.m44)*v;

		return newVec;
	}

}

