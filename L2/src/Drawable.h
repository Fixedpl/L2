#pragma once
#include "Primitive.h"
#include "Renderer.h"
#include "Texture.h"
#include "Transformable.h"

class Drawable
{
public:

	Drawable() {}

protected:
	// This function should call draw on
	// basic primitives or other custom drawables
	virtual void draw() = 0;

	friend class Renderer;

};

class BufferFiller : public Drawable
{
protected:

	BufferFiller(Renderer* renderer, const Entry& entry) : m_renderer(renderer), m_entry(entry) {}
	virtual ~BufferFiller() { m_renderer->releaseEntry(m_entry); }

	BufferFiller(const BufferFiller& drawable) = delete;
	BufferFiller& operator=(const BufferFiller& drawable) = delete;

	virtual uint32_t getArraySize() const = 0;

	virtual void populateBuffer(float* data) = 0;

	State getState();

	void draw() { m_renderer->draw(getState()); }

protected:

	Renderer* m_renderer;

	Entry m_entry;

	friend class Renderer;

};



class DrawableTransformable : public Drawable, public Transformable
{
public:
	DrawableTransformable(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& origin = glm::vec3(0.0f, 0.0f, 0.0f))
	:
	Transformable(pos, origin)
	{}
};

class Sprite : public RectangleBase, public BufferFiller
{
public:

	Sprite(Renderer* renderer, TextureSource* texture_source, 
		   const glm::vec3& pos, const float& width, const float& height, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		: BufferFiller(renderer, renderer->getSpriteEntry(texture_source->getTextureSlot())),
		  RectangleBase(pos, width, height, color),
		  m_texture_source(texture_source) {}

	// TEXT ONLY CONSTRUCTOR
	Sprite(Renderer* renderer, TextureSource* texture_source, 
		   const glm::vec3& pos, const float& width, const float& height, const uint32_t& text_size, 
		   const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		: BufferFiller(renderer, renderer->getSpriteEntry(0)),
		  RectangleBase(pos, width, height, color),
		  m_texture_source(texture_source) {}


protected:

	inline uint32_t getArraySize() const { return 36; }

	void populateBuffer(float* data);

protected:

	TextureSource* m_texture_source;

};

class Rectangle : public RectangleBase, public BufferFiller
{
public:

	Rectangle(Renderer* renderer, 
			  const glm::vec3& pos, const float& width, const float& height, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		: BufferFiller(renderer, renderer->getRectangleEntry()),
		  RectangleBase(pos, width, height, color) {}

protected:

	inline uint32_t getArraySize() const { return 24; }

	void populateBuffer(float* data);

};

class Circle : public CircleBase, public BufferFiller
{
public:

	Circle(Renderer* renderer,
		   const glm::vec3& pos, const float& radius, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		: BufferFiller(renderer, renderer->getCircleEntry()),
		  CircleBase(pos, radius, color) {}


protected:

	inline uint32_t getArraySize() const { return 24; }

	void populateBuffer(float* data);

};

class Line : public LineBase, public BufferFiller
{
public:

	Line(Renderer* renderer,
		const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		: BufferFiller(renderer, renderer->getLineEntry()),
		  LineBase(pos1, pos2, color) {}


protected:

	inline uint32_t getArraySize() const { return 12; }

	void populateBuffer(float* data);

};

class Point : public PointBase, public BufferFiller
{
public:

	Point(Renderer* renderer,
		  const glm::vec3& pos, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		: BufferFiller(renderer, renderer->getPointEntry()),
		  PointBase(pos, color) {}

protected:

	inline uint32_t getArraySize() const { return 6; }

	void populateBuffer(float* data);

};

