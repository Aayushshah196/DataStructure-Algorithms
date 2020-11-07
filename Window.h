#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class WindowManager;

class Window
{
public:
    Window(WindowManager& windowManager, sf::RenderWindow& window)
        : windowManager{ windowManager }
        , window{ window }
    {
        sf::Cursor cursor;
        if (cursor.loadFromSystem(sf::Cursor::Hand))
            window.setMouseCursor(cursor);
    }

    virtual ~Window() {}

    virtual void processEvents() = 0;
    virtual void update(const sf::Time& dt) = 0;
    virtual void draw() = 0;
protected:
    WindowManager& windowManager;
    sf::RenderWindow& window;
};