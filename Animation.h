#pragma once
#include <SFML/Graphics.hpp>
#include "./helper/WindowManager.h"
#include <memory>
class Animation
{
public:
	Animation();
	void run();
	void processInput();
	void render();
	void update(sf::Time dt);
private:
	static const sf::Time timePerFrame;
	sf::RenderWindow window;
	WindowManager windowManager;
};

