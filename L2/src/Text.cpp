#include "Text.h"

#include <cstdint>

#include "Renderer.h"

extern struct Character c[128];

Text::Text(Renderer* renderer, Texture* font_texture)
	:
	m_renderer(renderer),
	m_font_texture(font_texture)
{
}

Text::Text(Renderer* renderer, Texture* font_texture, const std::string& caption)
	:
	m_renderer(renderer),
	m_font_texture(font_texture)
{
	setCaption(caption);
}

Text::Text(Renderer* renderer, Texture* font_texture, const std::string& caption, const glm::vec3& _pos)
	:
	m_renderer(renderer),
	m_font_texture(font_texture),
	pos(_pos)
{
	setCaption(caption);
}

Text::~Text()
{
	for (auto& sprite : m_caption) {
		delete sprite;
	}
}

void Text::setCaption(const std::string& caption, const float& font_size)
{
	float x_offset = 0;
	float font_texture_height = m_font_texture->getHeight();

	float font_size_portion = font_size / 128.0f;

	for (uint32_t i = 0; i < caption.size(); ++i) {
		Character& character_data = c[caption[i]];

		glm::vec3 sprite_pos = pos;
		sprite_pos.x += x_offset + font_size_portion * character_data.bearingX;
		sprite_pos.y += font_size_portion * character_data.bearingY - font_size_portion * character_data.height;

		x_offset += font_size_portion * character_data.width + font_size_portion * character_data.bearingX;

		m_caption.push_back(new Sprite(m_renderer, &character_data.texture, sprite_pos, font_size_portion * character_data.width, font_size_portion * character_data.height));
	}

	redraw();
}

void Text::setRenderer(Renderer* renderer)
{
	m_renderer = renderer;
}

void Text::redraw()
{
	for (auto& character : m_caption) {
		m_renderer->draw(character);
	}
}
