#pragma once

#include <queue>


class IDHandler
{
public:

	IDHandler() {};
	IDHandler(const uint32_t& starting_n);

	// [left, right)
	void addRange(const uint32_t& left, const uint32_t& right);

	void add(const uint32_t& id);

	uint32_t top();

private:

	std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> m_ids;

};

