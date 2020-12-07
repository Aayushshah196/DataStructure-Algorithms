#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "SearchWindow.h"
#include "Window.h"
#include "Button.h"
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <stack>

SearchWindow::SearchWindow(WindowManager& windowManager, sf::RenderWindow& window, Search searchOpt)
	: Window(windowManager, window), startSort(false), mouseX(0), mouseY(0), isClicked(false), mButtons()
{
	this->searchOpt = searchOpt;
	srand(time(0));
	window.setMouseCursorVisible(true);
	float screenwidth = window.getSize().x;
	float screenHeight = window.getSize().y;

	sf::Vector2i pos(screenwidth / 2, screenHeight / 2);
	sf::Vector2i size(screenwidth, screenHeight);
	sf::Font& mFont = windowManager.getFont();

	auto resetBtn = std::make_shared<Button>();
	resetBtn->setAttributes("Reset", 40, mFont);
	resetBtn->setPos({ 90, 900 });
	resetBtn->setColor(sf::Color::White);

	auto searchBtn = std::make_shared<Button>();
	searchBtn->setAttributes("Search", 40, mFont);
	searchBtn->setPos({ 520, 900 });
	searchBtn->setColor(sf::Color::White);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 40, mFont);
	exitBtn->setPos({ 920, 900 });
	exitBtn->setColor(sf::Color::White);

	auto backBtn = std::make_shared<Button>();
	backBtn->setAttributes("Back", 40, mFont);
	backBtn->setPos({ 1260, 900 });
	backBtn->setColor(sf::Color::White);

	mButtons.push_back(resetBtn);
	mButtons.push_back(searchBtn);
	mButtons.push_back(exitBtn);
	mButtons.push_back(backBtn);

	for (int i = 0; i < 4; i++)
	{
		isSelected[i] = false;
	}
	this->sizeX = 15;
	this->sizeY = 35;
	for (int i = 0; i < this->sizeX; i++) {
		for (int j = 0; j < this->sizeY; j++) {
			Cell cell;
			cell.setPosition(j * 51 + 10, i * 51 + 10);
			int randval = rand() % 500;
			if(randval > 50 && randval < 125)
				cell.setBlock();
			grid.push_back(cell);
		}
	}
}
SearchWindow::~SearchWindow()
{
}

void SearchWindow::processEvents() {
	sf::Event event;

	if (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			windowManager.quit();
			break;
		case sf::Event::MouseMoved:
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mouseX = event.mouseButton.x;
				mouseY = event.mouseButton.y;
				isClicked = true;
			}
			break;
		}
	}
}

void SearchWindow::update(const sf::Time& dt)
{
	for (int i = 0; i < 4; i++)
	{
		if (mButtons.at(i)->getGlobalBounds().contains(mouseX, mouseY))
		{
			if (!isSelected[i])
			{
				isSelected[i] = true;
				mButtons.at(i)->setColor(sf::Color::Red);
			}
		}
		else
		{
			if (isSelected[i])
			{
				isSelected[i] = false;
				mButtons.at(i)->setColor(sf::Color::White);
			}
		}
	}
	if (items.size() < 2) {
		for (int i = 0; i < sizeX * sizeY; i++) {
			if (grid.at(i).hover(mouseX, mouseY)) {
				selected = i;
			}
		}
	}

	if (isClicked)
	{
		if (isSelected[0])
		{
			window.setMouseCursorVisible(true);
			//reset array
			this->reset();
		}
		//if search is clicked
		else if (isSelected[1])
		{
			this->search();
		}
		else if (isSelected[2])
		{
			windowManager.quit();
		}
		else if (isSelected[3])
		{
			std::unique_ptr<Window> menu(new Menu(windowManager, window, MenuScreen::Graph));
			windowManager.changeScene(std::move(menu));
		}
		if ((selected > 0) && (items.size() < 2)) {
			grid[selected].setFill(2);
			items.push_back(selected);
			selected = -1;
		}
		isClicked = false;
	}
}

void SearchWindow::draw() {
	window.clear(sf::Color::Black);
	for (Cell& cell : grid) {
		window.draw(cell);
	}
	for (int i = 0; i < 4; i++)
	{
		mButtons.at(i)->render(window);
	}
	window.display();
}

void SearchWindow::reset() {
	for (Cell& cell : grid) {
		cell.reset();
	}
	items.clear();
}

void SearchWindow::search() {
	switch(searchOpt)
	{
		case Search::BFS:
			SearchWindow::breadthFirstSearch();
			break;
		case Search::DFS:
			SearchWindow::depthFirstSearch();
			break;
	}
}

void SearchWindow::sleep(int delay) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void SearchWindow::breadthFirstSearch() {
  int delay = 100;
  std::queue<int> vertexQueue;
  vertexQueue.push(items[0]);
  grid[items[0]].setVisited();
  draw();
  sleep(delay);
  while (!vertexQueue.empty()) {
      int node = vertexQueue.front();
      vertexQueue.pop();
      for (int neighbour : getNeighbours(node)) {
          if (!grid[neighbour].isVisited()) {
              grid[neighbour].setVisited();
              grid[neighbour].setFill(4);
              vertexQueue.push(neighbour);
              grid[neighbour].setParent(&grid[node]);
              if (neighbour == items[1]) {
                  getPath();
                  return;
              }
          }
      }
      draw();
      sleep(delay);
  }
  getPath();
  return;
}

void SearchWindow::depthFirstSearch() {
  int delay = 50;
  std::stack<int> vertexStack;
  vertexStack.push(items[0]);
  grid[items[0]].setVisited();
  //draw();
  //sleep(delay);
  while (!vertexStack.empty()) {
      int node = vertexStack.top();
      vertexStack.pop();
      for (int neighbour : getNeighbours(node)) {
          if (!grid[neighbour].isVisited()) {
              grid[neighbour].setVisited();
              grid[neighbour].setFill(4);
              vertexStack.push(neighbour);
              grid[neighbour].setParent(&grid[node]);
              if (neighbour == items[1]) {
                  getPath();
                  return;
              }
			  draw();
          }
      }
      sleep(delay);
  }
  getPath();
  return;
}

// void SearchWindow::depthFirstSearch() {
//   int delay = 50;
//   std::stack<int> vertexStack;
//   vertexStack.push(items[0]);
//   grid[items[0]].setVisited();
//   draw();
//   sleep(delay);
//   int node = vertexStack.top();
//   dfsUtil(node, &vertexStack);
//   getPath();
//   return;
// }

// char SearchWindow::dfsUtil(int node, std::stack<int>* vertexStack)
// {
// 	vertexStack->pop();
// 	for (int neighbour : getNeighbours(node)) {
// 		if (!grid[neighbour].isVisited()) {
// 			grid[neighbour].setVisited();
// 			grid[neighbour].setFill(4);
// 			vertexStack->push(neighbour);
// 			grid[neighbour].setParent(&grid[node]);
// 			if (neighbour == items[1]) {
// 				return '1';
// 			}
// 			draw();
// 			sleep(100);
// 			if (dfsUtil(neighbour, vertexStack) == '1')
// 				return '1';
// 		}
// 	}
// }