#pragma once

#include "Renderer.h"

class Drawable
{
public:

	Drawable() {}
	Drawable(const Entry& entry) : m_entry(entry) {}
	virtual ~Drawable() {}

	Drawable(const Drawable& drawable) = delete;
	Drawable& operator=(const Drawable& drawable) = delete;

protected:

	virtual State getState() = 0;

protected:

	Entry m_entry;

	friend class Renderer;
};




