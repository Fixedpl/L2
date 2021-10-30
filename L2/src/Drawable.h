#pragma once
#include "Primitive.h"
#include "Texture.h"
#include "Transformable.h"
#include "RenderWindow.h"
#include "dllexport.h"

class LE_API Drawable : public Colorable
{
public:

	Drawable(const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// This function should call draw on
	// basic primitives or other custom drawables
	virtual void draw() = 0;

};

class LE_API DrawableTransformable : virtual public Drawable, virtual public Transformable
{
public:

	DrawableTransformable() {}


};

class LE_API BufferFiller : virtual public Drawable
{
protected:

	BufferFiller(RenderWindow* renderer,
				 const Entry& entry, 
				 const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	virtual ~BufferFiller();

	BufferFiller(const BufferFiller& drawable) = delete;
	BufferFiller& operator=(const BufferFiller& drawable) = delete;

	virtual uint32_t getArraySize() const = 0;

	virtual void populateBuffer(float* data) = 0;

	State getState();

	void draw();

protected:

	RenderWindow* m_renderer;

	Entry m_entry;

	friend class RenderWindow;
	friend class Renderer;

};


class LE_API Sprite : public RectangleBase, public BufferFiller, public DrawableTransformable
{
public:

	Sprite(RenderWindow* renderer,
		   TextureSource* texture_source, 
		   const glm::vec3& pos, 
		   const float& width, 
		   const float& height, 
		   const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// TEXT ONLY CONSTRUCTOR
	Sprite(RenderWindow* renderer,
		   TextureSource* texture_source, 
		   const glm::vec3& pos, 
		   const float& width, 
		   const float& height, 
		   const uint32_t& text_size, 
		   const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

private:

	inline uint32_t getArraySize() const;

	void populateBuffer(float* data);

private:

	TextureSource* m_texture_source;

};

class LE_API Rectangle : public RectangleBase, public BufferFiller, public DrawableTransformable
{
public:

	Rectangle(RenderWindow* renderer,
			  const glm::vec3& pos, 
			  const float& width, 
			  const float& height, 
			  const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

private:

	inline uint32_t getArraySize() const;

	void populateBuffer(float* data);

};

class LE_API Circle : public CircleBase, public BufferFiller, public DrawableTransformable
{
public:

	Circle(RenderWindow* renderer,
		   const glm::vec3& pos, 
		   const float& radius, 
		   const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

private:

	inline uint32_t getArraySize() const;

	void populateBuffer(float* data);

};

class LE_API Line : public LineBase, public BufferFiller, public DrawableTransformable
{
public:

	Line(RenderWindow* renderer,
		 const glm::vec3& pos1, 
		 const glm::vec3& pos2, 
		 const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

private:

	inline uint32_t getArraySize() const;

	void populateBuffer(float* data);

};

class LE_API Point : public PointBase, public BufferFiller, public DrawableTransformable
{
public:

	Point(RenderWindow* renderer,
		  const glm::vec3& pos, 
		  const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	
private:

	inline uint32_t getArraySize() const;

	void populateBuffer(float* data);

};

