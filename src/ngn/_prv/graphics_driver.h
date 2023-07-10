#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../gfx/color.h"
#include "../mth/mat4.h"
#include "../mth/vec2.h"
#include "../mth/vec3.h"
#include "../mth/vec4.h"
#include "../non_owning_ptr.h"
#include "context_driver.h"
#include "../gfx/vertex.h"

namespace ngn {

struct Logger;
struct Viewer;

namespace prv {

template <void(*F)(uint32_t)>
struct GraphicsResource {
	GraphicsResource(uint32_t id) : m_id{id} {}
	GraphicsResource(GraphicsResource&& other) : m_id{other.m_id} { other.m_id = 0; }
	~GraphicsResource() { if (m_id != 0) F(m_id); }
private:
	uint32_t m_id;
	friend struct GraphicsDriver;
};

void VertexBufferDeleter(uint32_t vb);
void IndexBufferDeleter(uint32_t ib);
void GpuProgramDeleter(uint32_t p);
void DriverTextureDeleter(uint32_t t);

struct VertexBuffer : GraphicsResource<VertexBufferDeleter> { using GraphicsResource::GraphicsResource; };
struct IndexBuffer : GraphicsResource<IndexBufferDeleter> { using GraphicsResource::GraphicsResource; };
struct GpuProgram : GraphicsResource<GpuProgramDeleter> { using GraphicsResource::GraphicsResource; };
struct DriverTexture : GraphicsResource<DriverTextureDeleter> { using GraphicsResource::GraphicsResource; };

struct GraphicsDriver {
	GraphicsDriver(ContextDriver::GlGetProcAddress loader, const Logger& logger) noexcept;

	constexpr operator bool() const noexcept { return m_init; };

	void setup2D(const Vec2<uint16_t>& position, const Vec2<uint16_t> size) const noexcept;
	void setup3D(const Viewer& viewer) const noexcept;
	void cls(color_t color) const noexcept;

	std::unique_ptr<VertexBuffer> createVertexBuffer(const std::vector<Vertex>& vertices) const noexcept;
	std::unique_ptr<IndexBuffer> createIndexBuffer(const std::vector<uint16_t>& indices) const noexcept;
	void bindBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer) const noexcept;
	void drawBuffers(size_t numIndices) const noexcept;

	std::unique_ptr<GpuProgram> createProgram(const std::string& vertex, const std::string& fragment) const noexcept;
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

	std::unique_ptr<DriverTexture> createTexture() const noexcept;
	void bindTexture(const DriverTexture& texture) const noexcept;
	void setTexturePixels(
		const DriverTexture& texture,
		const Vec2<uint16_t>& size,
		non_owning_ptr<const color_t> pixels) const noexcept;
private:
	const Logger& m_logger;
	bool m_init;
};

} // namespace prv

} // namespace ngn
