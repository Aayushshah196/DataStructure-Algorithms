#include <iostream>
#include "GraphWindow.h"
#include "Window.h"
#include "Button.h"
#include <time.h>
#include <stdlib.h>
#include "Node.h"

GraphWindow::GraphWindow(WindowManager& windowManager, sf::RenderWindow& window, Graph mst_algo) 
	: Window(windowManager, window), mouseX(0), mouseY(0), isClicked(false), mButtons(), mFont(windowManager.getFont())
{
	srand(time(0));
	window.setMouseCursorVisible(true);
	float screenwidth = window.getSize().x;
	float screenHeight = window.getSize().y;

	sf::Vector2i pos(screenwidth / 2, screenHeight / 2);
	sf::Vector2i size(screenwidth, screenHeight);

	auto resetBtn = std::make_shared<Button>();
	resetBtn->setAttributes("Reset", 40, mFont);
	resetBtn->setPos({ 70, 900 });
	resetBtn->setColor(sf::Color::White);

	auto searchBtn = std::make_shared<Button>();
	searchBtn->setAttributes("Search", 40, mFont);
	searchBtn->setPos({ 500, 900 });
	searchBtn->setColor(sf::Color::White);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 40, mFont);
	exitBtn->setPos({ 900, 900 });
	exitBtn->setColor(sf::Color::White);

	auto backBtn = std::make_shared<Button>();
	backBtn->setAttributes("Back", 40, mFont);
	backBtn->setPos({ 1250, 900 });
	backBtn->setColor(sf::Color::White);

	auto insertBtn = std::make_shared<Button>();
	insertBtn->setAttributes("Insert Node", 40, mFont);
	insertBtn->setPos({ 1500, 50 });
	insertBtn->setColor(sf::Color::White);

	auto lineBtn = std::make_shared<Button>();
	lineBtn->setAttributes("Draw Line", 40, mFont);
	lineBtn->setPos({ 1500, 150 });
	lineBtn->setColor(sf::Color::White);

	mButtons.push_back(resetBtn);
	mButtons.push_back(searchBtn);
	mButtons.push_back(exitBtn);
	mButtons.push_back(backBtn);
	mButtons.push_back(insertBtn);
	mButtons.push_back(lineBtn);

	for (int i = 0; i < 6; i++)
	{
		isSelected[i] = false;
	}
	canInsert = false;
	drawLine = false;
	isMst = false;
	this->mst_algo = mst_algo;
	this->createGraph();
}

GraphWindow::~GraphWindow()
{
	reset();
	for(Node* nodeptr : nodes)
	{
		delete nodeptr;
	}
	for (Edge* edgeptr : edges)
	{
		delete edgeptr;
	}
	nodes.clear();
	edges.clear();
}

void GraphWindow::processEvents() {
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
				if (drawLine)
				{
					prevX = mouseX;
					prevY = mouseY;
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mouseX = event.mouseButton.x;
				mouseY = event.mouseButton.y;
				if(drawLine)
				{
					createEdge(prevX, prevY, mouseX, mouseY);
				}
				if (canInsert)
				{
					createNode(mouseX, mouseY);
				}
				if (mButtons.at(4)->getGlobalBounds().contains(mouseX, mouseY))
				{
					drawLine = false;
					canInsert = !canInsert;
					if (canInsert)
					{
						mButtons.at(4)->setColor(sf::Color::Green);
					}
					else
					{
						mButtons.at(4)->setColor(sf::Color::White);
					}
				}
				if (mButtons.at(5)->getGlobalBounds().contains(mouseX, mouseY))
				{
					drawLine = !drawLine;
					canInsert = false;
					if (drawLine)
					{
						mButtons.at(5)->setColor(sf::Color::Green);
					}
					else
					{
						mButtons.at(5)->setColor(sf::Color::White);
					}
				}		
				isClicked = false;
			}
		}
	}
}

void GraphWindow::update(const sf::Time& dt)
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
	if (mButtons.at(4)->getGlobalBounds().contains(mouseX, mouseY))
	{
		if (!isSelected[4])
		{
			isSelected[4] = true;
			if (!canInsert)
				mButtons.at(4)->setColor(sf::Color::Red);
		}
	}
	else
	{
		if (isSelected[4])
		{
			isSelected[4] = false;
			if (!canInsert)
				mButtons.at(4)->setColor(sf::Color::White);
		}
	}
	if (mButtons.at(5)->getGlobalBounds().contains(mouseX, mouseY))
	{
		if (!isSelected[5])
		{
			isSelected[5] = true;
			if(!drawLine)
				mButtons.at(5)->setColor(sf::Color::Red);
		}
	}
	else
	{
		if (isSelected[5])
		{
			isSelected[5] = false;
			if(!drawLine)
				mButtons.at(5)->setColor(sf::Color::White);
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
			//search
			if(mst_algo == Graph::KR)
				this->kruskals();
			else if (mst_algo == Graph::PR)
				this->prims();
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
		else if (isSelected[4])
		{
			//if (canInsert)
			//{
				//canInsert = false;
				//mButtons.at(4)->setColor(sf::Color::White);
			//}
			//else
			//{
				//canInsert = true;
				//mButtons.at(4)->setColor(sf::Color::Green);
			//}
			//drawLine = false;
		}
		else if (isSelected[5])
		{
			//if (drawLine)
			//{
				//mButtons.at(5)->setColor(sf::Color::White);
			//}
			//else
			//{
				//mButtons.at(5)->setColor(sf::Color::Green);
			//}

			//drawLine = !drawLine;
			//canInsert = false;
		}
		isClicked = false;
	}
}

void GraphWindow::draw() {
	window.clear(sf::Color::Black);
	if (!isMst)
	{
		for (Edge* edgeptr : edges)
		{
			edgeptr->draw(window);
		}
	}	
	for (Edge* edgeptr : mst)
	{
		edgeptr->setColor(1);
		edgeptr->draw(window);
	}
	for (Node* nodeptr : nodes)
	{
		nodeptr->draw(window);
	}
	for (int i = 0; i < 6; i++)
	{
		mButtons.at(i)->render(window);
	}
	window.display();
}

void GraphWindow::reset() {
	isMst = false;
	mst.clear();
	for (Node* nodeptr : nodes)
	{
		nodeptr->setParent(NULL);
		nodeptr->rank = 0;
	}
	for (Edge* edgeptr : edges)
	{
		edgeptr->setColor();
	}
	edgeset.clear();
	visited.clear();
}

void GraphWindow::sleep(int delay) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

Node* GraphWindow::find(Node* val)
{
	if (val->getParent() == NULL)
	{
		return val;
	}
	return find(val->getParent());
}

void GraphWindow::union_set(Node* node1, Node* node2)
{
	//if (node1 != find(node1))
		//node2->setParent(find(node1));
	//else
		//node1->setParent(find(node2));
	node1 = find(node1);
	node2 = find(node2);
	if (node1->rank < node2->rank)
		node1->setParent(node2);
	else if (node1->rank > node2->rank)
		node2->setParent(node1);
	else {
		node1->setParent(node2);
		node1->rank++;
	}
}

void GraphWindow::kruskals()
{
	std::sort(edges.begin(), edges.end(), [](Edge* edge1, Edge* edge2) { return edge1->getWeight() < edge2->getWeight(); });
	for (int i = 0; i < edges.size(); i++)
	{
		edges[i]->setColor(2);
		draw();
		sleep(100);
		if (find(edges[i]->getNode1()) != find(edges[i]->getNode2()))
		{
			union_set(edges[i]->getNode1(), edges[i]->getNode2());
			mst.push_back(edges[i]);
		}
		edges[i]->setColor();
		draw();
		sleep(100);
		if (mst.size() == nodes.size() - 1)
			break;
	}
	isMst = true;
}

void GraphWindow::prims()
{
	int val = 3;
	addEdge(nodes[val]);
	visited.push_back(nodes[val]);
	while (mst.size() != (nodes.size() - 1))
	{
		//maintain priority in the edgeset for next edge
		//check if edge of any visited node is in the top edge of edgeset
		if (!checkVisit(edgeset.back()))
		{
			Edge* tmpedge = edgeset.back();
			for (Edge* edgeptr : edgeset)
			{
				edgeptr->setColor(2);
				draw();
				sleep(500);
				edgeptr->setColor();
				draw();
			}
			//addMst(tmpedge);
			sleep(500);
			mst.push_back(tmpedge);
			edgeset.pop_back();
			//union_set(tmpedge->getNode1(), tmpedge->getNode2());
			addNode(tmpedge->getNode1());
			addEdge(tmpedge->getNode1());
			addNode(tmpedge->getNode2());
			addEdge(tmpedge->getNode2());
		}
	}
	isMst = true;
}

void GraphWindow::createGraph()
{
	Node* node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(175, 75);
	nodes.push_back(node);

	node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(350, 450);
	nodes.push_back(node);

	node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(180, 650);
	nodes.push_back(node);

	node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(500, 180);
	nodes.push_back(node);

	node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(850, 650);
	nodes.push_back(node);

	node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(800, 95);
	nodes.push_back(node);

	node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(150, 380);
	nodes.push_back(node);

	node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(720, 420);
	nodes.push_back(node);

	Edge* edge = new Edge(nodes[0], nodes[1]);
	edges.push_back(edge);

	edge = new Edge(nodes[0], nodes[4]);
	edges.push_back(edge);

	edge = new Edge(nodes[0], nodes[5]);
	edges.push_back(edge);

	edge = new Edge(nodes[0], nodes[6]);
	edges.push_back(edge);

	edge = new Edge(nodes[1], nodes[2]);
	edges.push_back(edge);

	edge = new Edge(nodes[1], nodes[6]);
	edges.push_back(edge);

	edge = new Edge(nodes[2], nodes[4]);
	edges.push_back(edge);

	edge = new Edge(nodes[2], nodes[6]);
	edges.push_back(edge);

	edge = new Edge(nodes[3], nodes[4]);
	edges.push_back(edge);

	edge = new Edge(nodes[3], nodes[6]);
	edges.push_back(edge);

	edge = new Edge(nodes[3], nodes[7]);
	edges.push_back(edge);

	edge = new Edge(nodes[4], nodes[7]);
	edges.push_back(edge);

	edge = new Edge(nodes[5], nodes[7]);
	edges.push_back(edge);

	edge = new Edge(nodes[6], nodes[7]);
	edges.push_back(edge);
}

void GraphWindow::createEdge(int& a, int& b, int& c, int& d)
{
	Node* node1 = NULL;
	Node* node2 = NULL;
	for (Node* node : nodes)
	{
		if (node->contains(a, b))
			node1 = node;
		else if (node->contains(c, d))
			node2 = node;
	}
	if (node1 != NULL && node2 != NULL)
	{
		Edge* edge = new Edge(node1, node2);
		edges.push_back(edge);
	}
}

void GraphWindow::createNode(int& x, int& y)
{
	for (Button::buttonPtr button : mButtons)
	{
		if (button->getGlobalBounds().contains(x, y))
			return;
	}
	Node* node = new Node(this->mFont);
	node->setValue(nodes.size());
	node->setPosition(x, y);
	nodes.push_back(node);
}
