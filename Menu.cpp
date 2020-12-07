#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "SortWindow.h"
#include "SearchWindow.h"
#include "GraphWindow.h"

Menu::Menu(WindowManager& windowManager, sf::RenderWindow& window, MenuScreen currentScreen)
	: Window(windowManager, window), currentScreen(currentScreen), startSort(false), mouseX(0), mouseY(0), isClicked(false), buttons(), startGraph(false)
{
	window.setMouseCursorVisible(true);
	float screenWidth = window.getSize().x;
	float screenHeight = window.getSize().y;

	sf::Vector2i pos(screenWidth / 2, screenHeight / 2);
	sf::Vector2i size(screenWidth, screenHeight);
	sf::Font& font = windowManager.getFont();

	auto sortBtn = std::make_shared<Button>();
	sortBtn->setAttributes("Sorting", 40, font);
	sortBtn->setPos({ screenWidth / 2 - sortBtn->getSize() / 2, 600 });
	sortBtn->setColor(sf::Color::White);

	auto graphBtn = std::make_shared<Button>();
	graphBtn->setAttributes("Graph", 40, font);
	graphBtn->setPos({ screenWidth / 2 - graphBtn->getSize() / 2, 700 });
	graphBtn->setColor(sf::Color::White);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 40, font);
	exitBtn->setPos({ screenWidth / 2 - exitBtn->getSize() / 2, 800 });
	exitBtn->setColor(sf::Color::White);

	auto insertsortBtn = std::make_shared<Button>();
	insertsortBtn->setAttributes("Insertion Sort", 40, font);
	insertsortBtn->setPos({ screenWidth / 2 - insertsortBtn->getSize() / 2, 320 });
	insertsortBtn->setColor(sf::Color::White);

	auto selectionsortBtn = std::make_shared<Button>();
	selectionsortBtn->setAttributes("Selection Sort", 40, font);
	selectionsortBtn->setPos({ screenWidth / 2 - selectionsortBtn->getSize() / 2, 400 });
	selectionsortBtn->setColor(sf::Color::White);

	auto quicksortBtn = std::make_shared<Button>();
	quicksortBtn->setAttributes("Quick Sort", 40, font);
	quicksortBtn->setPos({ screenWidth / 2 - quicksortBtn->getSize() / 2, 480 });
	quicksortBtn->setColor(sf::Color::White);

	auto mergesortBtn = std::make_shared<Button>();
	mergesortBtn->setAttributes("Merge Sort", 40, font);
	mergesortBtn->setPos({ screenWidth / 2 - mergesortBtn->getSize() / 2, 560 });
	mergesortBtn->setColor(sf::Color::White);

	auto shellsortBtn = std::make_shared<Button>();
	shellsortBtn->setAttributes("Shell Sort", 40, font);
	shellsortBtn->setPos({ screenWidth / 2 - shellsortBtn->getSize() / 2, 640 });
	shellsortBtn->setColor(sf::Color::White);

	auto radixsortBtn = std::make_shared<Button>();
	radixsortBtn->setAttributes("Radix Sort", 40, font);
	radixsortBtn->setPos({ screenWidth / 2 - radixsortBtn->getSize() / 2, 720 });
	radixsortBtn->setColor(sf::Color::White);

	auto backBtn = std::make_shared<Button>();
	backBtn->setAttributes("Back", 40, font);
	backBtn->setPos({ screenWidth / 2 - backBtn->getSize() / 2, 800 });
	backBtn->setColor(sf::Color::White);

	auto primBtn = std::make_shared<Button>();
	primBtn->setAttributes("Prim's Algorithm", 40, font);
	primBtn->setPos({ screenWidth / 2 - primBtn->getSize() / 2, 480 });
	primBtn->setColor(sf::Color::White);

	auto krushkalBtn = std::make_shared<Button>();
	krushkalBtn->setAttributes("Krushkal's Algorithm", 40, font);
	krushkalBtn->setPos({ screenWidth / 2 - krushkalBtn->getSize() / 2, 560 });
	krushkalBtn->setColor(sf::Color::White);

	auto bfsBtn = std::make_shared<Button>();
	bfsBtn->setAttributes("Breadth First Search", 40, font);
	bfsBtn->setPos({ screenWidth / 2 - bfsBtn->getSize() / 2, 640 });
	bfsBtn->setColor(sf::Color::White);

	auto dfsBtn = std::make_shared<Button>();
	dfsBtn->setAttributes("Depth First Search", 40, font);
	dfsBtn->setPos({ screenWidth / 2 - dfsBtn->getSize() / 2, 720 });
	dfsBtn->setColor(sf::Color::White);

	buttons.push_back(sortBtn);
	buttons.push_back(graphBtn);
	buttons.push_back(exitBtn);
	buttons.push_back(insertsortBtn);
	buttons.push_back(selectionsortBtn);
	buttons.push_back(quicksortBtn);
	buttons.push_back(mergesortBtn);
	buttons.push_back(shellsortBtn);
	buttons.push_back(radixsortBtn);
	buttons.push_back(backBtn);
	buttons.push_back(primBtn);
	buttons.push_back(krushkalBtn);
	buttons.push_back(bfsBtn);
	buttons.push_back(dfsBtn);

	titleText.setFont(font);
	titleText.setString("Data Structure & Algorithm");
	titleText.setCharacterSize(80);
	titleText.setPosition(sf::Vector2f(screenWidth / 2 - titleText.getGlobalBounds().width / 2, 100 ));
	titleText.setFillColor(sf::Color::Red);

	for (int i = 0; i < 14; i++)
	{
		isSelected[i] = false;
	}
}

Menu::~Menu()
{
	buttons.clear();
}

void Menu::processEvents() {
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

void Menu::update(const sf::Time& dt)
{
	switch (currentScreen)
	{
	case MenuScreen::Main:
		for (int i = 0; i < 3; i++)
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
			window.setMouseCursorVisible(true);
			if (isSelected[0])
			{
				currentScreen = MenuScreen::Sort;
			}
			else if (isSelected[1])
			{
				currentScreen = MenuScreen::Graph;
			}
			else if (isSelected[2])
			{
				windowManager.quit();
			}
			isClicked = false;
		}
		break;

	case MenuScreen::Sort:
		for (int i = 3; i < 10; i++)
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
			window.setMouseCursorVisible(true);
			if (isSelected[3])
			{
				std::unique_ptr<Window> sortingwindow(new SortingWindow(windowManager, window, Sort::IS));
				windowManager.pushScene(std::move(sortingwindow));
			}
			else if (isSelected[4])
			{
				std::unique_ptr<Window> sortingwindow(new SortingWindow(windowManager, window, Sort::SLS));
				windowManager.pushScene(std::move(sortingwindow));
			}
			else if (isSelected[5])
			{
				std::unique_ptr<Window> sortingwindow(new SortingWindow(windowManager, window, Sort::QS));
				windowManager.pushScene(std::move(sortingwindow));
			}
			else if (isSelected[6])
			{
				std::unique_ptr<Window> sortingwindow(new SortingWindow(windowManager, window, Sort::MS));
				windowManager.pushScene(std::move(sortingwindow));
			}
			else if (isSelected[7])
			{
				std::unique_ptr<Window> sortingwindow(new SortingWindow(windowManager, window, Sort::SS));
				windowManager.pushScene(std::move(sortingwindow));
			}
			else if (isSelected[8])
			{
				std::unique_ptr<Window> sortingwindow(new SortingWindow(windowManager, window, Sort::RS));
				windowManager.pushScene(std::move(sortingwindow));
			}
			else if (isSelected[9])
			{
				currentScreen = MenuScreen::Main;
				buttons.at(9)->setColor(sf::Color::White);
			}
			isClicked = false;
		}
		break;

	case MenuScreen::Graph:
		for (int i = 10; i < 14; i++)
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
		if (buttons.at(9)->getGlobalBounds().contains(mouseX, mouseY))
			{
				if (!isSelected[9])
				{
					isSelected[9] = true;
					buttons.at(9)->setColor(sf::Color::Red);
				}
			}
			else
			{
				if (isSelected[9])
				{
					isSelected[9] = false;
					buttons.at(9)->setColor(sf::Color::White);
				}
			}

		if (isClicked)
		{
			window.setMouseCursorVisible(true);
			if (isSelected[10])
			{
				std::unique_ptr<Window> graphwindow(new GraphWindow(windowManager, window, Graph::PR));
				windowManager.pushScene(std::move(graphwindow));
			}
			else if (isSelected[11])
			{
				std::unique_ptr<Window> graphwindow(new GraphWindow(windowManager, window, Graph::KR));
				windowManager.pushScene(std::move(graphwindow));
			}
			else if (isSelected[12])
			{
				std::unique_ptr<Window> graphwindow(new SearchWindow(windowManager, window, Search::BFS));
				windowManager.pushScene(std::move(graphwindow));
			}
			else if (isSelected[13])
			{
				std::unique_ptr<Window> graphwindow(new SearchWindow(windowManager, window, Search::DFS));
				windowManager.pushScene(std::move(graphwindow));
			}
			else if (isSelected[9])
			{
				currentScreen = MenuScreen::Main;
				buttons.at(9)->setColor(sf::Color::White);
			}
			isClicked = false;
		}
		break;
	}
}

void Menu::draw() {
	window.clear(sf::Color::Black);

	window.draw(this->titleText);
	switch (currentScreen)
	{
	case MenuScreen::Main:
		for (int i = 0; i < 3; i++)
		{
			buttons.at(i)->render(window);
		}
		break;
	case MenuScreen::Sort:
		for (int j = 3; j < 10; j++)
		{
			buttons.at(j)->render(window);
		}
		break;
	case MenuScreen::Graph:
		for (int j = 10; j < 14; j++)
		{
			buttons.at(j)->render(window);
		}
		buttons.at(9)->render(window);
		break;
	}
	window.display();
}