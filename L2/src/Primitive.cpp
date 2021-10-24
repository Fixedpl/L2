#include "Primitive.h"

RectangleBase::RectangleBase(const glm::vec3& pos, const float& width, const float& height, const glm::vec4& color)
	: Colorable(color), m_width(width), m_height(height)
{
	setPosition(pos);
}

float RectangleBase::getWidth() const
{
	return m_width;
}

void RectangleBase::setWidth(const float& width)
{
	m_width = width;
}

float RectangleBase::getHeight() const
{
	return m_height;
}

void RectangleBase::setHeight(const float& height)
{
	m_height = height;
}

CircleBase::CircleBase(const glm::vec3& pos, const float& radius, const glm::vec4& color)
	: Colorable(color), m_radius(radius)
{
	setPosition(pos);
}

float CircleBase::getRadius() const
{
	return m_radius;
}

void CircleBase::setRadius(const float& radius)
{
	m_radius = radius;
}

LineBase::LineBase(const glm::vec3& start, const glm::vec3& finish, const glm::vec4& color)
	: Colorable(color), m_finish(finish)
{
	setPosition(start);
}


glm::vec3 LineBase::getLineStart() const
{
	return getPosition();
}

void LineBase::setLineStart(const glm::vec3& start)
{
	setPosition(start);
}

glm::vec3 LineBase::getLineFinish() const
{
	return m_finish;
}

void LineBase::setLineFinish(const glm::vec3& finish)
{
	m_finish = finish;
}

PointBase::PointBase(const glm::vec3& pos, const glm::vec4& color)
	: Colorable(color)
{
	setPosition(pos);
}

glm::vec4 Colorable::getColor() const
{
	return m_color;
}

void Colorable::setColor(const glm::vec4& color)
{
	m_color = color;
}
