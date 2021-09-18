#pragma once

#include <glm/glm.hpp>

#include "Renderer.h"
#include "Drawable.h"
#include "Texture.h"



struct Color
{
	Color() : r(0.0f), g(0.0f), b(0.0f) {}
	Color(const float& _r, const float& _g, const float& _b) : r(_r), g(_g), b(_b) {}

	float r, g, b;

};

class Shape : public Drawable
{
public:

	Color color;

	glm::mat4 transform;

public:

	Shape(const Color& _color = Color(1.0f, 1.0f, 1.0f)) : transform(1.0f), color(_color) {}
	Shape(Renderer* renderer, const Entry& entry, const Color& _color = Color(1.0f, 1.0f, 1.0f)) : Drawable(entry), m_renderer(renderer), transform(1.0f), color(_color) {}
	virtual ~Shape() { m_renderer->releaseEntry(m_entry); }

	virtual glm::vec4 getPosition() const = 0;
	virtual void setPosition(const glm::vec3& position) = 0;

	virtual void setRenderer(Renderer* renderer) = 0;

protected:

	State getState();

	virtual uint32_t getArraySize() const = 0;

	virtual void populateBuffer(float* data) = 0;

protected:

	Renderer* m_renderer;

};

class Rectangle : public Shape
{
public:

	glm::vec4 pos;
	float width, height;

public:

	Rectangle() {}
	Rectangle(Renderer* renderer);
	Rectangle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height);
	Rectangle(Renderer* renderer, const glm::vec3& _pos, const float& _width, const float& _height);
	Rectangle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height, const Color& _color);
	Rectangle(Renderer* renderer, const glm::vec3& _pos, const float& _width, const float& _height, const Color& _color);


	glm::vec4 getPosition() const { return pos; }
	void setPosition(const glm::vec3& position);

	void setRenderer(Renderer* renderer);

protected:

	void populateBuffer(float* data);

	uint32_t getArraySize() const { return 24; }

private:

	glm::vec4 v0, v1, v2, v3;

};


class Circle : public Shape
{
public:

	glm::vec4 pos;
	float radius;

public:

	Circle() {}
	Circle(Renderer* renderer);
	Circle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _radius);
	Circle(Renderer* renderer, const glm::vec3& _pos, const float& _radius);
	Circle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _radius, const Color& _color);
	Circle(Renderer* renderer, const glm::vec3& _pos, const float& _radius, const Color& _color);

	glm::vec4 getPosition() const { return pos; }
	void setPosition(const glm::vec3& position);

	void setRenderer(Renderer* renderer);

protected:

	void populateBuffer(float* data);

	uint32_t getArraySize() const { return 36; }

private:

	glm::vec4 v0, v1, v2, v3;

};

class Line : public Shape
{
public:

	glm::vec4 pos1, pos2;

public:

	Line() {}
	Line(Renderer* renderer);
	Line(Renderer* renderer, const float& _x1, const float& _y1, const float& _z1, const float& _x2, const float& _y2, const float& _z2);
	Line(Renderer* renderer, const glm::vec3& _pos1, const glm::vec3& _pos2);
	Line(Renderer* renderer, const float& _x1, const float& _y1, const float& _z1, const float& _x2, const float& _y2, const float& _z2, const Color& _color);
	Line(Renderer* renderer, const glm::vec3& _pos1, const glm::vec3& _pos2, const Color& _color);

	glm::vec4 getPosition() const { return pos1; }
	void setPosition(const glm::vec3& position);

	void setRenderer(Renderer* renderer);

protected:

	void populateBuffer(float* data);

	uint32_t getArraySize() const { return 12; }

private:

	glm::vec4 v0, v1;

};

class Point : public Shape
{
public:

	glm::vec4 pos;

public:

	Point() {}
	Point(Renderer* renderer);
	Point(Renderer* renderer, const float& _x, const float& _y, const float& _z);
	Point(Renderer* renderer, const glm::vec3& _pos);
	Point(Renderer* renderer, const float& _x, const float& _y, const float& _z, const Color& _color);
	Point(Renderer* renderer, const glm::vec3& _pos, const Color& _color);

	glm::vec4 getPosition() const { return pos; }
	void setPosition(const glm::vec3& position);

	void setRenderer(Renderer* renderer);

protected:

	void populateBuffer(float* data);

	uint32_t getArraySize() const { return 6; }

};

class Sprite : public Shape
{
public:

	glm::vec4 pos;
	float width, height;

public:

	Sprite() {}
	Sprite(Renderer* renderer, TextureSource* source_texture);
	Sprite(Renderer* renderer, TextureSource* source_texture, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height);
	Sprite(Renderer* renderer, TextureSource* source_texture, const glm::vec3& _pos, const float& _width, const float& _height);
	Sprite(Renderer* renderer, TextureSource* source_texture, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height, const Color& _color);
	Sprite(Renderer* renderer, TextureSource* source_texture, const glm::vec3& _pos, const float& _width, const float& _height, const Color& _color);

	glm::vec4 getPosition() const { return pos; }
	void setPosition(const glm::vec3& position);

	void setRenderer(Renderer* renderer);

	void setTextureSource(TextureSource* texture_source);

protected:

	void populateBuffer(float* data);

	uint32_t getArraySize() const { return 36; }

private:

	glm::vec4 v0, v1, v2, v3;

	TextureSource* m_texture_source;

};
