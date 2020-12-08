#include "Edge.h"
#include <cmath>
#include <iostream>

Edge::Edge()
{
	this->node1 = NULL;
	this->node2 = NULL;
	this->weight = -1;
}

Edge::Edge(Node* node1, Node* node2)
{
	this->node1 = node1;
	this->node2 = node2;
	if (this->node1->getPosition().y < this->node2->getPosition().y)
		rect.setPosition(this->node1->getPosition());
	else
		rect.setPosition(this->node2->getPosition());
	float angle = (this->node1->getPosition().y - this->node2->getPosition().y) / (this->node1->getPosition().x - this->node2->getPosition().x);
	angle = atan(angle) * 57.2958;
	angle += (angle < 0) ? 90 : -90;
	angle = (angle == 90 || angle == -90) ? -1 * angle : angle;
	this->weight = sqrt(pow(this->node1->getPosition().x - this->node2->getPosition().x, 2) + pow(this->node1->getPosition().y - this->node2->getPosition().y, 2));
	rect.setSize(sf::Vector2f(5, this->weight));
	rect.setRotation(angle);
}

void Edge::draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void Edge::setNodes(Node* node1, Node* node2)
{
	this->node1 = node1;
	this->node2 = node2;
	if (this->node1->getPosition().y < this->node2->getPosition().y)
		rect.setPosition(this->node1->getPosition());
	else
		rect.setPosition(this->node2->getPosition());
	float angle = (this->node1->getPosition().y - this->node2->getPosition().y) / (this->node1->getPosition().x - this->node2->getPosition().x);
	angle = atan(angle) * 57.2958;
	angle += (angle < 0) ? 90 : -90;
	angle = (angle == 90 || angle == -90) ? -1 * angle : angle;
	this->weight = sqrt(pow(this->node1->getPosition().x - this->node2->getPosition().x, 2) + pow(this->node1->getPosition().y - this->node2->getPosition().y, 2));
	rect.setSize(sf::Vector2f(5, this->weight));
	rect.setRotation(angle);
}

float Edge::getWeight()
{
	return this->weight;
	//return sqrt(pow(this->node1->getPosition().x-this->node2->getPosition().x,2) + pow(this->node1->getPosition().y-this->node2->getPosition().y,2));
}

void Edge::setColor(int type)
{
	switch (type)
	{
	case 1:
		rect.setFillColor(sf::Color::Green);
		return;
	case 2:
		rect.setFillColor(sf::Color::Red);
		return;
	default:
		rect.setFillColor(sf::Color::White);
		return;
	}
}

void Edge::setWeight(float x)
{
	this->weight = x;
}

Node* Edge::getNode1()
{
	return this->node1;
}

Node* Edge::getNode2()
{
	return this->node2;
}
