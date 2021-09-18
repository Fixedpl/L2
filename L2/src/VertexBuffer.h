#pragma once
#include <cstdint>
#include <vector>

#include "DrawTypeEnum.h"
#include "gl.h"


struct VertexAttributeElement {
	uint32_t vertex_dim;
	uint32_t data_type;

	static uint32_t getTypeSize(const uint32_t& data_type);
};


class VertexBufferLayout
{
public:

	VertexBufferLayout();

	void addAttribute(const uint32_t& vertex_dim, const uint32_t& data_type = GL_FLOAT);

	void addAttributes(const std::vector<uint32_t>& vertex_dims);

	void resetAttributes();

	void bind() const;

	std::vector<VertexAttributeElement> getAttributeElements() const { return m_va_elements; }

	uint32_t getSizeOfAttributeElementsDimensions() const;

	uint32_t getSumOfVerticeDimensions() const;

private:

	uint32_t m_id;

	uint32_t m_stride;

	std::vector<VertexAttributeElement> m_va_elements;

};


class VertexBuffer
{
public:

	VertexBuffer();
	VertexBuffer(const DrawType& draw_type, const Usage& usage);
	~VertexBuffer();

	void bind() const;

	void create(const uint32_t& object_size, const uint32_t& object_count);

	void update(void* data, const uint32_t& vertice_size, const uint32_t& vertice_count);
	void update(void* data, const uint32_t& vertice_size, const uint32_t& vertice_count, const uint32_t& count_offset);

	DrawType getDrawType() const { return m_draw_type; }
	void setDrawType(const DrawType& draw_type) { m_draw_type = draw_type; }

	Usage getUsage() const { return m_usage; }
	void setUsage(const Usage& usage) { m_usage = usage; }

	uint32_t getVerticeCount() const { return m_vertice_count; }

private:

	uint32_t m_id;

	DrawType m_draw_type;

	Usage m_usage;

	uint32_t m_vertice_count;

};

