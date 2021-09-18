#include "Renderer.h"
#include "Drawable.h"

Renderer::~Renderer()
{
	for (auto& container : m_containers) {
		delete container.buffer->getBuffer();
		delete container.buffer;
	}
}

void Renderer::draw()
{
	for (auto& container : m_containers) {
		container.shader->bind();
		container.buffer->draw();
	}
}

void Renderer::draw(Drawable* drawable)
{
	State state = drawable->getState();
	m_containers[state.entry.container].buffer->update(state.data, state.entry.id);
	delete[] state.data;
}

Entry Renderer::getSpriteEntry(const uint32_t& tex_id)
{
	return Entry(tex_id + 4, m_containers[tex_id + 4].buffer->pullId());
}

Entry Renderer::getRectangleEntry()
{
	return Entry(0, m_containers[0].buffer->pullId());
}

Entry Renderer::getCircleEntry()
{
	return Entry(1, m_containers[1].buffer->pullId());
}

Entry Renderer::getLineEntry()
{
	return Entry(2, m_containers[2].buffer->pullId());
}

Entry Renderer::getPointEntry()
{
	return Entry(3, m_containers[3].buffer->pullId());
}

void Renderer::releaseEntry(const Entry& entry)
{
	m_containers[entry.container].buffer->pushId(entry.id);
	m_containers[entry.container].buffer->reset(entry.id);
}

void Renderer::init()
{
	Shader* default33_shader = m_shader_system.loadShader("res/shader/vertexShader.vert", "res/shader/fragmentShader.frag");
	Shader* circle_shader = m_shader_system.loadShader("res/shader/vertexShaderCircle.vert", "res/shader/fragmentShaderCircle.frag");
	Shader* texture_shader = m_shader_system.loadShader("res/shader/vertexShaderTexture.vert", "res/shader/fragmentShaderTexture.frag");
	
	texture_shader->bind();

	for (uint32_t i = 0; i < 32; ++i) {
		texture_shader->setUniform1i("u_texture[" + std::to_string(i) + "]", i);
	}

	for (uint32_t i = 0; i < 10; ++i) {

		AutomaticBuffer* abt = new AutomaticBuffer(
									new IndexedBuffer(
										DrawType::DYNAMIC, Usage::TRIANGLE,
										std::vector<uint32_t>{ 3, 3, 2, 1 },
										std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3}));
		abt->create(100);
		m_containers.emplace_back(Container(abt, texture_shader));
	}

	IndexedBuffer* rectangle_buf = new IndexedBuffer(
									DrawType::DYNAMIC, Usage::TRIANGLE,
									std::vector<uint32_t>{ 3, 3 },
									std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3});

	IndexedBuffer* circle_buf = new IndexedBuffer(
									DrawType::DYNAMIC, Usage::TRIANGLE,
									std::vector<uint32_t>{ 3, 3, 3 },
									std::vector<uint32_t>{ 0, 1, 2, 0, 2, 3});

	Buffer* line_buf = new Buffer(
						DrawType::DYNAMIC,
						Usage::LINE,
						std::vector<uint32_t>{ 3, 3 }, 
						2);

	Buffer* point_buf = new Buffer(
						DrawType::DYNAMIC,
						Usage::POINT,
						std::vector<uint32_t>{ 3, 3 },
						1);

	AutomaticBuffer* rectangle_buffer = new AutomaticBuffer(rectangle_buf);
	AutomaticBuffer* circle_buffer = new AutomaticBuffer(circle_buf);
	AutomaticBuffer* line_buffer = new AutomaticBuffer(line_buf);
	AutomaticBuffer* point_buffer = new AutomaticBuffer(point_buf);

	rectangle_buffer->create(20000);
	circle_buffer->create(10000);
	line_buffer->create(10000);
	point_buffer->create(10000);

	
	m_containers.emplace_back(Container(rectangle_buffer, default33_shader));
	m_containers.emplace_back(Container(circle_buffer, circle_shader));
	m_containers.emplace_back(Container(line_buffer, default33_shader));
	m_containers.emplace_back(Container(point_buffer, default33_shader));
}
