#pragma once
#include <iostream>
#include "RenderWindow.h"
#include "Drawable.h"
#include "Text.h"



class Game : protected RenderWindow
{
public:
	
	Game();
	~Game();

	void run();

protected:

	void onEvent(const float& frame_time);
	void onUpdate(const float& frame_time);	

private:

	static constexpr uint32_t m_window_width = 1280;
	static constexpr uint32_t m_window_height = 720;

	Rectangle* rect;

	Texture tex3;
	TexturePart tex2;
	Texture font_tex;
	Text* title;
	Circle* test_circle;

	Sprite* sprite2;

	bool once = false;

	Animation* test_animation;

};

