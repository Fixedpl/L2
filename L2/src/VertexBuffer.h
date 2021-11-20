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

	std::vector<VertexAttributeElement> getAttributeElements() const;

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

	DrawType getDrawType() const;
	void setDrawType(const DrawType& draw_type);

	Usage getUsage() const;
	void setUsage(const Usage& usage);

	uint32_t getVerticeCount() const;

private:

	uint32_t m_id;

	DrawType m_draw_type;

	Usage m_usage;

	uint32_t m_vertice_count;

};

