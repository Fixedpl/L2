#pragma once
#include <vector>
#include <cstdint>

#include "DrawTypeEnum.h"

class IndexBuffer
{
public:

	IndexBuffer();
	IndexBuffer(const DrawType& draw_type, const std::vector<uint32_t>& pattern);
	~IndexBuffer();

	void bind() const;

	bool create(const uint32_t& indice_count_reserved);

	void fillUsingPattern(const uint32_t& object_count);
	void fillUsingPattern(const uint32_t& object_count, const uint32_t& object_count_offset);

	void update(uint32_t* data, const uint32_t& indice_count);
	void update(uint32_t* data, const uint32_t& indice_count, const uint32_t& count_offset);

	std::vector<uint32_t> getPattern() const;
	void setPattern(const std::vector<uint32_t>& pattern);

	DrawType getDrawType() const;
	void setDrawType(const DrawType& draw_type);

	uint32_t getIndiceCount() const;

	bool isCreationPossible() const;

	uint32_t getVerticeCountPerFigure() const;
	uint32_t getIndiceCountPerFigure() const;

private:

	void calculateFigureDetails();

	void fillArrayWithPattern(uint32_t* arr, const uint32_t& object_count, const uint32_t& starting_value);

private:

	uint32_t m_id;

	uint32_t m_indice_count;

	DrawType m_draw_type;

	std::vector<uint32_t> m_pattern;
	uint32_t m_vertice_count_per_figure;
	uint32_t m_indice_count_per_figure;
};

