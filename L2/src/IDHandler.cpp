#include "IDHandler.h"


IDHandler::IDHandler(const uint32_t& starting_n)
{
	addRange(0, starting_n);
}

void IDHandler::addRange(const uint32_t& left, const uint32_t& right)
{
	for (uint32_t i = left; i < right; i++) {
		m_ids.push(i);
	}
}

void IDHandler::add(const uint32_t& id)
{
	m_ids.push(id);
}

uint32_t IDHandler::top()
{
	uint32_t top = m_ids.top();
	m_ids.pop();
	return top;
}