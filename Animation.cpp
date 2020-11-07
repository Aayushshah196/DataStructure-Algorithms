#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "Menu.h"

const sf::Time Animation::timePerFrame = sf::seconds(1.f / 60.f);

Animation::Animation() :window(sf::VideoMode::getDesktopMode(), "DSA")
{
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	std::unique_ptr<Window> menu(new Menu(windowManager, window));
	windowManager.changeScene(std::move(menu));
}
void Animation::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (windowManager.isRunning())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			processInput();
			update(timePerFrame);
		}
		render();
	}

}

void Animation::processInput()
{
	windowManager.processEvents();
}

void Animation::render()
{
	windowManager.draw();
	window.setView(window.getDefaultView());

}
void Animation::update(sf::Time dt)
{
	windowManager.update(dt);
}
