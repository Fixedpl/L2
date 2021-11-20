#pragma once

#include <cstdint>
#include <string>

#include <glm/glm.hpp>


struct TexCoords
{

	TexCoords();
	TexCoords(const glm::vec2& _top_left, const glm::vec2& _bot_right);
	TexCoords(const glm::vec2& _top_left, const glm::vec2& _bot_left, const glm::vec2& _bot_right, const glm::vec2& _top_right);

	glm::vec2 top_left, bot_left, bot_right, top_right;

};


class TextureSource
{
public:

	TextureSource();
	TextureSource(const uint32_t& texture_slot);


	virtual TexCoords getTextureCoordinatesNormalised() = 0;

	inline float getTextureSlot() { return m_texture_slot; };

	void setTextureSlot(const float& texture_slot);

protected:

	float m_texture_slot;

};

class Texture : public TextureSource
{
public:

	Texture();
	Texture(const uint32_t& texture_slot);
	Texture(const uint32_t& texture_slot, const std::string& path);
	~Texture();

	void loadTexture(const std::string& path);

	TexCoords getTextureCoordinatesNormalised();

	inline int32_t getWidth() const { return m_width; };
	inline int32_t getHeight() const { return m_height; };

private:

	void activateSlot(const uint32_t& texture_slot);

	void bind() const;

private:

	uint32_t m_id;

	int32_t m_width, m_height, m_BPP;
};



class TexturePart : public TextureSource
{
public:

	TexturePart();
	TexturePart(Texture* source);
	TexturePart(Texture* source, const TexCoords& tex_coords_rel);
	TexturePart(Texture* source, const glm::vec2& top_left_rel, const glm::vec2& bot_right_rel);

	void setSource(Texture* source);

	TexCoords setTextureCoords(const TexCoords& tex_coords_rel);
	TexCoords setTextureCoords(const glm::vec2& top_left_rel, const glm::vec2& bot_right_rel);
	TexCoords setTextureCoords(const glm::vec2& top_left_rel, const glm::vec2& bot_left_rel, const glm::vec2& bot_right_rel, const glm::vec2& top_right_rel);

	TexCoords getTextureCoordinatesNormalised();

	inline float getWidth() const { return m_width; }
	inline float getHeight() const { return m_height; }

private:

	Texture* m_source_texture;

	TexCoords m_tex_coords;

	float m_width, m_height;

};

