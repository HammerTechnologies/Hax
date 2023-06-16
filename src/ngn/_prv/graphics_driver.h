#pragma once

#include <string>
#include <vector>
#include "../gfx/color.h"
#include "../mth/mat4.h"
#include "../mth/vec2.h"
#include "../mth/vec3.h"
#include "../mth/vec4.h"
#include "context_driver.h"
#include "vertex.h"

namespace ngn {

struct Logger;
struct Viewer;

namespace prv {

struct GraphicsResource {
	GraphicsResource(uint32_t id) : m_id{id} {}
	constexpr operator bool() const noexcept { return m_id != 0; }
private:
	uint32_t m_id;
	friend struct GraphicsDriver;
};

struct VertexBuffer : GraphicsResource {};
struct IndexBuffer : GraphicsResource {};
struct GpuProgram : GraphicsResource {};
struct DriverTexture : GraphicsResource {};

struct GraphicsDriver {
	GraphicsDriver(ContextDriver::GlGetProcAddress loader, const Logger& logger) noexcept;

	constexpr operator bool() const noexcept { return m_init; };

	void setup2D(const Vec2<uint16_t>& position, const Vec2<uint16_t> size) const noexcept;
	void setup3D(const Viewer& viewer) const noexcept;
	void cls(color_t color) const noexcept;

	VertexBuffer createVertexBuffer(const std::vector<Vertex>& vertices) const noexcept;
	IndexBuffer createIndexBuffer(const std::vector<uint16_t>& indices) const noexcept;
	void bindBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer) const noexcept;
	void drawBuffers(size_t numIndices) const noexcept;
	void deleteBuffer(const VertexBuffer& buffer) const noexcept;
	void deleteBuffer(const IndexBuffer& buffer) const noexcept;

	GpuProgram createProgram(const std::string& vertex, const std::string& fragment) const noexcept;
	void deleteProgram(const GpuProgram& program) const noexcept;
	void useProgram(const GpuProgram& program) const noexcept;
	int32_t getProgramUniformLocation(const GpuProgram& program, const std::string& name) const noexcept;
	void setProgramUniform(int32_t location, int32_t value) const noexcept;
	void setProgramUniform(int32_t location, real_t value) const noexcept;
	void setProgramUniform(int32_t location, const Vec2r& v) const noexcept;
	void setProgramUniform(int32_t location, const Vec3r& v) const noexcept;
	void setProgramUniform(int32_t location, const Vec4r& v) const noexcept;
	void setProgramUniform(int32_t location, const Mat4r& m) const noexcept;
	int32_t getProgramAttribLocation(const GpuProgram& program, const std::string& name) const noexcept;
	void setProgramAttrib(int32_t location, size_t size, bool normalize, size_t offset) const noexcept;

	DriverTexture createTexture() const noexcept;
	void deleteTexture(const DriverTexture& texture) const noexcept;
	void bindTexture(const DriverTexture& texture) const noexcept;
	void setTexturePixels(
		const DriverTexture& texture,
		const Vec2<uint16_t>& size,
		const color_t* pixels) const noexcept;
private:
	const Logger& m_logger;
	bool m_init;
};

} // namespace prv

} // namespace ngn
