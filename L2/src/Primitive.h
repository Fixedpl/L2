#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "Transformable.h"


class Pinch
{
public:

	virtual bool perforates(const glm::vec2& point) = 0;

};


class RectangleBase : virtual public Transformable, virtual public Pinch
{
public:

	RectangleBase(const float& width, const float& height);

	float getWidth() const;
	void setWidth(const float& width);

	float getHeight() const;
	void setHeight(const float& height);

	bool perforates(const glm::vec2& point);

protected:

	float m_width, m_height;

};

class CircleBase : virtual public Transformable, virtual public Pinch
{
public:

	CircleBase(const float& radius);

	float getRadius() const;
	void setRadius(const float& radius);

	bool perforates(const glm::vec2& point);

protected:

	float m_radius;

};

class LineBase : virtual public Transformable, virtual public Pinch
{
public:

	LineBase(const glm::vec3& start, const glm::vec3& finish);


	glm::vec3 getLineStart() const;
	void setLineStart(const glm::vec3& start);

	glm::vec3 getLineFinish() const;
	void setLineFinish(const glm::vec3& finish);

	bool perforates(const glm::vec2& point);

protected:

	glm::vec3 m_start, m_finish;

};


class PointBase : virtual public Transformable, virtual public Pinch
{
public:

	PointBase(const glm::vec3& point);

	bool perforates(const glm::vec2& point);

};
