#pragma once

#include <cmath>
#include "Node.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Edge
{
private:
	Node* node1;
	Node* node2;
	sf::RectangleShape rect;
	float weight;
public:
	Edge();
	Edge(Node* node1, Node* node2);
	void draw(sf::RenderWindow& window);
	void setNodes(Node* node1, Node* node2);
	float getWeight();
	void setColor(int type = -1);
	void setWeight(float x);
	Node* getNode1();
	Node* getNode2();
};

