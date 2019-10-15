#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>

namespace algebra
{
	template <typename T>
	class Vec2
	{
	public:
		Vec2(T x, T y) : x_(x), y_(y) {}
		bool operator==(const Vec2<T>& vec) const
		{
			return (x_ == vec.x_ && y_ == vec.y_);
		}
		bool operator!=(const Vec2<T>& vec) const
		{
			return (x_ != vec.x_ || y_ != vec.y_);
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
			x_ = vec.x_;
			y_ = vec.y_;
			return *this;
		}
		Vec2<T> operator+(T s) const
		{
			Vec2<T> vec(x_, y_);
			vec += s;
			return vec;
		}
		Vec2<T> operator-(T s) const
		{
			Vec2<T> vec(x_, y_);
			vec -= s;
			return vec;
		}
		Vec2<T> operator*(T s) const
		{
			Vec2<T> vec(x_, y_);
			vec *= s;
			return vec;
		}
		Vec2<T> operator/(T s) const
		{
			Vec2<T> vec(x_, y_);
			vec /= s;
			return vec;
		}
		Vec2<T> operator+=(T s)
		{
			x_ += s;
			y_ += s;
			return *this;
		}
		Vec2<T> operator-=(T s)
		{
			x_ -= s;
			y_ -= s;
			return *this;
		}
		Vec2<T> operator*=(T s)
		{
			x_ *= s;
			y_ *= s;
			return *this;
		}
		Vec2<T> operator/=(T s)
		{
			x_ /= s;
			y_ /= s;
			return *this;
		}
		Vec2<T> operator+(const Vec2<T>& vec) const
		{
			Vec2<T> v(x_, y_);
			v.x_ += vec.x_;
			v.y_ += vec.y_;
			return v;
		}
		Vec2<T> operator-(const Vec2<T>& vec) const
		{
			Vec2<T> v(x_, y_);
			v.x_ -= vec.x_;
			v.y_ -= vec.y_;
			return v;
		}
		T operator*(const Vec2<T>& vec) const
		{
			return x_ * vec.x_ + y_ * vec.y_;
		}


		T length() const
		{
			return std::sqrt(double_length());
		}

		T double_length() const
		{
			return x_ * x_ + y_ * y_;
		}

		Vec2<T> normalize() const
		{
			Vec2<T> n(x_, y_);
			const T len = length();
			n.x_ /= len;
			n.y_ /= len;
			return n;
		}

		friend std::ostream& operator<<(std::ostream& out, const Vec2<T>& v)
		{
			out << "{" << v.x_ << ", " << v.y_ << "}\n";
			return out;
		}
		T x_;
		T y_;
	};

	template <typename T>
	class Vec3
	{
	public:
		Vec3() : x_(0), y_(0), z_(0) {}
		Vec3(T x, T y, T z) : x_(x), y_(y), z_(z) {}
		Vec3(const Vec3<T>& v) : x_(v.x_), y_(v.y_), z_(v.z_) {}

		bool operator==(const Vec3<T>& vec) const
		{
			return (x_ == vec.x_ && y_ == vec.y_ &&
				z_ == vec.z_);
		}
		bool operator!=(const Vec3<T>& vec) const
		{
			return (x_ != vec.x_ || y_ != vec.y_ ||
				z_ != vec.z_);
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
			x_ = vec.x_;
			y_ = vec.y_;
			z_ = vec.z_;
			return *this;
		}
		Vec3<T> operator+(T s) const
		{
			Vec3<T> vec(x_, y_, z_);
			vec += s;
			return vec;
		}

		Vec3<T> operator-(T s) const
		{
			Vec3<T> vec(x_, y_, z_);
			vec -= s;
			return vec;
		}

		Vec3<T> operator*(T s) const
		{
			Vec3<T> vec(x_, y_, z_);
			vec *= s;
			return vec;
		}
		Vec3<T> operator/(T s) const
		{
			Vec3<T> vec(x_, y_, z_);
			vec /= s;
			return vec;
		}
		Vec3<T> operator+=(T s)
		{
			x_ += s;
			y_ += s;
			z_ += s;
			return *this;
		}
		Vec3<T> operator-=(T s)
		{
			x_ -= s;
			y_ -= s;
			z_ -= s;
			return *this;
		}
		Vec3<T> operator*=(T s)
		{
			x_ *= s;
			y_ *= s;
			z_ *= s;
			return *this;
		}
		Vec3<T> operator/=(T s)
		{
			x_ /= s;
			y_ /= s;
			z_ /= s;
			return *this;
		}
		Vec3<T> operator+(const Vec3<T>& vec) const
		{
			Vec3<T> v(x_, y_, z_);
			v.x_ += vec.x_;
			v.y_ += vec.y_;
			v.z_ += vec.z_;
			return v;
		}
		Vec3<T> operator-(const Vec3<T>& vec) const
		{
			Vec3<T> v(x_, y_, z_);
			v.x_ -= vec.x_;
			v.y_ -= vec.y_;
			v.z_ -= vec.z_;
			return v;
		}
		T operator*(const Vec3<T>& vec) const
		{
			return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_;
		}
		Vec3<T> operator^(const Vec3<T>& vec) const
		{
			return Vec3<T>(
				y_ * vec.z_ - z_ * vec.y_,
				z_ * vec.x_ - x_ * vec.z_,
				x_ * vec.y_ - y_ * vec.x_);
		}


		T length() const
		{
			return std::sqrt(double_length());
		}

		T double_length() const
		{
			return x_ * x_ + y_ * y_ + z_ * z_;
		}

		Vec3<T> normalize() const
		{
			Vec3<T> n(x_, y_, z_);
			const T len = length();
			n.x_ /= len;
			n.y_ /= len;
			n.z_ /= len;
			return n;
		}

		friend std::ostream& operator<<(std::ostream& out, const Vec3<T>& v)
		{
			out << "{" << v.x_ << ", " << v.y_ << ", " << v.z_ << "}\n";
			return out;
		}

		T x_;
		T y_;
		T z_;
	};


	template <typename T>
	class Vec4
	{
	public:
		Vec4(T x, T y, T z, T w) : x_(x), y_(y), z_(z), w_(w) {}
		Vec4(const Vec3<T>& v) : x_(v.x_), y_(v.y_), z_(v.z_), w_(1) {}
		bool operator==(const Vec4<T>& vec) const
		{
			return (x_ == vec.x_ && y_ == vec.y_ &&
				z_ == vec.z_ && w_ == vec.w_);
		}
		bool operator!=(const Vec4<T>& vec) const
		{
			return (x_ != vec.x_ || y_ != vec.y_ ||
				z_ != vec.z_ || w_ != vec.w_);
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
			x_ = vec.x_;
			y_ = vec.y_;
			z_ = vec.z_;
			w_ = vec.w_;
			return *this;
		}
		Vec4<T> operator+(T s) const
		{
			Vec4<T> vec(x_, y_, z_, w_);
			vec += s;
			return vec;
		}
		Vec4<T> operator-(T s) const
		{
			Vec4<T> vec(x_, y_, z_, w_);
			vec -= s;
			return vec;
		}
		Vec4<T> operator*(T s) const
		{
			Vec4<T> vec(x_, y_, z_, w_);
			vec *= s;
			return vec;
		}
		Vec4<T> operator/(T s) const
		{
			Vec4<T> vec(x_, y_, z_, w_);
			vec /= s;
			return vec;
		}
		Vec4<T> operator+=(T s)
		{
			x_ += s;
			y_ += s;
			z_ += s;
			w_ += s;
			return *this;
		}
		Vec4<T> operator-=(T s)
		{
			x_ -= s;
			y_ -= s;
			z_ -= s;
			w_ -= s;
			return *this;
		}
		Vec4<T> operator*=(T s)
		{
			x_ *= s;
			y_ *= s;
			z_ *= s;
			w_ *= s;
			return *this;
		}
		Vec4<T> operator/=(T s)
		{
			x_ /= s;
			y_ /= s;
			z_ /= s;
			w_ /= s;
			return *this;
		}
		Vec4<T> operator+(const Vec4<T>& vec) const
		{
			Vec4<T> v(x_, y_, z_, w_);
			v.x_ += vec.x_;
			v.y_ += vec.y_;
			v.z_ += vec.z_;
			v.w_ += vec.w_;
			return v;
		}
		Vec4<T> operator-(const Vec4<T>& vec) const
		{
			Vec4<T> v(x_, y_, z_, w_);
			v.x_ -= vec.x_;
			v.y_ -= vec.y_;
			v.z_ -= vec.z_;
			v.w_ -= vec.w_;
			return v;
		}
		T operator*(const Vec4<T>& vec) const
		{
			return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_ + w_ * vec.w_;
		}

		T length() const 
		{
			return std::sqrt(double_length());
		}

		T double_length() const
		{
			return x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
		}

		Vec4<T> normalize() const
		{
			Vec4<T> n(x_, y_, z_, w_);
			const T len = length();
			n.x_ /= len;
			n.y_ /= len;
			n.z_ /= len;
			n.w_ /= len;
			return n;
		}


		friend std::ostream& operator<<(std::ostream& out, const Vec4<T>& v)
		{
			out << "{" << v.x_ << ", " << v.y_ << ", " << v.z_ << ", " << v.w_ << "}\n";
			return out;
		}

		T x_;
		T y_;
		T z_;
		T w_;
	};

	

	template <typename T>
	class Matrix2
	{
	public:
		Matrix2(T m11, T m12, T m21, T m22) : m11_(m11), m12_(m12), m21_(m21), m22_(m22){}
		Matrix2(const Matrix2<T>& mat) 
		{
			m11_ = mat.m11_;
			m12_ = mat.m12_;
			m21_ = mat.m21_;
			m22_ = mat.m22_;
		}

		Matrix2<T> operator+(const Matrix2<T>& mat)
		{
			Matrix2<T> newMat(*this);
			newMat.m11_ += mat.m11_;
			newMat.m12_ += mat.m12_;
			newMat.m21_ += mat.m21_;
			newMat.m22_ += mat.m22_;
			return newMat;
		}
		Matrix2<T> operator-(const Matrix2<T>& mat)
		{
			Matrix2<T> newMat(*this);
			newMat.m11_ -= mat.m11_;
			newMat.m12_ -= mat.m12_;
			newMat.m21_ -= mat.m21_;
			newMat.m22_ -= mat.m22_;
			return newMat;
		}
		Matrix2<T> operator*(T s)
		{
			Matrix2<T> newMat(*this);
			newMat.m11_ *= s;
			newMat.m12_ *= s;
			newMat.m21_ *= s;
			newMat.m22_ *= s;
			return newMat;
		}
		Matrix2<T> operator/(T s)
		{
			Matrix2<T> newMat(*this);
			newMat.m11_ /= s;
			newMat.m12_ /= s;
			newMat.m21_ /= s;
			newMat.m22_ /= s;
			return newMat;
		}
		Matrix2<T> transpose() const
		{
			Matrix2<T> mat(*this);
			mat.m12_ = m21_;
			mat.m21_ = m12_;
			return mat;
		}
		Matrix2<T> operator*(const Matrix2<T>& m) const 
		{
			Matrix2<T> newMat(*this);
			newMat.m11_ = Vec2<T>(m11_, m12_)*Vec2<T>(m.m11_, m.m21_);
			newMat.m12_ = Vec2<T>(m11_, m12_)*Vec2<T>(m.m12_, m.m22_);
			newMat.m21_ = Vec2<T>(m21_, m22_)*Vec2<T>(m.m11_, m.m21_);
			newMat.m22_ = Vec2<T>(m21_, m22_)*Vec2<T>(m.m12_, m.m22_);

			return newMat;
		}
		T det() const
		{
			return m11_ * m22_ - m12_ * m21_;
		}

		Matrix2<T> minor() const
		{
			Matrix2<T> mat(*this);
			mat.m11_ = m22_;
			mat.m12_ = m21_;
			mat.m21_ = m12_;
			mat.m22_ = m11_;

			return mat;
		}

		Matrix2<T> cofactor() const
		{
			Matrix2<T> mat = minor();
			return Matrix2<T>(mat.m11_, -mat.m12_,
						      -mat.m21_, mat.m22_);
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
			out << "[" << m.m11_ << ", " << m.m12_ << "\n";
			out << m.m21_ << ", " << m.m22_ << "]\n";
			return out;
		}

		T m11_;
		T m12_;
		T m21_;
		T m22_;
	};


	template <typename T>
	class Matrix3
	{
	public:
		Matrix3(T m11, T m12, T m13,
			T m21, T m22, T m23,
			T m31, T m32, T m33) :
			m11_(m11), m12_(m12), m13_(m13),
			m21_(m21), m22_(m22), m23_(m23),
			m31_(m31), m32_(m32), m33_(m33) {}

		Matrix3(const Matrix3<T>& mat)
		{
			m11_ = mat.m11_;
			m12_ = mat.m12_;
			m13_ = mat.m13_;
			m21_ = mat.m21_;
			m22_ = mat.m22_;
			m23_ = mat.m23_;
			m31_ = mat.m31_;
			m32_ = mat.m32_;
			m33_ = mat.m33_;
		}

		Matrix3<T> operator+(const Matrix3<T>& mat)
		{
			Matrix3<T> newMat(*this);
			newMat.m11_ += mat.m11_;
			newMat.m12_ += mat.m12_;
			newMat.m13_ += mat.m13_;
			newMat.m21_ += mat.m21_;
			newMat.m22_ += mat.m22_;
			newMat.m23_ += mat.m23_;
			newMat.m31_ += mat.m31_;
			newMat.m32_ += mat.m32_;
			newMat.m33_ += mat.m33_;
			return newMat;
		}
		Matrix3<T> operator-(const Matrix3<T>& mat)
		{
			Matrix3<T> newMat(*this);
			newMat.m11_ -= mat.m11_;
			newMat.m12_ -= mat.m12_;
			newMat.m13_ -= mat.m13_;
			newMat.m21_ -= mat.m21_;
			newMat.m22_ -= mat.m22_;
			newMat.m23_ -= mat.m23_;
			newMat.m31_ -= mat.m31_;
			newMat.m32_ -= mat.m32_;
			newMat.m33_ -= mat.m33_;
			return newMat;
		}

		Matrix3<T> operator*(T s)
		{
			Matrix3<T> newMat(*this);
			newMat.m11_ *= s;
			newMat.m12_ *= s;
			newMat.m13_ *= s;
			newMat.m21_ *= s;
			newMat.m22_ *= s;
			newMat.m23_ *= s;
			newMat.m31_ *= s;
			newMat.m32_ *= s;
			newMat.m33_ *= s;
			return newMat;
		}

		Matrix3<T> operator/(T s)
		{
			Matrix3<T> newMat(*this);
			newMat.m11_ /= s;
			newMat.m12_ /= s;
			newMat.m13_ /= s;
			newMat.m21_ /= s;
			newMat.m22_ /= s;
			newMat.m23_ /= s;
			newMat.m31_ /= s;
			newMat.m32_ /= s;
			newMat.m33_ /= s;
			return newMat;
		}

		Matrix3<T> transpose() const
		{
			Matrix3<T> mat(*this);
			mat.m12_ = m21_;
			mat.m13_ = m31_;
			mat.m21_ = m12_;
			mat.m23_ = m32_;
			mat.m31_ = m13_;
			mat.m32_ = m23_;
			return mat;
		}

		Matrix3<T> operator*(const Matrix3<T>& m) const
		{
			Matrix3<T> newMat(*this);
			newMat.m11_ = Vec3<T>(m11_, m12_, m13_)*Vec3<T>(m.m11_, m.m21_, m.m31_);
			newMat.m12_ = Vec3<T>(m11_, m12_, m13_)*Vec3<T>(m.m12_, m.m22_, m.m32_);
			newMat.m13_ = Vec3<T>(m11_, m12_, m13_)*Vec3<T>(m.m13_, m.m23_, m.m33_);

			newMat.m21_ = Vec3<T>(m21_, m22_, m23_)*Vec3<T>(m.m11_, m.m21_, m.m31_);
			newMat.m22_ = Vec3<T>(m21_, m22_, m23_)*Vec3<T>(m.m12_, m.m22_, m.m32_);
			newMat.m23_ = Vec3<T>(m21_, m22_, m23_)*Vec3<T>(m.m13_, m.m23_, m.m33_);

			newMat.m31_ = Vec3<T>(m31_, m32_, m33_)*Vec3<T>(m.m11_, m.m21_, m.m31_);
			newMat.m32_ = Vec3<T>(m31_, m32_, m33_)*Vec3<T>(m.m12_, m.m22_, m.m32_);
			newMat.m33_ = Vec3<T>(m31_, m32_, m33_)*Vec3<T>(m.m13_, m.m23_, m.m33_);

			return newMat;
		}

		T det() const
		{
			Matrix2<T> mat1 (m22_, m23_, m32_, m33_);
			Matrix2<T> mat2 (m21_, m23_, m31_, m33_);
			Matrix2<T> mat3 (m21_, m22_, m31_, m32_);

			return m11_ * mat1.det() -
				   m12_ * mat2.det() +
				   m13_ * mat3.det();
		}

		Matrix3<T> minor() const
		{
			Matrix3<T> mat(*this);
			mat.m11_ = Matrix2<T>(m22_, m23_, m32_, m33_).det();
			mat.m12_ = Matrix2<T>(m21_, m23_, m31_, m33_).det();
			mat.m13_ = Matrix2<T>(m21_, m22_, m31_, m32_).det();

			mat.m21_ = Matrix2<T>(m12_, m13_, m32_, m33_).det();
			mat.m22_ = Matrix2<T>(m11_, m13_, m31_, m33_).det();
			mat.m23_ = Matrix2<T>(m11_, m12_, m31_, m32_).det();

			mat.m31_ = Matrix2<T>(m12_, m13_, m22_, m23_).det();
			mat.m32_ = Matrix2<T>(m11_, m13_, m21_, m23_).det();
			mat.m33_ = Matrix2<T>(m11_, m12_, m21_, m22_).det();

			return mat;
		}

		Matrix3<T> cofactor() const
		{
			Matrix3<T> mat = minor();
			return Matrix3<T>(mat.m11_, -mat.m12_, mat.m13_,
							  -mat.m21_, mat.m22_, -mat.m23_,
							  mat.m31_, -mat.m32_, mat.m33_);
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
			out << "[" << m.m11_ << ", " << m.m12_ << ", " << m.m13_ << "\n";
			out << m.m21_ << ", " << m.m22_ << ", " << m.m23_ << "\n";
			out << m.m31_ << ", " << m.m32_ << ", " << m.m33_ << "]\n";
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

		T m11_;
		T m12_;
		T m13_;
		T m21_;
		T m22_;
		T m23_;
		T m31_;
		T m32_;
		T m33_;

	};

	template <typename T>
	class Matrix4
	{
	public:
		Matrix4(T m11, T m12, T m13, T m14,
			T m21, T m22, T m23, T m24,
			T m31, T m32, T m33, T m34,
			T m41, T m42, T m43, T m44) :
			m11_(m11), m12_(m12), m13_(m13), m14_(m14),
			m21_(m21), m22_(m22), m23_(m23), m24_(m24),
			m31_(m31), m32_(m32), m33_(m33), m34_(m34),
			m41_(m41), m42_(m42), m43_(m43), m44_(m44) {}

		Matrix4(const Matrix4<T>& mat)
		{
			m11_ = mat.m11_;
			m12_ = mat.m12_;
			m13_ = mat.m13_;
			m14_ = mat.m14_;
			m21_ = mat.m21_;
			m22_ = mat.m22_;
			m23_ = mat.m23_;
			m24_ = mat.m24_;
			m31_ = mat.m31_;
			m32_ = mat.m32_;
			m33_ = mat.m33_;
			m34_ = mat.m34_;
			m41_ = mat.m41_;
			m42_ = mat.m42_;
			m43_ = mat.m43_;
			m44_ = mat.m44_;
		}

		Matrix4<T> operator+(const Matrix4<T>& mat)
		{
			Matrix4<T> newMat(*this);
			newMat.m11_ += mat.m11_;
			newMat.m12_ += mat.m12_;
			newMat.m13_ += mat.m13_;
			newMat.m14_ += mat.m14_;
			newMat.m21_ += mat.m21_;
			newMat.m22_ += mat.m22_;
			newMat.m23_ += mat.m23_;
			newMat.m24_ += mat.m24_;
			newMat.m31_ += mat.m31_;
			newMat.m32_ += mat.m32_;
			newMat.m33_ += mat.m33_;
			newMat.m34_ += mat.m34_;
			newMat.m41_ += mat.m41_;
			newMat.m42_ += mat.m42_;
			newMat.m43_ += mat.m43_;
			newMat.m44_ += mat.m44_;
			return newMat;
		}

		Matrix4<T> operator-(const Matrix4<T>& mat)
		{
			Matrix4<T> newMat(*this);
			newMat.m11_ -= mat.m11_;
			newMat.m12_ -= mat.m12_;
			newMat.m13_ -= mat.m13_;
			newMat.m14_ -= mat.m14_;
			newMat.m21_ -= mat.m21_;
			newMat.m22_ -= mat.m22_;
			newMat.m23_ -= mat.m23_;
			newMat.m24_ -= mat.m24_;
			newMat.m31_ -= mat.m31_;
			newMat.m32_ -= mat.m32_;
			newMat.m33_ -= mat.m33_;
			newMat.m34_ -= mat.m34_;
			newMat.m41_ -= mat.m41_;
			newMat.m42_ -= mat.m42_;
			newMat.m43_ -= mat.m43_;
			newMat.m44_ -= mat.m44_;
			return newMat;
		}

		Matrix4<T> operator*(T s)
		{
			Matrix4<T> newMat(*this);
			newMat.m11_ *= s;
			newMat.m12_ *= s;
			newMat.m13_ *= s;
			newMat.m14_ *= s;
			newMat.m21_ *= s;
			newMat.m22_ *= s;
			newMat.m23_ *= s;
			newMat.m24_ *= s;
			newMat.m31_ *= s;
			newMat.m32_ *= s;
			newMat.m33_ *= s;
			newMat.m34_ *= s;
			newMat.m41_ *= s;
			newMat.m42_ *= s;
			newMat.m43_ *= s;
			newMat.m44_ *= s;
			return newMat;
		}

		Matrix4<T> operator/(T s)
		{
			Matrix4<T> newMat(*this);
			newMat.m11_ /= s;
			newMat.m12_ /= s;
			newMat.m13_ /= s;
			newMat.m14_ /= s;
			newMat.m21_ /= s;
			newMat.m22_ /= s;
			newMat.m23_ /= s;
			newMat.m24_ /= s;
			newMat.m31_ /= s;
			newMat.m32_ /= s;
			newMat.m33_ /= s;
			newMat.m34_ /= s;
			newMat.m41_ /= s;
			newMat.m42_ /= s;
			newMat.m43_ /= s;
			newMat.m44_ /= s;
			return newMat;
		}

		Matrix4<T> transpose() const
		{
			Matrix4<T> mat(*this);
			mat.m12_ = m21_;
			mat.m13_ = m31_;
			mat.m14_ = m41_;
			mat.m21_ = m12_;
			mat.m23_ = m32_;
			mat.m24_ = m42_;
			mat.m31_ = m13_;
			mat.m32_ = m23_;
			mat.m34_ = m43_;
			mat.m41_ = m14_;
			mat.m42_ = m24_;
			mat.m43_ = m34_;
			return mat;
		}

		Matrix4<T> operator*(const Matrix4<T>& m) const
		{
			Matrix4<T> newMat(*this);

			newMat.m11_ = Vec4<T>(m11_, m12_, m13_, m14_)*Vec4<T>(m.m11_, m.m21_, m.m31_, m.m41_);
			newMat.m12_ = Vec4<T>(m11_, m12_, m13_, m14_)*Vec4<T>(m.m12_, m.m22_, m.m32_, m.m42_);
			newMat.m13_ = Vec4<T>(m11_, m12_, m13_, m14_)*Vec4<T>(m.m13_, m.m23_, m.m33_, m.m43_);
			newMat.m14_ = Vec4<T>(m11_, m12_, m13_, m14_)*Vec4<T>(m.m14_, m.m24_, m.m34_, m.m44_);

			newMat.m21_ = Vec4<T>(m21_, m22_, m23_, m24_)*Vec4<T>(m.m11_, m.m21_, m.m31_, m.m41_);
			newMat.m22_ = Vec4<T>(m21_, m22_, m23_, m24_)*Vec4<T>(m.m12_, m.m22_, m.m32_, m.m42_);
			newMat.m23_ = Vec4<T>(m21_, m22_, m23_, m24_)*Vec4<T>(m.m13_, m.m23_, m.m33_, m.m43_);
			newMat.m24_ = Vec4<T>(m21_, m22_, m23_, m24_)*Vec4<T>(m.m14_, m.m24_, m.m34_, m.m44_);

			newMat.m31_ = Vec4<T>(m31_, m32_, m33_, m34_)*Vec4<T>(m.m11_, m.m21_, m.m31_, m.m41_);
			newMat.m32_ = Vec4<T>(m31_, m32_, m33_, m34_)*Vec4<T>(m.m12_, m.m22_, m.m32_, m.m42_);
			newMat.m33_ = Vec4<T>(m31_, m32_, m33_, m34_)*Vec4<T>(m.m13_, m.m23_, m.m33_, m.m43_);
			newMat.m34_ = Vec4<T>(m31_, m32_, m33_, m34_)*Vec4<T>(m.m14_, m.m24_, m.m34_, m.m44_);

			newMat.m41_ = Vec4<T>(m41_, m42_, m43_, m44_)*Vec4<T>(m.m11_, m.m21_, m.m31_, m.m41_);
			newMat.m42_ = Vec4<T>(m41_, m42_, m43_, m44_)*Vec4<T>(m.m12_, m.m22_, m.m32_, m.m42_);
			newMat.m43_ = Vec4<T>(m41_, m42_, m43_, m44_)*Vec4<T>(m.m13_, m.m23_, m.m33_, m.m43_);
			newMat.m44_ = Vec4<T>(m41_, m42_, m43_, m44_)*Vec4<T>(m.m14_, m.m24_, m.m34_, m.m44_);

			return newMat;
		}

		T det() const
		{
			Matrix3<T> mat1(m22_, m23_, m24_,
				m32_, m33_, m34_,
				m42_, m43_, m44_);

			Matrix3<T> mat2(m21_, m23_, m24_,
				m31_, m33_, m34_,
				m41_, m43_, m44_);

			Matrix3<T> mat3(m21_, m22_, m24_,
				m31_, m32_, m34_,
				m41_, m42_, m44_);

			Matrix3<T> mat4(m21_, m22_, m23_,
				m31_, m32_, m33_,
				m41_, m42_, m43_);

			return m11_ * mat1.det() - m12_ * mat2.det() +
				m13_ * mat3.det() - m14_ * mat4.det();
		}

		Matrix4<T> minor() const
		{
			Matrix4<T> mat(*this);

			mat.m11_ = Matrix3<T>(m22_, m23_, m24_,
								  m32_, m33_, m34_,
								  m42_, m43_, m44_).det();
			mat.m12_ = Matrix3<T>(m21_, m23_, m24_,
								  m31_, m33_, m34_,
								  m41_, m43_, m44_).det();
			mat.m13_ = Matrix3<T>(m21_, m22_, m24_,
								  m31_, m32_, m34_,
								  m41_, m42_, m44_).det();
			mat.m14_ = Matrix3<T>(m21_, m22_, m23_,
								  m31_, m32_, m33_,
								  m41_, m42_, m43_).det();
			
			mat.m21_ = Matrix3<T>(m12_, m13_, m14_,
								  m32_, m33_, m34_,
								  m42_, m43_, m44_).det();
			mat.m22_ = Matrix3<T>(m11_, m13_, m14_,
								  m31_, m33_, m34_,
								  m41_, m43_, m44_).det();
			mat.m23_ = Matrix3<T>(m11_, m12_, m14_,
								  m31_, m32_, m34_,
								  m41_, m42_, m44_).det();
			mat.m24_ = Matrix3<T>(m11_, m12_, m13_,
								  m31_, m32_, m33_,
								  m41_, m42_, m43_).det();
			
			mat.m31_ = Matrix3<T>(m12_, m13_, m14_,
								  m22_, m23_, m24_,
								  m42_, m43_, m44_).det();
			mat.m32_ = Matrix3<T>(m11_, m13_, m14_,
								  m21_, m23_, m24_,
								  m41_, m43_, m44_).det();
			mat.m33_ = Matrix3<T>(m11_, m12_, m14_,
								  m21_, m22_, m24_,
								  m41_, m42_, m44_).det();
			mat.m34_ = Matrix3<T>(m11_, m12_, m13_,
								  m21_, m22_, m23_,
								  m41_, m42_, m43_).det();
			
			mat.m41_ = Matrix3<T>(m12_, m13_, m14_,
								  m22_, m23_, m24_,
								  m32_, m33_, m34_).det();
			mat.m42_ = Matrix3<T>(m11_, m13_, m14_,
								  m21_, m23_, m24_,
								  m31_, m33_, m34_).det();
			mat.m43_ = Matrix3<T>(m11_, m12_, m14_,
								  m21_, m22_, m24_,
								  m31_, m32_, m34_).det();
			mat.m44_ = Matrix3<T>(m11_, m12_, m13_,
								  m21_, m22_, m23_,
								  m31_, m32_, m33_).det();

			return mat;
		}

		Matrix4<T> cofactor() const
		{
			Matrix4<T> mat = minor();
			return Matrix4<T>(mat.m11_, -mat.m12_, mat.m13_, -mat.m14_,
							 -mat.m21_, mat.m22_, -mat.m23_, mat.m24_,
							 mat.m31_, -mat.m32_, mat.m33_, mat.m34_,
							 -mat.m41_, mat.m42_, -mat.m43_, mat.m44_);
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
			out << "[" << m.m11_ << ", " << m.m12_ << ", " << m.m13_ << ", " << m.m14_ << "\n";
			out << m.m21_ << ", " << m.m22_ << ", " << m.m23_ << ", " << m.m24_ << "\n";
			out << m.m31_ << ", " << m.m32_ << ", " << m.m33_ << ", " << m.m34_ << "\n";
			out << m.m41_ << ", " << m.m42_ << ", " << m.m43_ << ", " << m.m44_ << "]\n";
			return out;
		}

		static Matrix4<T> projectionMatrix(T w, T h, T zn, T zf, T fov) {
			return Matrix4((h/w)*1/ std::tan(fov/2), 0, 0, 0,
				            0, 1/ std::tan(fov/2), 0, 0,
				            0, 0, zf/(zf-zn), 1,
				            0, 0, -zf*zn/(zf-zn), 0);
		}

		T m11_;
		T m12_;
		T m13_;
		T m14_;
		T m21_;
		T m22_;
		T m23_;
		T m24_;
		T m31_;
		T m32_;
		T m33_;
		T m34_;
		T m41_;
		T m42_;
		T m43_;
		T m44_;
	};

	template <typename T>
	class Quaternion {

	public:
		Quaternion(T x, T y, T z, T w) : x_(x), y_(y), z_(z), w_(w) {}
		Quaternion(const Quaternion<T>& q) : x_(q.x_), y_(q.y_), z_(q.z_), w_(q.w_) {}
		Quaternion(const Vec3<T>& v) // yaw (Z), pitch (Y), roll (X)
		{
			double cy = cos(v.z_ * 0.5);
			double sy = sin(v.z_ * 0.5);
			double cp = cos(v.y_ * 0.5);
			double sp = sin(v.y_ * 0.5);
			double cr = cos(v.x_ * 0.5);
			double sr = sin(v.x_ * 0.5);

			w_ = cy * cp * cr + sy * sp * sr;
			x_ = cy * cp * sr - sy * sp * cr;
			y_ = sy * cp * sr + cy * sp * cr;
			z_ = sy * cp * cr - cy * sp * sr;

		}
		Vec3<T> ToVec3(const Quaternion<T>& q) const
		{
			Vec3<T> vec(0,0,0);
			// roll (x-axis rotation)
			double sinr_cosp = +2.0 * (q.w_ * q.x_ + q.y_ * q.z_);
			double cosr_cosp = +1.0 - 2.0 * (q.x_ * q.x_ + q.y_ * q.y_);
			vec.x_ = atan2(sinr_cosp, cosr_cosp);

			// pitch (y-axis rotation)
			double sinp = +2.0 * (q.w_ * q.y_ - q.z_ * q.x_);
			if (fabs(sinp) >= 1)
				vec.y_ = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
			else
				vec.y_ = asin(sinp);

			// yaw (z-axis rotation)
			double siny_cosp = +2.0 * (q.w_ * q.z_ + q.x_ * q.y_);
			double cosy_cosp = +1.0 - 2.0 * (q.y_ * q.y_ + q.z_ * q.z_);
			vec.z_ = atan2(siny_cosp, cosy_cosp);

			return vec;
		}

		Quaternion<T> operator+(const Quaternion<T>& q) const
		{
			Quaternion<T> qua(*this);
			qua.x_ += q.x_;
			qua.y_ += q.y_;
			qua.z_ += q.z_;
			qua.w_ += q.w_;

			return qua;
		}

		Quaternion<T> operator*(const Quaternion<T>& q) const
		{
			return Quaternion<T>(x_ * q.x_ - y_ * q.y_ - z_ * q.z_ - w_ * q.w_,
				                 x_ * q.y_ + y_ * q.x_ + z_ * q.w_ - w_ * q.z_,
				                 x_ * q.z_ - y_ * q.w_ + z_ * q.x_ + w_ * q.y_,
				                 x_ * q.w_ + y_ * q.z_ - z_ * q.y_ + w_ * q.x_);
		}

		Quaternion<T> inv() const
		{
			return Quaternion<T>(x_, -y_, -z_, -w_);
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
			out << "{" << v.x_ << ", " << v.y_ << ", " << v.z_ << ", " << v.w_ << "}\n";
			return out;
		}
		
		T x_;
		T y_;
		T z_;
		T w_;

	};


	template <typename T>
	Vec2<T> operator*(const Vec2<T>& v, const Matrix2<T>& m)
	{
		Vec2<T> newVec(v);
		newVec.x_ = Vec2<T>(m.m11_, m.m21_)*v;
		newVec.y_ = Vec2<T>(m.m12_, m.m22_)*v;

		return newVec;
	}

	template <typename T>
	Vec3<T> operator*(const Vec3<T>& v, const Matrix3<T>& m)
	{
		Vec3<T> newVec(v);
		newVec.x_ = Vec3<T>(m.m11_, m.m21_, m.m31_)*v;
		newVec.y_ = Vec3<T>(m.m12_, m.m22_, m.m32_)*v;
		newVec.z_ = Vec3<T>(m.m13_, m.m23_, m.m33_)*v;

		return newVec;
	}

	template <typename T>
	Vec4<T> operator*(const Vec4<T>& v, const Matrix4<T>& m)
	{
		Vec4<T> newVec(v);
		
		newVec.x_ = Vec4<T>(m.m11_, m.m21_, m.m31_, m.m41_)*v;
		newVec.y_ = Vec4<T>(m.m12_, m.m22_, m.m32_, m.m42_)*v;
		newVec.z_ = Vec4<T>(m.m13_, m.m23_, m.m33_, m.m43_)*v;
		newVec.w_ = Vec4<T>(m.m14_, m.m24_, m.m34_, m.m44_)*v;

		return newVec;
	}

}

