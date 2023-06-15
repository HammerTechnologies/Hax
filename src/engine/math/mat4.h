#pragma once

#include <array>
#include <cmath>
#include "../real.h"
#include "quat.h"
#include "vec3.h"
#include "vec4.h"

template <typename T>
struct Mat4 {
	constexpr Mat4() noexcept
	: Mat4({1, 0, 0, 0,	0, 1, 0, 0,	0, 0, 1, 0,	0, 0, 0, 1}) {}

	constexpr Mat4(const std::array<T, 16> m) noexcept
	: m_data(m) {}

	constexpr Mat4 operator*(const Mat4& other) const noexcept {
		auto result = Mat4 {};
		for (size_t i = 0; i < 4; ++i) {
			const auto a0 = m_data[i];
			const auto a1 = m_data[i+4];
			const auto a2 = m_data[i+8];
			const auto a3 = m_data[i+12];
			result.m_data[i] = a0*other.m_data[0] + a1*other.m_data[1] + a2*other.m_data[2] + a3*other.m_data[3];
			result.m_data[i+4] = a0*other.m_data[4] + a1*other.m_data[5] + a2*other.m_data[6] + a3*other.m_data[7];
			result.m_data[i+8] = a0*other.m_data[8] + a1*other.m_data[9] + a2*other.m_data[10] + a3*other.m_data[11];
			result.m_data[i+12] = a0*other.m_data[12] + a1*other.m_data[13] + a2*other.m_data[14] + a3*other.m_data[15];
		}
		return result;
	}

	constexpr Vec4<T> operator*(const Vec4<T>& v) const noexcept {
		const auto translation = Mat4{}.translate({v.x(), v.y(), v.z()});
		translation.m_data[15] = v.w();
		const auto result = *this * translation;
		return {result.m_data[12], result.m_data[13], result.m_data[14], result.m_data[15]};
	}

	constexpr const T* data() const noexcept { return m_data.data(); }
	constexpr T* data() noexcept { return m_data.data(); }

	constexpr Mat4 translate(const Vec3<T>& v) const noexcept {
		auto translation = Mat4 {};
		translation.m_data[12] = v.x();
		translation.m_data[13] = v.y();
		translation.m_data[14] = v.z();
		return *this * translation;
	}

	constexpr Mat4 rotate(const T& angle, const Vec3<T>& axis) const noexcept {
		const auto c = std::cos(angle);
		const auto s = std::sin(angle);
		const auto xx = axis.x() * axis.x();
		const auto xy = axis.x() * axis.y();
		const auto xz = axis.x() * axis.z();
		const auto yy = axis.y() * axis.y();
		const auto yz = axis.y() * axis.z();
		const auto zz = axis.z() * axis.z();

		auto rotation = Mat4 {};
		rotation.m_data[0] = xx * (1 - c) + c;
		rotation.m_data[1] = xy * (1 - c) + axis.z() * s;
		rotation.m_data[2] = xz * (1 - c) - axis.y() * s;
		rotation.m_data[4] = xy * (1 - c) - axis.z() * s;
		rotation.m_data[5] = yy * (1 - c) + c;
		rotation.m_data[6] = yz * (1 - c) + axis.x() * s;
		rotation.m_data[8] = xz * (1 - c) + axis.y() * s;
		rotation.m_data[9] = yz * (1 - c) - axis.x() * s;
		rotation.m_data[10] = zz * (1 - c) + c;
		return *this * rotation;
	}

	constexpr Mat4 rotate(const Quat<T>& q) const noexcept {
		return rotate(q.angle(), q.axis());
	}

	constexpr Mat4 scale(const Vec3<T>& v) const noexcept {
		auto scale = Mat4 {};
		scale.m_data[0] = v.x();
		scale.m_data[5] = v.y();
		scale.m_data[10] = v.z();
		return *this * scale;
	}

	constexpr Mat4 transposed() const noexcept {
		const auto arr = std::array<T, 16> {};
		for (auto r = 0; r < 4; ++r) {
			for (auto c = 0; c < 4; ++c) {
				arr[c*4 + r] = m_data[r*4 + c];
			}
		}
		return {arr};
	}

	constexpr Mat4 inverse() const noexcept {
		const auto arr = std::array<T, 16> {};
		arr[ 0] =  m_data[5] * m_data[10] * m_data[15] - m_data[5] * m_data[11] * m_data[14] - m_data[9] * m_data[6] * m_data[15] + m_data[9] * m_data[7] * m_data[14] + m_data[13] * m_data[6] * m_data[11] - m_data[13] * m_data[7] * m_data[10];
		arr[ 4] = -m_data[4] * m_data[10] * m_data[15] + m_data[4] * m_data[11] * m_data[14] + m_data[8] * m_data[6] * m_data[15] - m_data[8] * m_data[7] * m_data[14] - m_data[12] * m_data[6] * m_data[11] + m_data[12] * m_data[7] * m_data[10];
		arr[ 8] =  m_data[4] * m_data[ 9] * m_data[15] - m_data[4] * m_data[11] * m_data[13] - m_data[8] * m_data[5] * m_data[15] + m_data[8] * m_data[7] * m_data[13] + m_data[12] * m_data[5] * m_data[11] - m_data[12] * m_data[7] * m_data[ 9];
		arr[12] = -m_data[4] * m_data[ 9] * m_data[14] + m_data[4] * m_data[10] * m_data[13] + m_data[8] * m_data[5] * m_data[14] - m_data[8] * m_data[6] * m_data[13] - m_data[12] * m_data[5] * m_data[10] + m_data[12] * m_data[6] * m_data[ 9];
		arr[ 1] = -m_data[1] * m_data[10] * m_data[15] + m_data[1] * m_data[11] * m_data[14] + m_data[9] * m_data[2] * m_data[15] - m_data[9] * m_data[3] * m_data[14] - m_data[13] * m_data[2] * m_data[11] + m_data[13] * m_data[3] * m_data[10];
		arr[ 5] =  m_data[0] * m_data[10] * m_data[15] - m_data[0] * m_data[11] * m_data[14] - m_data[8] * m_data[2] * m_data[15] + m_data[8] * m_data[3] * m_data[14] + m_data[12] * m_data[2] * m_data[11] - m_data[12] * m_data[3] * m_data[10];
		arr[ 9] = -m_data[0] * m_data[ 9] * m_data[15] + m_data[0] * m_data[11] * m_data[13] + m_data[8] * m_data[1] * m_data[15] - m_data[8] * m_data[3] * m_data[13] - m_data[12] * m_data[1] * m_data[11] + m_data[12] * m_data[3] * m_data[ 9];
		arr[13] =  m_data[0] * m_data[ 9] * m_data[14] - m_data[0] * m_data[10] * m_data[13] - m_data[8] * m_data[1] * m_data[14] + m_data[8] * m_data[2] * m_data[13] + m_data[12] * m_data[1] * m_data[10] - m_data[12] * m_data[2] * m_data[ 9];
		arr[ 2] =  m_data[1] * m_data[ 6] * m_data[15] - m_data[1] * m_data[ 7] * m_data[14] - m_data[5] * m_data[2] * m_data[15] + m_data[5] * m_data[3] * m_data[14] + m_data[13] * m_data[2] * m_data[ 7] - m_data[13] * m_data[3] * m_data[ 6];
		arr[ 6] = -m_data[0] * m_data[ 6] * m_data[15] + m_data[0] * m_data[ 7] * m_data[14] + m_data[4] * m_data[2] * m_data[15] - m_data[4] * m_data[3] * m_data[14] - m_data[12] * m_data[2] * m_data[ 7] + m_data[12] * m_data[3] * m_data[ 6];
		arr[10] =  m_data[0] * m_data[ 5] * m_data[15] - m_data[0] * m_data[ 7] * m_data[13] - m_data[4] * m_data[1] * m_data[15] + m_data[4] * m_data[3] * m_data[13] + m_data[12] * m_data[1] * m_data[ 7] - m_data[12] * m_data[3] * m_data[ 5];
		arr[14] = -m_data[0] * m_data[ 5] * m_data[14] + m_data[0] * m_data[ 6] * m_data[13] + m_data[4] * m_data[1] * m_data[14] - m_data[4] * m_data[2] * m_data[13] - m_data[12] * m_data[1] * m_data[ 6] + m_data[12] * m_data[2] * m_data[ 5];
		arr[ 3] = -m_data[1] * m_data[ 6] * m_data[11] + m_data[1] * m_data[ 7] * m_data[10] + m_data[5] * m_data[2] * m_data[11] - m_data[5] * m_data[3] * m_data[10] - m_data[ 9] * m_data[2] * m_data[ 7] + m_data[ 9] * m_data[3] * m_data[ 6];
		arr[ 7] =  m_data[0] * m_data[ 6] * m_data[11] - m_data[0] * m_data[ 7] * m_data[10] - m_data[4] * m_data[2] * m_data[11] + m_data[4] * m_data[3] * m_data[10] + m_data[ 8] * m_data[2] * m_data[ 7] - m_data[ 8] * m_data[3] * m_data[ 6];
		arr[11] = -m_data[0] * m_data[ 5] * m_data[11] + m_data[0] * m_data[ 7] * m_data[ 9] + m_data[4] * m_data[1] * m_data[11] - m_data[4] * m_data[3] * m_data[ 9] - m_data[ 8] * m_data[1] * m_data[ 7] + m_data[ 8] * m_data[3] * m_data[ 5];
		arr[15] =  m_data[0] * m_data[ 5] * m_data[10] - m_data[0] * m_data[ 6] * m_data[ 9] - m_data[4] * m_data[1] * m_data[10] + m_data[4] * m_data[2] * m_data[ 9] + m_data[ 8] * m_data[1] * m_data[ 6] - m_data[ 8] * m_data[2] * m_data[ 5];
		const auto det = m_data[0] * arr[0] + m_data[1] * arr[4] + m_data[2] * arr[8] + m_data[3] * arr[12];
		if (std::abs(det) <= T{0.00001}) return Mat4 {m_data};
		const auto invdet = T{1.0} / det;
		for (auto i = 0; i < 16; i++) {
			arr[i] *= invdet;
		}
		return {arr};
	}

	constexpr static Mat4 ortho(const T& left, const T& right, const T& bottom, const T& top, const T& near_, const T& far_) noexcept {
		const auto a = T{2.0} / (right - left);
		const auto b = T{2.0} / (top - bottom);
		const auto c = T{2.0} / (far_ - near_);
		const auto tx = -(right+left) / (right-left);
		const auto ty = -(top+bottom) / (top-bottom);
		const auto tz = -(far_+near_) / (far_-near_);
		auto result = Mat4 {};
		result.m_data[0] = a;
		result.m_data[5] = b;
		result.m_data[10] = c;
		result.m_data[12] = tx;
		result.m_data[13] = ty;
		result.m_data[14] = tz;
		return result;
	}

	constexpr static Mat4 frustum(const T& left, const T& right, const T& bottom, const T& top, const T& near_, const T& far_) noexcept {
		auto result = Mat4 {};
		result.m_data[0]  = 2 * near_ / (right - left);
		result.m_data[5]  = 2 * near_ / (top - bottom);
		result.m_data[8]  = -(right + left) / (right - left);
		result.m_data[9]  = -(top + bottom) / (top - bottom);
		result.m_data[10] = (far_ + near_) / (far_ - near_);
		result.m_data[11] = 1;
		result.m_data[14] = -(2 * far_ * near_) / (far_ - near_);
		result.m_data[15] = 0;
		return result;
	}

	constexpr static Mat4 perspective(const T& fovy, const T& aspect, const T& near_, const T& far_) noexcept {
		const auto tangent = std::tan(fovy / 2);
		const auto height = near_ * tangent;
		const auto width = height * aspect;
		return Mat4::frustum(-width, width, -height, height, near_, far_);
	}

	constexpr static Mat4 lookat(const Vec3<T>& center, const Vec3<T>& eye, const Vec3<T>& up) noexcept {
		const auto z = (eye - center).norm();
		const auto x = up.cross(z).norm();
		const auto y = z.cross(x).norm();
		const auto mat = Mat4 {{
			x.x(),
			y.x(),
			z.x(),
			0,
			x.y(),
			y.y(),
			z.y(),
			0,
			x.z(),
			y.z(),
			z.z(),
			0,
			0,
			0,
			0,
			1}};
		return mat.translate(center * -1);
	}

	constexpr static Mat4 transform(const Vec3<T>& pos, const Quat<T>& rot, const Vec3<T>& scale) noexcept {
		return Mat4 {}.translate(pos).rotate(rot).scale(scale);
	}

	constexpr static Mat4 billboard(const Mat4& view, const Vec3<T>& pos, const T& spin, const T& width, const T& height, bool upfront) {
		auto mat = view.transposed();
		mat.m_data[3] = 0;
		mat.m_data[7] = 0;
		mat.m_data[11] = 0;
		mat.m_data[12] = pos.x();
		mat.m_data[13] = pos.y();
		mat.m_data[14] = pos.z();
		mat.m_data[15] = 1;
		if (upfront) {
			mat.m_data[4] = 0;
			mat.m_data[5] = 1;
			mat.m_data[6] = 0;
		}
		return mat.rotate(spin, Vec3{0, 0, 1}).scale(Vec3<T> {width, height, 1});
	}
private:
	std::array<T, 16> m_data;
};

using Mat4r = Mat4<real_t>;
