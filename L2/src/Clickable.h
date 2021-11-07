#pragma once
#include <glm/glm.hpp>

#include "Primitive.h"

class Clickable
{
public:

	virtual void onClick() = 0;

};


class ClickablePinch : virtual public Clickable, virtual public Pinch
{
public:

};
