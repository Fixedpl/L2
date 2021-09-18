#pragma once
#include "VertexBuffer.h"

#include <vector>

#include "IndexBuffer.h"
#include "IDHandler.h"

class AbstractBuffer
{
public:

	virtual ~AbstractBuffer() {};

	virtual void bind() const = 0;

	virtual bool create(const uint32_t& object_count_reserved) = 0;

	virtual void update(void* data, const uint32_t& object_count) = 0;
	virtual void update(void* data, const uint32_t& object_count, const uint32_t& object_count_offset) = 0;

	virtual void reset(const uint32_t& object_count_offset) = 0;

	DrawType getDrawType() const { return m_vertex_buffer.getDrawType(); }
	void setDrawType(const DrawType& draw_type) { m_vertex_buffer.setDrawType(draw_type); }

	Usage getUsage() const { return m_vertex_buffer.getUsage(); }
	void setUsage(const Usage& usage) { m_vertex_buffer.setUsage(usage); }

	std::vector<uint32_t> getVertexDimensions() const { return m_vertex_dims; }
	void setVertexDimensions(const std::vector<uint32_t>& vertex_dims);

	virtual void draw() = 0;

protected:

	AbstractBuffer();
	AbstractBuffer(const DrawType& draw_type, const Usage& usage, const std::vector<uint32_t>& vertex_dims);

	bool _create(const uint32_t& object_count_reserved);

	void extractVerticeDetails();

	bool isCreationPossible() const;

protected:

	VertexBuffer m_vertex_buffer;
	VertexBufferLayout m_vertex_buffer_layout;

	std::vector<uint32_t> m_vertex_dims;

	uint32_t m_vertice_size;

};

class Buffer : public AbstractBuffer
{
public:

	Buffer();
	Buffer(	const DrawType& draw_type, 
			const Usage& usage, 
			const std::vector<uint32_t>& vertex_dims, 
			const uint32_t& points_per_object);
	
	bool create(const uint32_t& object_count_reserved);

	void update(void* data, const uint32_t& object_count);
	void update(void* data, const uint32_t& object_count, const uint32_t& object_count_offset);

	void reset(const uint32_t& object_count_offset);

	void draw();

	uint32_t getPointsPerOjbect() const { return m_points_per_object; }
	void setPointsPerObject(const uint32_t& points_per_object) { m_points_per_object = points_per_object; }

	void bind() const;

private:

	uint32_t m_points_per_object;

};

class IndexedBuffer : public AbstractBuffer
{
public:

	IndexedBuffer();
	IndexedBuffer(	const DrawType& draw_type, 
					const Usage& usage, 
					const std::vector<uint32_t>& vertex_dims,
					const std::vector<uint32_t>& pattern);

	bool create(const uint32_t& object_count_reserved);

	void update(void* data, const uint32_t& object_count);
	void update(void* data, const uint32_t& object_count, const uint32_t& object_count_offset);

	void reset(const uint32_t& object_count_offset);

	std::vector<uint32_t> getPattern() const { return m_index_buffer.getPattern(); }
	void setPattern(const std::vector<uint32_t>& pattern);

	void draw();

	void bind() const;

private:

	IndexBuffer m_index_buffer;

	uint32_t m_object_size;

};

class AutomaticBuffer : private IDHandler
{
public:

	AutomaticBuffer() : m_buffer(nullptr) {}
	AutomaticBuffer(AbstractBuffer* buffer) : m_buffer(buffer) {}

	void create(const uint32_t& object_count);

	void update(float* data, const uint32_t& id);

	void reset(const uint32_t& id);

	uint32_t pullId() { return top(); }

	void pushId(const uint32_t& id) { add(id); }

	AbstractBuffer* getBuffer() { return m_buffer; }
	void setBuffer(AbstractBuffer* buffer) { m_buffer = buffer; }

	void draw() { return m_buffer->draw(); }

private:

	AbstractBuffer* m_buffer;

};

