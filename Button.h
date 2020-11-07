#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

class Button 
{
public:
    Button();
    typedef std::shared_ptr<Button> buttonPtr;
    void render(sf::RenderTarget& renderer);
    void setPos(const sf::Vector2f& pos);
    void setAttributes(const std::string& text, int size, sf::Font& font);
    sf::FloatRect getGlobalBounds();
    void setColor(const sf::Color color);
    int getSize();

private:
    sf::Vector2f position;
    sf::Text text;
};