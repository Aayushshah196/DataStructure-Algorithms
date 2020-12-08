#include "WindowManager.h"
#include <iostream>

WindowManager::WindowManager() : running(true)
{
    if (!font.loadFromFile("sansation.ttf"))
    {
        std::cout << "Error on ," << std::endl;
        // error...
    }
}

WindowManager::~WindowManager()
{
    while (!scenes.empty()) {
        popScene();
    }
}

sf::Font& WindowManager::getFont() 
{
    return font;
}
void WindowManager::pushScene(std::unique_ptr<Window> scene)
{
    scenes.push(std::move(scene));
}

void WindowManager::popScene()
{
    scenes.pop();
}

void WindowManager::changeScene(std::unique_ptr<Window> scene)
{
    if (!scenes.empty()) {
        popScene();
    }
    pushScene(std::move(scene));
}

void WindowManager::processEvents()
{
    scenes.top()->processEvents();
}

void WindowManager::update(sf::Time dt)
{
    scenes.top()->update(dt);
}

void WindowManager::draw()
{
    scenes.top()->draw();
}

std::unique_ptr<Window> WindowManager::getCurrentState()
{
    return std::move(scenes.top());
}

bool WindowManager::isRunning()
{
    return running;
}

void WindowManager::quit()
{
    running = false;
}
