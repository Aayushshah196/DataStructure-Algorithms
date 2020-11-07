#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
class Cell : public sf::Drawable
{
private:
	sf::Vector2f size;
	sf::RectangleShape rect;
	char selected, path, color;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(rect, states);
	}
	bool visited, block;
	Cell* parent;
public:
	Cell();
	char isSelected();
	char isPath();
	void setColor();
	void setPosition(float x, float y);
	void setSelected();
	bool hover(int& mouseX, int& mouseY) {
		return rect.getGlobalBounds().contains(mouseX, mouseY);
	}
	void setEnd() {
		rect.setFillColor(sf::Color::Green);
	}
	void setFill(int x = -1) {
		switch (x) {
		case 1:
			rect.setFillColor(sf::Color::Yellow);
			return;
		case 2:
			rect.setFillColor(sf::Color::Green);
			return;
		case 3:
			rect.setFillColor(sf::Color::Red);
			return;
		case 4:
			rect.setFillColor(sf::Color::Blue);
			return;
		default:
			rect.setFillColor(sf::Color::Black);
			return;
		}
	} 
	void setBlock() {
		this->block = true;
		setFill();
	}
	bool isBlock() {
		return this->block;
	}
	void reset() {
		selected = '0';
		path = '0';
		srand(time(0));
		int x = rand()%550;
		if (x > 50 && x < 125)
			this->block = true;
		this->block ? setFill() : setFill(1);
		this->parent = NULL;
		visited = false;
	}
	void setVisited() {
		visited = true;
	}
	bool isVisited() {
		return visited;
	}
	void setPath();
	void onClick();
	void previous(Cell* parent) {
		this->parent = parent;
	}
	Cell* getParent() {
		return this->parent;
	}
};

