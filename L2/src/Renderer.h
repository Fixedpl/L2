#pragma once
#include <vector>

#include "Buffer.h"
#include "ShaderSystem.h"
#include "dllexport.h"

class BufferFiller;
class Drawable;

struct Container
{
	Container() : buffer(nullptr), shader(nullptr) {}
	Container(AutomaticBuffer* _buffer, Shader* _shader) : buffer(_buffer), shader(_shader) {}

	AutomaticBuffer* buffer;
	Shader* shader;
};

struct Entry
{
	Entry() : container(0), id(0) {}
	Entry(const uint32_t& _container, const uint32_t& _id) : container(_container), id(_id) {}

	uint32_t container;
	uint32_t id;
};

struct State
{
	State() : data(nullptr) {}
	State(const Entry& _entry, float* _data) : entry(_entry), data(_data) {}
	Entry entry;
	float* data;
};

class LE_API Renderer
{
public:

	Renderer();
	~Renderer();

	void draw(const State& state);
	void draw(BufferFiller* drawable);
	void draw(Drawable* custom_drawable);

	Entry getSpriteEntry(const uint32_t& tex_id);
	Entry getRectangleEntry();
	Entry getCircleEntry();
	Entry getLineEntry();
	Entry getPointEntry();

	void releaseEntry(const Entry& entry);

protected:

	void draw();

private:

	void init();

protected:

	ShaderSystem m_shader_system;

private:

	std::vector<Container> m_containers;
	
};

