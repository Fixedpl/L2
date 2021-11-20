#include "VertexBuffer.h"

uint32_t VertexAttributeElement::getTypeSize(const uint32_t& data_type)
{
	switch (data_type) {
	case GL_FLOAT:
		return 4;
	}
	return 0;
}

VertexBufferLayout::VertexBufferLayout() : m_stride(0) {
	glGenVertexArrays(1, &m_id);
}

void VertexBufferLayout::addAttribute(const uint32_t& vertex_dim, const uint32_t& data_type) {
	m_va_elements.push_back({ vertex_dim, data_type });
	glBindVertexArray(m_id);
	m_stride += vertex_dim * VertexAttributeElement::getTypeSize(data_type);
	unsigned int offset = 0;
	for (int i = 0; i < m_va_elements.size(); i++) {
		VertexAttributeElement vae = m_va_elements[i];
		glVertexAttribPointer(i, vae.vertex_dim, vae.data_type, GL_FALSE, m_stride, (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += vae.vertex_dim * VertexAttributeElement::getTypeSize(data_type);
	}
}

void VertexBufferLayout::addAttributes(const std::vector<uint32_t>& vertex_dims) {
	for (auto& dim : vertex_dims) {
		addAttribute(dim);
	}
}

void VertexBufferLayout::resetAttributes()
{
	m_stride = 0;
	m_va_elements.clear();
}

void VertexBufferLayout::bind() const {
	glBindVertexArray(m_id);
}

std::vector<VertexAttributeElement> VertexBufferLayout::getAttributeElements() const
{
	return m_va_elements;
}

uint32_t VertexBufferLayout::getSizeOfAttributeElementsDimensions() const
{
	uint32_t sum = 0;
	for (auto& el : m_va_elements) {
		sum += el.vertex_dim;
	}
	return sum * 4;
}

uint32_t VertexBufferLayout::getSumOfVerticeDimensions() const
{
	uint32_t sum = 0;
	for (auto& vae : m_va_elements) {
		sum += vae.vertex_dim;
	}
	return sum;
}

VertexBuffer::VertexBuffer()
	:
	m_id(0),
	m_draw_type(DrawType::UNDEFINED),
	m_usage(Usage::UNDEFINED),
	m_vertice_count(0)
{
	glGenBuffers(1, &m_id);
}

VertexBuffer::VertexBuffer(const DrawType& draw_type, const Usage& usage)
	:
	m_id(0),
	m_draw_type(draw_type),
	m_usage(usage),
	m_vertice_count(0)
{
	glGenBuffers(1, &m_id);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::create(const uint32_t& vertice_size, const uint32_t& vertice_count)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);

	glBufferData(GL_ARRAY_BUFFER, vertice_size * vertice_count, nullptr, (GLenum)m_draw_type);
}

void VertexBuffer::update(void* data, const uint32_t& vertice_size, const uint32_t& vertice_count)
{
	if (vertice_count > m_vertice_count) {
		m_vertice_count = vertice_count;
	}
		
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertice_size * vertice_count, data);
}

void VertexBuffer::update(void* data, const uint32_t& vertice_size, const uint32_t& vertice_count, const uint32_t& count_offset)
{
	if (vertice_count + count_offset > m_vertice_count) {
		m_vertice_count = vertice_count + count_offset;
	}
	
	glBufferSubData(GL_ARRAY_BUFFER, vertice_size * count_offset, vertice_size * vertice_count, data);
}

DrawType VertexBuffer::getDrawType() const
{
	return m_draw_type;
}

void VertexBuffer::setDrawType(const DrawType& draw_type)
{
	m_draw_type = draw_type;
}

Usage VertexBuffer::getUsage() const
{
	return m_usage;
}

void VertexBuffer::setUsage(const Usage& usage)
{
	m_usage = usage;
}

uint32_t VertexBuffer::getVerticeCount() const
{
	return m_vertice_count;
}
