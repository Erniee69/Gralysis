#pragma once
#include <AcidLib/Containers/Array.hpp>
#include <AcidLib/Math/Vector.hpp>
#include <AcidLib/Math/Trig.hpp>

namespace ac {

	class Transform2D {
	public:

		static const Transform2D NullTransform;

		static const Transform2D Identity;

		Transform2D();

		Transform2D(float* p_data);

		Transform2D(float x0y0, float x1y0, float x2y0, float x0y1, float x1y1, float x2y1, float x0y2, float x1y2, float x2y2);

		Transform2D operator*(const Transform2D& other) const;
		Transform2D& operator*=(const Transform2D& other);

		Array<float, 3>& operator[](int index);

		const Array<float, 3>& operator[](int index) const;

		Transform2D& translate(float x, float y);
		Transform2D& translate(Vec2 v);

		Transform2D& rotate(float angle);

		Transform2D& scale(float x, float y);
		Transform2D& scale(Vec2 v);

		Transform2D& combine(const Transform2D& other);

		Transform2D getInverseTransform() const;

		Vec2 transformPoint(Vec2 v) const;

	private:

		Array<Array<float, 3>, 3> m_data;
	};

	class Transform3D {
	public:

		static const Transform3D NullTransform;

		static const Transform3D Identity;

		Transform3D();

		Transform3D(float* p_data);

		Transform3D(float x0y0, float x1y0, float x2y0, float x3y0, float x0y1, float x1y1, float x2y1, float x3y1, float x0y2, float x1y2, float x2y2, float x3y2, float x0y3, float x1y3, float x2y3, float x3y3);

		Transform3D operator*(const Transform3D& other) const;
		Transform3D& operator*=(const Transform3D& other);

		Array<float, 4>& operator[](int index);

		const Array<float, 4>& operator[](int index) const;

		Transform3D& translate(float x, float y, float z);
		Transform3D& translate(Vec3 v);

		Transform3D& rotateX(float angle);
		Transform3D& rotateY(float angle);
		Transform3D& rotateZ(float angle);

		Transform3D& scale(float x, float y, float z);
		Transform3D& scale(Vec3 v);

		Transform3D& combine(const Transform3D& other);

		Transform3D getInverseTransform() const;

		Vec3 transformPoint(Vec3 v) const;

	private:

		Array<Array<float, 4>, 4> m_data;
	};

	const Transform2D Transform2D::NullTransform = Transform2D(0, 0, 0, 0, 0, 0, 0, 0, 0);

	const Transform2D Transform2D::Identity = Transform2D(1, 0, 0, 0, 1, 0, 0, 0, 1);

	const Transform3D Transform3D::NullTransform = Transform3D(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	const Transform3D Transform3D::Identity = Transform3D(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	Transform2D::Transform2D() {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				m_data[i][j] = (i == j) ? 1 : 0;
			}
		}
	}

	Transform2D::Transform2D(float* p_data) {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				m_data[i][j] = p_data[3 * i + j];
			}
		}
	}

	Transform2D::Transform2D(float x0y0, float x1y0, float x2y0, float x0y1, float x1y1, float x2y1, float x0y2, float x1y2, float x2y2) {

		m_data[0][0] = x0y0;
		m_data[0][1] = x0y1;
		m_data[0][2] = x0y2;
		m_data[1][0] = x1y0;
		m_data[1][1] = x1y1;
		m_data[1][2] = x1y2;
		m_data[2][0] = x2y0;
		m_data[2][1] = x2y1;
		m_data[2][2] = x2y2;
	}

	Transform2D Transform2D::operator*(const Transform2D& other) const {

		Transform2D result = NullTransform;

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				for (int k = 0; k < 3; k++) {

					result[i][j] += m_data[i][k] * other.m_data[k][j];
				}
			}
		}

		return result;
	}

	Transform2D& Transform2D::operator*=(const Transform2D& other) {

		Transform2D result;

		result = (*this) * other;

		(*this) = result;

		return *this;
	}

	Array<float, 3>& Transform2D::operator[](int index) {

		return m_data[index];
	}

	const Array<float, 3>& Transform2D::operator[](int index) const {

		return m_data[index];
	}

	Transform2D& Transform2D::translate(float x, float y) {

		(*this) = Transform2D(1, 0, x, 0, 1, y, 0, 0, 1) * (*this);

		return *this;
	}

	Transform2D& Transform2D::translate(Vec2 v) {

		(*this) = Transform2D(1, 0, v.x, 0, 1, v.y, 0, 0, 1) * (*this);

		return *this;
	}

	Transform2D& Transform2D::rotate(float angle) {

		(*this) = Transform2D(cos(angle), sin(angle), 0, -sin(angle), cos(angle), 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform2D& Transform2D::scale(float x, float y) {

		(*this) = Transform2D(x, 0, 0, 0, y, 0, 0, 0, 1) * (*this);

		return *this;
	}
	Transform2D& Transform2D::scale(Vec2 v) {

		(*this) = Transform2D(v.x, 0, 0, 0, v.y, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform2D& Transform2D::combine(const Transform2D& other) {

		Transform2D tmp = NullTransform;

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				for (int k = 0; k < 3; k++) {

					tmp[i][j] += m_data[i][k] * m_data[k][j];
				}
			}
		}

		(*this) = tmp;

		return *this;
	}

	Transform2D Transform2D::getInverseTransform() const {

		Transform2D result = NullTransform;

		result.m_data[0][0] = m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1];
		result.m_data[0][1] = -m_data[0][1] * m_data[2][2] + m_data[0][2] * m_data[2][1];
		result.m_data[0][2] = m_data[0][1] * m_data[1][2] - m_data[0][2] * m_data[1][1];

		result.m_data[1][0] = -m_data[1][0] * m_data[2][2] + m_data[1][2] * m_data[2][0];
		result.m_data[1][1] = m_data[0][0] * m_data[2][2] - m_data[0][2] * m_data[2][0];
		result.m_data[1][2] = -m_data[0][0] * m_data[1][2] + m_data[0][2] * m_data[1][0];

		result.m_data[2][0] = m_data[1][0] * m_data[2][1] - m_data[1][1] * m_data[2][0];
		result.m_data[2][1] = -m_data[0][0] * m_data[2][1] + m_data[0][1] * m_data[2][0];
		result.m_data[2][2] = m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0];

		float det = m_data[0][0] * result.m_data[0][0] + m_data[0][1] * result.m_data[1][0] + m_data[0][2] * result.m_data[2][0];

		if (det == 0) {

			return Transform2D();
		}

		det = 1.0 / det;

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				result.m_data[i][j] *= det;
			}
		}

		return result;
	}

	Vec2 Transform2D::transformPoint(Vec2 v) const {

		Vec3 homogenousPoint = Vec3(v.x, v.y, 1);

		Vec3 result;

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				result[i] = m_data[i][j] * homogenousPoint[j];
			}
		}

		return Vec2(result.x / result.z, result.y / result.z);
	}

	Transform3D::Transform3D() {

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {

				m_data[i][j] = (i == j) ? 1 : 0;
			}
		}
	}

	Transform3D::Transform3D(float* p_data) {

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {

				m_data[i][j] = p_data[4 * i + j];
			}
		}
	}

	Transform3D::Transform3D(float x0y0, float x1y0, float x2y0, float x3y0, float x0y1, float x1y1, float x2y1, float x3y1, float x0y2, float x1y2, float x2y2, float x3y2, float x0y3, float x1y3, float x2y3, float x3y3) {

		m_data[0][0] = x0y0;
		m_data[0][1] = x1y0;
		m_data[0][2] = x2y0;
		m_data[0][3] = x3y0;
		m_data[1][0] = x0y1;
		m_data[1][1] = x1y1;
		m_data[1][2] = x2y1;
		m_data[1][3] = x3y1;
		m_data[2][0] = x0y2;
		m_data[2][1] = x1y2;
		m_data[2][2] = x2y2;
		m_data[2][3] = x3y2;
		m_data[3][0] = x0y3;
		m_data[3][1] = x1y3;
		m_data[3][2] = x2y3;
		m_data[3][3] = x3y3;
	}

	Transform3D Transform3D::operator*(const Transform3D& other) const {

		Transform3D result = NullTransform;

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {

				for (int k = 0; k < 4; k++) {

					result[i][j] += m_data[i][k] * other.m_data[k][j];
				}
			}
		}

		return result;
	}

	Transform3D& Transform3D::operator*=(const Transform3D& other) {

		Transform3D result;

		result = (*this) * other;

		(*this) = result;

		return *this;
	}

	Array<float, 4>& Transform3D::operator[](int index) {

		return m_data[index];
	}

	const Array<float, 4>& Transform3D::operator[](int index) const {

		return m_data[index];
	}

	Transform3D& Transform3D::translate(float x, float y, float z) {

		(*this) = Transform3D(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform3D& Transform3D::translate(Vec3 v) {

		(*this) = Transform3D(1, 0, 0, v.x, 0, 1, 0, v.y, 0, 0, 1, v.z, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform3D& Transform3D::rotateX(float angle) {

		(*this) = Transform3D(cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform3D& Transform3D::rotateY(float angle) {

		(*this) = Transform3D(cos(angle), 0, sin(angle), 0, 0, 1, 0, 0, -sin(angle), 0, cos(angle), 0, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform3D& Transform3D::rotateZ(float angle) {

		(*this) = Transform3D(1, 0, 0, 0, 0, cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle), 0, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform3D& Transform3D::scale(float x, float y, float z) {

		(*this) = Transform3D(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform3D& Transform3D::scale(Vec3 v) {

		(*this) = Transform3D(v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, v.z, 0, 0, 0, 0, 1) * (*this);

		return *this;
	}

	Transform3D& Transform3D::combine(const Transform3D& other) {

		(*this) *= other;

		return *this;
	}

	Transform3D Transform3D::getInverseTransform() const {

		Transform3D result = NullTransform;

		result.m_data[0][0] = m_data[1][1] * m_data[2][2] * m_data[3][3] - m_data[1][1] * m_data[2][3] * m_data[3][2] - m_data[2][1] * m_data[1][2] * m_data[3][3] + m_data[2][1] * m_data[1][3] * m_data[3][2] + m_data[3][1] * m_data[1][2] * m_data[2][3] - m_data[3][1] * m_data[1][3] * m_data[2][2];
		result.m_data[0][1] = -m_data[0][1] * m_data[2][2] * m_data[3][3] + m_data[0][1] * m_data[2][3] * m_data[3][2] + m_data[2][1] * m_data[0][2] * m_data[3][3] - m_data[2][1] * m_data[0][3] * m_data[3][2] - m_data[3][1] * m_data[0][2] * m_data[2][3] + m_data[3][1] * m_data[0][3] * m_data[2][2];
		result.m_data[0][2] = m_data[0][1] * m_data[1][2] * m_data[3][3] - m_data[0][1] * m_data[1][3] * m_data[3][2] - m_data[1][1] * m_data[0][2] * m_data[3][3] + m_data[1][1] * m_data[0][3] * m_data[3][2] + m_data[3][1] * m_data[0][2] * m_data[1][3] - m_data[3][1] * m_data[0][3] * m_data[1][2];
		result.m_data[0][3] = -m_data[0][1] * m_data[1][2] * m_data[2][3] + m_data[0][1] * m_data[1][3] * m_data[2][2] + m_data[1][1] * m_data[0][2] * m_data[2][3] - m_data[1][1] * m_data[0][3] * m_data[2][2] - m_data[2][1] * m_data[0][2] * m_data[1][3] + m_data[2][1] * m_data[0][3] * m_data[1][2];

		result.m_data[1][0] = -m_data[1][0] * m_data[2][2] * m_data[3][3] + m_data[1][0] * m_data[2][3] * m_data[3][2] + m_data[2][0] * m_data[1][2] * m_data[3][3] - m_data[2][0] * m_data[1][3] * m_data[3][2] - m_data[3][0] * m_data[1][2] * m_data[2][3] + m_data[3][0] * m_data[1][3] * m_data[2][2];
		result.m_data[1][1] = m_data[0][0] * m_data[2][2] * m_data[3][3] - m_data[0][0] * m_data[2][3] * m_data[3][2] - m_data[2][0] * m_data[0][2] * m_data[3][3] + m_data[2][0] * m_data[0][3] * m_data[3][2] + m_data[3][0] * m_data[0][2] * m_data[2][3] - m_data[3][0] * m_data[0][3] * m_data[2][2];
		result.m_data[1][2] = -m_data[0][0] * m_data[1][2] * m_data[3][3] + m_data[0][0] * m_data[1][3] * m_data[3][2] + m_data[1][0] * m_data[0][2] * m_data[3][3] - m_data[1][0] * m_data[0][3] * m_data[3][2] - m_data[3][0] * m_data[0][2] * m_data[1][3] + m_data[3][0] * m_data[0][3] * m_data[1][2];
		result.m_data[1][3] = m_data[0][0] * m_data[1][2] * m_data[2][3] - m_data[0][0] * m_data[1][3] * m_data[2][2] - m_data[1][0] * m_data[0][2] * m_data[2][3] + m_data[1][0] * m_data[0][3] * m_data[2][2] + m_data[2][0] * m_data[0][2] * m_data[1][3] - m_data[2][0] * m_data[0][3] * m_data[1][2];

		result.m_data[2][0] = m_data[1][0] * m_data[2][1] * m_data[3][3] - m_data[1][0] * m_data[2][3] * m_data[3][1] - m_data[2][0] * m_data[1][1] * m_data[3][3] + m_data[2][0] * m_data[1][3] * m_data[3][1] + m_data[3][0] * m_data[1][1] * m_data[2][3] - m_data[3][0] * m_data[1][3] * m_data[2][1];
		result.m_data[2][1] = -m_data[0][0] * m_data[2][1] * m_data[3][3] + m_data[0][0] * m_data[2][3] * m_data[3][1] + m_data[2][0] * m_data[0][1] * m_data[3][3] - m_data[2][0] * m_data[0][3] * m_data[3][1] - m_data[3][0] * m_data[0][1] * m_data[2][3] + m_data[3][0] * m_data[0][3] * m_data[2][1];
		result.m_data[2][2] = m_data[0][0] * m_data[1][1] * m_data[3][3] - m_data[0][0] * m_data[1][3] * m_data[3][1] - m_data[1][0] * m_data[0][1] * m_data[3][3] + m_data[1][0] * m_data[0][3] * m_data[3][1] + m_data[3][0] * m_data[0][1] * m_data[1][3] - m_data[3][0] * m_data[0][3] * m_data[1][1];
		result.m_data[2][3] = -m_data[0][0] * m_data[1][1] * m_data[2][3] + m_data[0][0] * m_data[1][3] * m_data[2][1] + m_data[1][0] * m_data[0][1] * m_data[2][3] - m_data[1][0] * m_data[0][3] * m_data[2][1] - m_data[2][0] * m_data[0][1] * m_data[1][3] + m_data[2][0] * m_data[0][3] * m_data[1][1];

		result.m_data[3][0] = -m_data[1][0] * m_data[2][1] * m_data[3][2] + m_data[1][0] * m_data[2][2] * m_data[3][1] + m_data[2][0] * m_data[1][1] * m_data[3][2] - m_data[2][0] * m_data[1][2] * m_data[3][1] - m_data[3][0] * m_data[1][1] * m_data[2][2] + m_data[3][0] * m_data[1][2] * m_data[2][1];
		result.m_data[3][1] = m_data[0][0] * m_data[2][1] * m_data[3][2] - m_data[0][0] * m_data[2][2] * m_data[3][1] - m_data[2][0] * m_data[0][1] * m_data[3][2] + m_data[2][0] * m_data[0][2] * m_data[3][1] + m_data[3][0] * m_data[0][1] * m_data[2][2] - m_data[3][0] * m_data[0][2] * m_data[2][1];
		result.m_data[3][2] = -m_data[0][0] * m_data[1][1] * m_data[3][2] + m_data[0][0] * m_data[1][2] * m_data[3][1] + m_data[1][0] * m_data[0][1] * m_data[3][2] - m_data[1][0] * m_data[0][2] * m_data[3][1] - m_data[3][0] * m_data[0][1] * m_data[1][2] + m_data[3][0] * m_data[0][2] * m_data[1][1];
		result.m_data[3][3] = m_data[0][0] * m_data[1][1] * m_data[2][2] - m_data[0][0] * m_data[1][2] * m_data[2][1] - m_data[1][0] * m_data[0][1] * m_data[2][2] + m_data[1][0] * m_data[0][2] * m_data[2][1] + m_data[2][0] * m_data[0][1] * m_data[1][2] - m_data[2][0] * m_data[0][2] * m_data[1][1];

		float det = m_data[0][0] * result.m_data[0][0] + m_data[0][1] * result.m_data[1][0] + m_data[0][2] * result.m_data[2][0] + m_data[0][3] * result.m_data[3][0];

		if (det == 0) {

			return Transform3D();
		}

		det = 1.0 / det;

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {

				result.m_data[i][j] *= det;
			}
		}

		return result;
	}

	Vec3 Transform3D::transformPoint(Vec3 v) const {

		Vec4 homogenousPoint = Vec4(v.x, v.y, v.z, 1);

		Vec4 result;

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 4; j++) {

				result[i] += m_data[i][j] * homogenousPoint[j];
			}
		}

		return Vec3(result.x / result.w, result.y / result.w, result.z / result.w);
	}
}