#pragma once
#include <AcidLib/Math/Math.hpp>
#include <AcidLib/Exception/IndexOutOfBoundsException.hpp>

namespace ac {

	template <typename T>
	class Vector2 {
	public:

		T x;
		T y;

		Vector2();

		Vector2(T p_x, T p_y);

		template <typename U>
		Vector2(Vector2<U> other);

		T& operator[](int index);

		const T& operator[](int index) const;
	};

	template <typename T>
	class Vector3 {
	public:

		T x;
		T y;
		T z;

		Vector3();

		Vector3(T p_x, T p_y, T p_z);

		template <typename U>
		Vector3(Vector3<U> other);

		T& operator[](int index);

		const T& operator[](int index) const;
	};

	template <typename T>
	class Vector4 {
	public:

		T x;
		T y;
		T z;
		T w;

		Vector4();

		Vector4(T p_x, T p_y, T p_z, T p_w);

		template <typename U>
		Vector4(Vector4<U> other);

		T& operator[](int index);

		const T& operator[](int index) const;
	};

	template <typename T>
	Vector2<T>::Vector2() {

		x = 0;
		y = 0;
	}

	template <typename T>
	Vector2<T>::Vector2(T p_x, T p_y) {

		x = p_x;
		y = p_y;
	}

	template <typename T>
	template <typename U>
	Vector2<T>::Vector2(Vector2<U> other) {

		x = other.x;
		y = other.y;
	}

	template <typename T>
	T& Vector2<T>::operator[](int index) {

		switch (index) {

		case 0: return x;
		case 1: return y;
		default: throw IndexOutOfBoundsException(index, 0, 2);
		}
	}

	template <typename T>
	const T& Vector2<T>::operator[](int index) const {

		switch (index) {

		case 0: return x;
		case 1: return y;
		default: throw IndexOutOfBoundsException(index, 0, 2);
		}
	}

	template <typename T>
	Vector3<T>::Vector3() {

		x = 0;
		y = 0;
		z = 0;
	}

	template <typename T>
	Vector3<T>::Vector3(T p_x, T p_y, T p_z) {

		x = p_x;
		y = p_y;
		z = p_z;
	}

	template <typename T>
	template <typename U>
	Vector3<T>::Vector3(Vector3<U> other) {

		x = other.x;
		y = other.y;
		z = other.z;
	}

	template <typename T>
	T& Vector3<T>::operator[](int index) {

		switch (index) {

		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: throw IndexOutOfBoundsException(index, 0, 3);
		}
	}

	template <typename T>
	const T& Vector3<T>::operator[](int index) const {

		switch (index) {

		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: throw IndexOutOfBoundsException(index, 0, 3);
		}
	}

	template <typename T>
	Vector4<T>::Vector4() {

		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template <typename T>
	Vector4<T>::Vector4(T p_x, T p_y, T p_z, T p_w) {

		x = p_x;
		y = p_y;
		z = p_z;
		w = p_w;
	}

	template <typename T>
	template <typename U>
	Vector4<T>::Vector4(Vector4<U> other) {

		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	template <typename T>
	T& Vector4<T>::operator[](int index) {

		switch (index) {

		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw IndexOutOfBoundsException(index, 0, 3);
		}
	}

	template <typename T>
	const T& Vector4<T>::operator[](int index) const {

		switch (index) {

		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw IndexOutOfBoundsException(index, 0, 3);
		}
	}

	template <typename T>
	Vector2<T> operator+(Vector2<T> v1, Vector2<T> v2) {

		return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
	}

	template <typename T>
	Vector3<T> operator+(Vector3<T> v1, Vector3<T> v2) {

		return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	template <typename T>
	Vector4<T> operator+(Vector4<T> v1, Vector4<T> v2) {

		return Vector4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	template <typename T>
	Vector2<T> operator-(Vector2<T> v1, Vector2<T> v2) {

		return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
	}

	template <typename T>
	Vector3<T> operator-(Vector3<T> v1, Vector3<T> v2) {

		return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	template <typename T>
	Vector4<T> operator-(Vector4<T> v1, Vector4<T> v2) {

		return Vector4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	template <typename T>
	Vector2<T> operator*(T n, Vector2<T> v) {

		return Vector2<T>(n * v.x, n * v.y);
	}

	template <typename T>
	Vector3<T> operator*(T n, Vector3<T> v) {

		return Vector3<T>(n * v.x, n * v.y, n * v.z);
	}

	template <typename T>
	Vector4<T> operator*(T n, Vector4<T> v) {

		return Vector4<T>(n * v.x, n * v.y, n * v.z, n * v.w);
	}

	template <typename T>
	Vector2<T> operator*(Vector2<T> v, T n) {

		return Vector2<T>(v.x * n, v.y * n);
	}

	template <typename T>
	Vector3<T> operator*(Vector3<T> v, T n) {

		return Vector3<T>(v.x * n, v.y * n, v.z * n);
	}

	template <typename T>
	Vector4<T> operator*(Vector4<T> v, T n) {

		return Vector4<T>(v.x * n, v.y * n, v.z * n, v.w * n);
	}

	template <typename T>
	Vector2<T> operator/(T n, Vector2<T> v) {

		return Vector2<T>(n / v.x, n / v.y);
	}

	template <typename T>
	Vector3<T> operator/(T n, Vector3<T> v) {

		return Vector3<T>(n / v.x, n / v.y, n / v.z);
	}

	template <typename T>
	Vector4<T> operator/(T n, Vector4<T> v) {

		return Vector4<T>(n / v.x, n / v.y, n / v.z, n / v.w);
	}

	template <typename T>
	Vector2<T> operator/(Vector2<T> v, T n) {

		return Vector2<T>(v.x / n, v.y / n);
	}

	template <typename T>
	Vector3<T> operator/(Vector3<T> v, T n) {

		return Vector3<T>(v.x / n, v.y / n, v.z / n);
	}

	template <typename T>
	Vector4<T> operator/(Vector4<T> v, T n) {

		return Vector4<T>(v.x / n, v.y / n, v.z / n, v.w / n);
	}

	float abs(Vector2<int> v) {

		return sqrt(float(v.x * v.x + v.y * v.y));
	}

	float abs(Vector2<float> v) {

		return sqrt(v.x * v.x + v.y * v.y);
	}

	double abs(Vector2<double> v) {

		return sqrt(v.x * v.x + v.y * v.y);
	}

	float abs(Vector3<int> v) {

		return sqrt(float(v.x * v.x + v.y * v.y + v.z * v.z));
	}

	float abs(Vector3<float> v) {

		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	double abs(Vector3<double> v) {

		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	float abs(Vector4<int> v) {

		return sqrt(float(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
	}

	float abs(Vector4<float> v) {

		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}

	double abs(Vector4<double> v) {

		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}

	Vector2<float> norm(Vector2<float> v) {

		return v / abs(v);
	}

	Vector2<double> norm(Vector2<double> v) {

		return v / abs(v);
	}

	Vector3<float> norm(Vector3<float> v) {

		return v / abs(v);
	}

	Vector3<double> norm(Vector3<double> v) {

		return v / abs(v);
	}

	Vector4<float> norm(Vector4<float> v) {

		return v / abs(v);
	}

	Vector4<double> norm(Vector4<double> v) {

		return v / abs(v);
	}

	typedef Vector2<int> IVec2;
	typedef Vector3<int> IVec3;
	typedef Vector4<int> IVec4;

	typedef Vector2<float> Vec2;
	typedef Vector3<float> Vec3;
	typedef Vector4<float> Vec4;
}