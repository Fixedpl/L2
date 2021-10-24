#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "Drawable.h"




struct Character
{
	TexturePart texture;
	float width, height;
	float bearing_left, bearing_right, bearing_bot, bearing_top;
	float advance;
	float size;
};

class Text : public DrawableTransformable, public Colorable
{
public:

	Text(Renderer* renderer, 
		 const std::string& caption, 
		 const uint32_t& font_size = 12,
		 const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f),
		 const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	~Text();
	
	static void setFontTexture(Texture* font_texture) { m_font_texture = font_texture; }

	static void loadFontData(const std::string& font_data_path);

	std::string getCaption() const;
	void setCaption(const std::string& caption);

	uint32_t getFontSize() const;
	void setFontSize(const uint32_t& font_size);

protected:

	void setCaption(const std::string& caption, const uint32_t& font_size, const glm::vec4& font_color);

	void draw();

private:

	bool m_requires_update;

	std::string m_caption;

	uint32_t m_font_size;

	std::vector<Sprite*> m_sprite_caption;
		
	Renderer* m_renderer;

	static Texture* m_font_texture;

};
