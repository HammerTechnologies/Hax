#pragma once

#include <string>
#include <vector>
#include "../../math/mat4.h"
#include "../../math/vec3.h"
#include "../color.h"
#include "context_driver.h"
#include "vertex.h"

struct Logger;

struct VertexBuffer {
	VertexBuffer(uint32_t id) : m_id{id} {}
private:
	uint32_t m_id;
	friend struct GraphicsDriver;
};

struct IndexBuffer {
	IndexBuffer(uint32_t id) : m_id{id} {}
private:
	uint32_t m_id;
	friend struct GraphicsDriver;
};

struct GpuProgram {
	GpuProgram(uint32_t id) : m_id{id} {}
	constexpr bool isValid() const noexcept { return m_id != 0; }
private:
	uint32_t m_id;
	friend struct GraphicsDriver;
};

struct DriverTexture {
	DriverTexture(uint32_t id) : m_id{id} {}
	constexpr bool isValid() const noexcept { return m_id != 0; }
private:
	uint32_t m_id;
	friend struct GraphicsDriver;
};

struct GraphicsDriver {
	GraphicsDriver(ContextDriver::GlGetProcAddress loader, const Logger& logger) noexcept;

	constexpr bool isValid() const noexcept { return m_init; };

	void setup2D(uint16_t x, uint16_t y, uint16_t w, uint16_t h) const noexcept;
	void cls(uint32_t color) const noexcept;

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
	void setProgramUniform(int32_t location, real_t x, real_t y) const noexcept;
	void setProgramUniform(int32_t location, const Vec3r& v) const noexcept;
	void setProgramUniform(int32_t location, real_t x, real_t y, real_t z, real_t w) const noexcept;
	void setProgramUniform(int32_t location, const Mat4r& m) const noexcept;
	int32_t getProgramAttribLocation(const GpuProgram& program, const std::string& name) const noexcept;
	void setProgramAttrib(int32_t location, size_t size, bool normalize, size_t offset) const noexcept;

	DriverTexture createTexture() const noexcept;
	void deleteTexture(const DriverTexture& texture) const noexcept;
	void bindTexture(const DriverTexture& texture) const noexcept;
	void setTexturePixels(
		const DriverTexture& texture,
		uint16_t width,
		uint16_t height,
		const uint32_t* pixels) const noexcept;
private:
	const Logger& m_logger;
	bool m_init;
};
