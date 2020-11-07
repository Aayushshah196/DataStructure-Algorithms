#include "Button.h"
#include <iostream>

Button::Button() : text()
{
}

void Button::setAttributes(const std::string& text, int size, sf::Font& font)
{
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFont(font);
}

void Button::render(sf::RenderTarget& renderer)
{
    renderer.draw(text);
}

sf::FloatRect Button::getGlobalBounds()
{
    return text.getGlobalBounds();
}

void Button::setColor(const sf::Color color)
{
    this->text.setFillColor(color);
}

void Button::setPos(const sf::Vector2f& pos)
{
    position = pos;
    text.setPosition(position);
}
int Button::getSize()
{
    return text.getGlobalBounds().width;
}