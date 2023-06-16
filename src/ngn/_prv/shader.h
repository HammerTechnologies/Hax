#pragma once

#include <cstdint>
#include <string>
#include "../mth/mat4.h"
#include "../mth/vec2.h"
#include "../mth/vec3.h"
#include "../mth/vec4.h"
#include "graphics_driver.h"

namespace ngn::prv {

struct Shader {
	Shader(const GraphicsDriver& driver, const std::string& vertex, const std::string& fragment) noexcept;
	~Shader() noexcept;

	constexpr operator bool() const noexcept { return m_program; }

	int32_t getUniform(const std::string& name) const noexcept;

	void prepare() const noexcept;
	void setInt(int32_t location, int32_t value) const noexcept;
	void setReal(int32_t location, real_t value) const noexcept;
	void setVec2(int32_t location, const Vec2r& v) const noexcept;
	void setVec3(int32_t location, const Vec3r& v) const noexcept;
	void setVec4(int32_t location, const Vec4r& v) const noexcept;
	void setMat4(int32_t location, const Mat4r& m) const noexcept;
private:
	const GraphicsDriver& m_driver;
	GpuProgram m_program;
	int32_t m_vertexPos;
	int32_t m_vertexColor;
	int32_t m_vertexTexCoords;
};

} // namespace ngn::prv
