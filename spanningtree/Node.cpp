#include "Node.h"
#include <string>

Node::Node(sf::Font& font) 
{
	circle.setFillColor(sf::Color::White);
	circle.setOutlineThickness(1);
	circle.setOutlineColor(sf::Color::Blue);
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Blue);
	this->parent = NULL;
	val = -1;
	rank = 0;
}

void Node::setPosition(float x, float y)
{
	circle.setPosition(sf::Vector2f(x, y));
	text.setPosition(sf::Vector2f(x - text.getGlobalBounds().width / 2, y - text.getGlobalBounds().height/1.2));
}

void Node::setValue(int value)
{
	this->val = value;
	text.setString(std::to_string(value));
	circle.setRadius(30.0 );
	circle.setOrigin(circle.getRadius(), circle.getRadius());
}

int Node::getValue()
{
	return val;
}

sf::Vector2f Node::getPosition()
{
	return this->circle.getPosition();
}

void Node::draw(sf::RenderTarget& target)
{
	target.draw(circle);
	target.draw(text);
}

Node* Node::getParent()
{
	return this->parent;
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}

bool Node::contains(int& x, int& y)
{
	return circle.getGlobalBounds().contains(sf::Vector2f(x, y));
}
