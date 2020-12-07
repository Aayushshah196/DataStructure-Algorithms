#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
class Node
{
private:
	sf::CircleShape circle;
	sf::Text text;
	Node* parent;
	int val;
public:
	int rank;
	Node(sf::Font& font);
	typedef std::shared_ptr<Node> nodePtr;
	void setPosition(float x, float y);
	void setValue(int value);
	int getValue();
	sf::Vector2f getPosition();
	void draw(sf::RenderTarget& target);
	Node* getParent();
	void setParent(Node* parent);
	bool contains(int& x, int& y);
};

