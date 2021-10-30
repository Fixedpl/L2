#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "Transformable.h"
#include "dllexport.h"

class LE_API Pinch
{
public:

	virtual bool perforates(const glm::vec2& point) = 0;

};

class LE_API Colorable
{
public:

	Colorable(const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::vec4 getColor() const;
	virtual void setColor(const glm::vec4& color);

protected:

	glm::vec4 m_color;

};

class LE_API RectangleBase : virtual public Transformable, virtual public Pinch
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

class LE_API CircleBase : virtual public Transformable, virtual public Pinch
{
public:

	CircleBase(const float& radius);

	float getRadius() const;
	void setRadius(const float& radius);

	bool perforates(const glm::vec2& point);

protected:

	float m_radius;

};

class LE_API LineBase : virtual public Transformable, virtual public Pinch
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


class LE_API PointBase : virtual public Transformable, virtual public Pinch
{
public:

	PointBase(const glm::vec3& point);

	bool perforates(const glm::vec2& point);

};
