#include "Game.h"

#include <glm/gtx/string_cast.hpp>

Game::Game()
	:
	RenderWindow(1280, 720, "Game"),
	tex1(0), tex3(1)
{
	setVSync(false);
	

	tex1.loadTexture("res/texture/adios.png");
	tex3.loadFont("res/font/arial.ttf");

	title.setRenderer(this);
	title.setFontTexture(&tex3);
	title.pos = glm::vec3(200.0f, 500.0f, 0.0f);

	title.setCaption("Adios", 16.0f);

	tex2 = TexturePart(&tex1, TexCoords(glm::vec2(0.0f, 200.0f), glm::vec2(400.0f, 0.0f)));

	sprite.setTextureSource(&tex1);
	sprite.setRenderer(this);
	sprite.pos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	sprite.width = 60.0f;
	sprite.height = 40.0f;
	
	sprite2.setTextureSource(&tex2);
	sprite2.setRenderer(this);
	sprite2.pos = glm::vec4(500.0f, 200.0f, 0.0f, 1.0f);
	sprite2.width  = 60.0f;
	sprite2.height = 40.0f;

	test_animation = new BezierTrajectory(&sprite, glm::vec2(400.0f, 400.0f), 2.0f, glm::vec2(100.0f, 400.0f));

	draw(&sprite);
	draw(&sprite2);

}

void Game::run()
{
	display();
}

void Game::onUpdate(const float& frame_time)
{
	if (isKeyPressed(KEY_W) && !once) {
		once = true;
		pushAnimation(test_animation);
	}
	
}
