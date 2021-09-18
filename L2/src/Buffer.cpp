#include "Buffer.h"

#include <iostream>

AbstractBuffer::AbstractBuffer()
	:
	m_vertice_size(0)
{
}

AbstractBuffer::AbstractBuffer(const DrawType& draw_type, const Usage& usage, const std::vector<uint32_t>& vertex_dims)
	:
	m_vertex_buffer(draw_type, usage),
	m_vertex_dims(vertex_dims),
	m_vertice_size(0)
{
	extractVerticeDetails();
}

bool AbstractBuffer::_create(const uint32_t& object_count_reserved)
{
	if (!isCreationPossible()) {
		return false;
	}

	m_vertex_buffer_layout.bind();

	m_vertex_buffer.create(m_vertice_size, object_count_reserved);

	if (m_vertex_buffer_layout.getAttributeElements().size()) {
		m_vertex_buffer_layout.resetAttributes();
	}

	m_vertex_buffer_layout.addAttributes(m_vertex_dims);

	return true;
}

void AbstractBuffer::extractVerticeDetails()
{
	m_vertice_size = 0;
	for (auto& dim : m_vertex_dims) {
		m_vertice_size += dim;
	}
	m_vertice_size *= 4;;
}

bool AbstractBuffer::isCreationPossible() const
{
	if (m_vertex_buffer.getUsage() == Usage::UNDEFINED) {
		std::cout << "[ERROR] Buffer.cpp: Couldn't create buffer because Usage is undefined.\n";
		return false;
	}
	if (m_vertex_buffer.getDrawType() == DrawType::UNDEFINED) {
		std::cout << "[ERROR] Buffer.cpp: Couldn't create buffer because DrawType is undefined.\n";
		return false;
	}
	if (m_vertex_dims.empty()) {
		std::cout << "[ERROR] Buffer.cpp: Couldn't create buffer because Vertex dimensions aren't defined.\n";
		return false;
	}
	return true;
}

void AbstractBuffer::setVertexDimensions(const std::vector<uint32_t>& vertex_dims)
{
	m_vertex_dims = vertex_dims;
	extractVerticeDetails();
}

Buffer::Buffer()
	: m_points_per_object(0)
{
}

Buffer::Buffer(	const DrawType& draw_type, 
				const Usage& usage, 
				const std::vector<uint32_t>& vertex_dims, 
				const uint32_t& points_per_object)
	:
	AbstractBuffer(draw_type, usage, vertex_dims),
	m_points_per_object(points_per_object)
{
}

void Buffer::bind() const
{
	m_vertex_buffer_layout.bind();
	m_vertex_buffer.bind();
}

bool Buffer::create(const uint32_t& object_count_reserved)
{
	if (!m_points_per_object) {
		std::cout << "[ERROR] Buffer.cpp: Cannot create buffer. Points per object undefined\n";
	}

	return _create(object_count_reserved * m_points_per_object);
}

void Buffer::update(void* data, const uint32_t& object_count)
{
	bind();

	m_vertex_buffer.update(data, m_vertice_size, object_count * m_points_per_object);
}

void Buffer::update(void* data, const uint32_t& object_count, const uint32_t& object_count_offset)
{
	bind();

	m_vertex_buffer.update(data, m_vertice_size, object_count * m_points_per_object, object_count_offset * m_points_per_object);
}

void Buffer::reset(const uint32_t& object_count_offset)
{
	float* data = new float[m_vertice_size * m_points_per_object / sizeof(float)]{};

	bind();

	m_vertex_buffer.update((void*)data, m_vertice_size, m_points_per_object, object_count_offset * m_points_per_object);

	delete[] data;
}

void Buffer::draw()
{
	bind();

	glDrawArrays(static_cast<GLenum>(m_vertex_buffer.getUsage()), 0, m_vertex_buffer.getVerticeCount());
}


IndexedBuffer::IndexedBuffer()
	:
	m_object_size(0)
{
}

IndexedBuffer::IndexedBuffer(	const DrawType& draw_type,
								const Usage& usage, 
								const std::vector<uint32_t>& vertex_dims, 
								const std::vector<uint32_t>& pattern)
	:
	AbstractBuffer(draw_type, usage, vertex_dims),
	m_index_buffer(draw_type, pattern),
	m_object_size(m_vertice_size * m_index_buffer.getVerticeCountPerFigure())
{

}

bool IndexedBuffer::create(const uint32_t& object_count_reserved)
{
	if (!isCreationPossible() || !m_index_buffer.isCreationPossible()) {
		return false;
	}

	_create(object_count_reserved * m_index_buffer.getVerticeCountPerFigure());
	m_index_buffer.create(object_count_reserved * m_index_buffer.getIndiceCountPerFigure());


	return true;
}

void IndexedBuffer::update(void* data, const uint32_t& object_count)
{
	bind();

	m_vertex_buffer.update(data, m_object_size, object_count);
	m_index_buffer.fillUsingPattern(object_count);
}

void IndexedBuffer::update(void* data, const uint32_t& object_count, const uint32_t& object_count_offset)
{
	bind();

	m_vertex_buffer.update(data, m_object_size, object_count, object_count_offset);
	m_index_buffer.fillUsingPattern(object_count, object_count_offset);
}

void IndexedBuffer::reset(const uint32_t& object_count_offset)
{
	float* data = new float[m_object_size / sizeof(float)];

	bind();

	m_vertex_buffer.update((void *)data, m_object_size, 1, object_count_offset);
	delete[] data;
}

void IndexedBuffer::bind() const
{
	m_vertex_buffer_layout.bind();
	m_vertex_buffer.bind();
	m_index_buffer.bind();
}

void IndexedBuffer::setPattern(const std::vector<uint32_t>& pattern)
{
	m_index_buffer.setPattern(pattern);
	m_object_size = m_vertice_size * m_index_buffer.getVerticeCountPerFigure();
}

void IndexedBuffer::draw()
{
	bind();

	glDrawElements(static_cast<GLenum>(m_vertex_buffer.getUsage()), m_index_buffer.getIndiceCount(), GL_UNSIGNED_INT, (const void*)0);
}


void AutomaticBuffer::create(const uint32_t& object_count)
{
	if (!m_buffer) {
		std::cout << "[ERROR] Buffer.cpp: Buffer is undefined\n";
		return;
	}
	m_buffer->create(object_count);
	addRange(0, object_count);
}

void AutomaticBuffer::update(float* data, const uint32_t& id)
{
	m_buffer->update((void*)data, 1, id);
}

void AutomaticBuffer::reset(const uint32_t& id)
{
	m_buffer->reset(id);
}
