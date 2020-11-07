#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SortWindow.h"

SortingWindow::SortingWindow(WindowManager& windowManager, sf::RenderWindow& window, Sort sortOpt)
	: Window(windowManager, window), sorted(false), mouseX(0), mouseY(0), isClicked(false), buttons()
{
	this->sortOpt = sortOpt;
	this->prev = -1;
	this->next = -1;
	window.setMouseCursorVisible(true);
	float screenwidth = window.getSize().x;
	float screenHeight = window.getSize().y;

	sf::Vector2i pos(screenwidth / 2, screenHeight / 2);
	sf::Vector2i size(screenwidth, screenHeight);
	sf::Font& font = windowManager.getFont();

	auto resetBtn = std::make_shared<Button>();
	resetBtn->setAttributes("Reset", 40, font);
	resetBtn->setPos({ 20, 900 });
	resetBtn->setColor(sf::Color::White);

	auto sortBtn = std::make_shared<Button>();
	sortBtn->setAttributes("Sort", 40, font);
	sortBtn->setPos({ 450, 900 });
	sortBtn->setColor(sf::Color::White);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 40, font);
	exitBtn->setPos({ 850, 900 });
	exitBtn->setColor(sf::Color::White);

	auto backBtn = std::make_shared<Button>();
	backBtn->setAttributes("Back", 40, font);
	backBtn->setPos({ 1150, 900 });
	backBtn->setColor(sf::Color::White);

	buttons.push_back(resetBtn);
	buttons.push_back(sortBtn);
	buttons.push_back(exitBtn);
	buttons.push_back(backBtn);

	for (int i = 0; i < 4; i++)
	{
		isSelected[i] = false;
	}

	this->size = 55;
	srand(time(0));
	for (int i = 0; i < this->size; i++) {
		float height = rand() % 800;
		beams.push_back(-1*height);
	}
}
SortingWindow::~SortingWindow()
{
}

void SortingWindow::processEvents() {
	sf::Event event;

	if (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			//window.close();
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

void SortingWindow::update(const sf::Time& dt)
{
		for (int i = 0; i < 4; i++)
		{
			if (buttons.at(i)->getGlobalBounds().contains(mouseX, mouseY))
			{
				if (!isSelected[i])
				{
					isSelected[i] = true;
					buttons.at(i)->setColor(sf::Color::Red);
				}
			}
			else
			{
				if (isSelected[i])
				{
					isSelected[i] = false;
					buttons.at(i)->setColor(sf::Color::White);
				}
			}
		}

		if (isClicked)
		{
			if (isSelected[0])
			{
				window.setMouseCursorVisible(true);
				this->reset();
			}
			else if (isSelected[1])
			{
				//sort
				this->sort();
			}
			else if (isSelected[2])
			{
				windowManager.quit();
			}
			else if (isSelected[3])
			{
				std::unique_ptr<Window> menu(new Menu(windowManager, window, MenuScreen::Sort));
				windowManager.changeScene(std::move(menu));
			}
			isClicked = false;
		}
}

void SortingWindow::draw() {
	window.clear(sf::Color::Black);
	sf::RectangleShape currentRect;
	for (int i = 0; i < this->size; i++) {
	   currentRect.setSize(sf::Vector2f(30, beams[i]));
	   currentRect.setPosition(sf::Vector2f(i * 32+65, 850));
	   currentRect.setFillColor(sf::Color::White);
	   currentRect.setOutlineColor(sf::Color::Black);
	   currentRect.setOutlineThickness(2);
	   if (i == prev) currentRect.setFillColor(sf::Color(67, 130, 232, 255));
	   if (i == next) currentRect.setFillColor(sf::Color::Red);
	   window.draw(currentRect);
	}
	for (int i = 0; i < 4; i++)
	{
		buttons.at(i)->render(window);
	}
	window.display();
}

void SortingWindow::sort() {
	if(!this->sorted)
	{
		switch(sortOpt) {
			case Sort::IS:
				break;
			case Sort::SLS:
				SortingWindow::selectionSort();
				break;
			case Sort::QS:
				break;
			case Sort::MS:
				break;
			case Sort::SS:
				break;
			case Sort::RS:
				break;
			case Sort::HS:
				break;
		}
		this->sorted = true;
	}
	
}


void SortingWindow::reset() {
	this->beams.clear();
	srand(time(0));
	for (int i = 0; i < this->size; i++) {
		float height = rand() % 800;
		beams.push_back(-1*height);
	}
	this->sorted = false;
}

void SortingWindow::sleep(int& delay) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

bool SortingWindow::isSorted() {
	return this->sorted;
}

void SortingWindow::setNodes(int i, int j) {
	this->prev = i;
	this->next = j;
}

void SortingWindow::selectionSort() {
	int delay = 10;
	for (int i = 0; i < size; i++) {
		int min_index = i;
		sleep(delay);
		for (int j = i + 1; j < size; j++) {
			if (beams[min_index] < beams[j]) {
				min_index = j;
			}
			setNodes(i, j);
			draw();
			setNodes(-1, -1);
			sleep(delay);
		}
		std::swap(beams[i], beams[min_index]);
		setNodes(i, min_index);
		draw();
		setNodes(-1, -1);
	}
}
void SortingWindow::heapSort() {
	
}
void SortingWindow::insertionSort() {
	
}
void SortingWindow::MergeSort() {
	
}
void SortingWindow::ShellSort() {
	
}
void SortingWindow::radixSort() {
	
}
void SortingWindow::quickSort() {
	
}