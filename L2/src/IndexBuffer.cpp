#include "IndexBuffer.h"

#include <iostream>

#include "gl.h"

IndexBuffer::IndexBuffer()
	:
	m_id(0),
	m_indice_count(0),
	m_draw_type(DrawType::UNDEFINED),
	m_vertice_count_per_figure(0),
	m_indice_count_per_figure(0)
{
}

IndexBuffer::IndexBuffer(const DrawType& draw_type, const std::vector<uint32_t>& pattern)
	:
	m_id(0),
	m_indice_count(0),
	m_draw_type(draw_type), 
	m_pattern(pattern),
	m_vertice_count_per_figure(0),
	m_indice_count_per_figure(0)
{
	calculateFigureDetails();
}

IndexBuffer::~IndexBuffer()
{
	if (m_id) {
		glDeleteBuffers(1, &m_id);
	}
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

bool IndexBuffer::create(const uint32_t& indice_count_reserved)
{
	if (!isCreationPossible()) {
		return false;
	}

	if (!m_id) {
		glGenBuffers(1, &m_id);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_count_reserved * sizeof(uint32_t), nullptr, (GLenum)m_draw_type);

	return true;
}

void IndexBuffer::fillUsingPattern(const uint32_t& object_count)
{
	
	uint32_t* arr = new uint32_t[object_count * m_indice_count_per_figure];
	fillArrayWithPattern(arr, object_count, 0);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
					0, 
					sizeof(uint32_t) * m_indice_count_per_figure * object_count,
					arr);

	m_indice_count = object_count * m_indice_count_per_figure;
	delete[] arr;
}

void IndexBuffer::fillUsingPattern(const uint32_t& object_count, const uint32_t& object_count_offset)
{
	uint32_t* arr = new uint32_t[object_count * m_indice_count_per_figure];
	fillArrayWithPattern(arr, object_count, m_vertice_count_per_figure * object_count_offset);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 
					sizeof(uint32_t) * m_indice_count_per_figure * object_count_offset, 
					sizeof(uint32_t) * m_indice_count_per_figure * object_count,
					arr);

	uint32_t candidate_count = (object_count + object_count_offset) * m_indice_count_per_figure;
	if (candidate_count > m_indice_count) {
		m_indice_count = candidate_count;
	}
	delete[] arr;
}

void IndexBuffer::update(uint32_t* data, const uint32_t& indice_count)
{
	if (indice_count > m_indice_count) {
		m_indice_count = indice_count;
	}
		
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indice_count * sizeof(uint32_t), data);
}

void IndexBuffer::update(uint32_t* data, const uint32_t& indice_count, const uint32_t& count_offset)
{
	if (indice_count + count_offset > m_indice_count) {
		m_indice_count = indice_count + count_offset;
	}
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count_offset, indice_count * sizeof(uint32_t), data);
}

void IndexBuffer::setPattern(const std::vector<uint32_t>& pattern)
{
	m_pattern = pattern;
	calculateFigureDetails();
}

bool IndexBuffer::isCreationPossible() const
{
	if (m_pattern.empty()) {
		std::cout << "[ERROR] IndexBuffer.cpp: Couldn't create index buffer. Pattern is undefined" << std::endl;
		return false;
	}

	if (m_draw_type == DrawType::UNDEFINED) {
		std::cout << "[ERROR] IndexBuffer.cpp: Couldn't create index buffer. Draw type is undefined" << std::endl;
		return false;
	}
	return true;
}

void IndexBuffer::calculateFigureDetails()
{
	uint32_t max_number_in_pattern = 0;
	for (uint32_t number : m_pattern) {
		max_number_in_pattern = std::max(max_number_in_pattern, number);
	}

	m_vertice_count_per_figure = max_number_in_pattern + 1;
	m_indice_count_per_figure = m_pattern.size();
}

void IndexBuffer::fillArrayWithPattern(uint32_t* arr, const uint32_t& object_count, const uint32_t& starting_value)
{
	uint32_t next_starting_value = starting_value;
	for (uint32_t i = 0; i < object_count; i += m_indice_count_per_figure) {
		for (uint32_t j = 0; j < m_indice_count_per_figure; ++j) {
			arr[i + j] = m_pattern[j] + next_starting_value;
		}
		next_starting_value += m_indice_count_per_figure + 1;
	}
}

