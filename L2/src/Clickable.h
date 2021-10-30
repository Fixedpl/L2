#pragma once
#include <glm/glm.hpp>

#include "Primitive.h"
#include "dllexport.h"

class LE_API Clickable
{
public:

	virtual void onClick() = 0;

};


class LE_API ClickablePinch : virtual public Clickable, virtual public Pinch
{
public:

	ClickablePinch() {}

};
