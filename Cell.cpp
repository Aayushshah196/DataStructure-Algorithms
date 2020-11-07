#include "Cell.h"

Cell::Cell() {
	size.x = 50;
	size.y = 50;
	selected = '0';
	path = '0';
	rect.setSize(size);
	rect.setFillColor(sf::Color::Yellow);
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	parent = NULL;
	block = false;
}

char Cell::isSelected() {
	return selected;
}

char Cell::isPath() {
	return path;
}

void Cell::setColor() {
	if(selected == '1')
		rect.setFillColor(sf::Color::Red);
	if(path == '1')
		rect.setFillColor(sf::Color::Green);

	rect.setOutlineColor(sf::Color::White);
}

void Cell::setPosition(float x, float y) {
	rect.setPosition(sf::Vector2f(x, y));
}

void Cell::setSelected() {
	 selected = '1';
}

void Cell::setPath() {
	path = '1';
}

void Cell::onClick() {
	rect.setFillColor(sf::Color::Cyan);
}