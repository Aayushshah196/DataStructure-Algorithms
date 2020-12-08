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
	resetBtn->setPos({ 80, 900 });
	resetBtn->setColor(sf::Color::White);

	auto sortBtn = std::make_shared<Button>();
	sortBtn->setAttributes("Sort", 40, font);
	sortBtn->setPos({ 505, 900 });
	sortBtn->setColor(sf::Color::White);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 40, font);
	exitBtn->setPos({ 900, 900 });
	exitBtn->setColor(sf::Color::White);

	auto backBtn = std::make_shared<Button>();
	backBtn->setAttributes("Back", 40, font);
	backBtn->setPos({ 1230, 900 });
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
		beams.push_back(height);
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
	   currentRect.setSize(sf::Vector2f(30, (-1)*beams[i]));
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
		switch (sortOpt) {
		case Sort::IS:
			SortingWindow::insertionSort();
			break;
		case Sort::SLS:
			SortingWindow::selectionSort();
			break;
		case Sort::QS:
			SortingWindow::quickSort();
			break;
		case Sort::MS:
			SortingWindow::MergeSort();
			break;
		case Sort::SS:
			SortingWindow::ShellSort();
			break;
		case Sort::RS:
			SortingWindow::radixSort();
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
		beams.push_back(height);
	}
	this->sorted = false;
}

void SortingWindow::sleep(int delay) {
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
			if (beams[min_index] > beams[j]) {
				min_index = j;
			}
			setNodes(i, j);
			draw();
			setNodes(-1, -1);
			sleep(delay);
		}
		std::swap(beams[i], beams[min_index]);
	}
}
void SortingWindow::insertionSort() {

		for (int i = 0; i < this->size; i++) {
			int temp = beams[i];
			int j = i - 1;
			while (j >= 0 && beams[j] > temp) {
				{
					beams[j + 1] = beams[j];
					j--;
				}
				setNodes(i, j);
				draw();
				setNodes(-1, -1);
				sleep(30);
			}
			beams[j + 1] = temp;
		}
	}

void SortingWindow::MergeSort() {
	mergeSortHelper(0, this->size - 1);
}
void SortingWindow::ShellSort() {
	shellSortHelper(this->size);
}
void SortingWindow::radixSort() {
	radixSortHelper(this->size);
}
void SortingWindow::quickSort() {
	quickSortHelper(0, this->size - 1);
}

//Merge Sort Helper template
void SortingWindow::mergeSortHelper(int low, int high) {
	if (low < high) {
		int middle = (low + high) / 2;

		mergeSortHelper(low, middle);
		mergeSortHelper(middle + 1, high);
		merge(low, middle, high);
	}
}

//Merge Template
void SortingWindow::merge(int left, int middle, int right) {
	//Decleration of Iterator variables and temp array
	int i = left;
	int j = middle + 1;
	int k = left;
	std::vector<int> temp = beams;

	//Loop to move to combine the two seperate arrays until one is empty
	while (i <= middle && j <= right) {
		if (beams[i] >= beams[j]) {
			temp[k] = beams[i];
			i++;
		}
		else {
			temp[k] = beams[j];
			j++;
		}
		k++;
		setNodes(i, j);
		draw();
		setNodes(-1, -1);
		sleep(30);

	}

	//Move the leftover elements of whichever array still has them
	while (i <= middle) {
		temp[k] = beams[i];
		i++;
		k++;
	}

	while (j <= right) {
		temp[k] = beams[j];
		j++;
		k++;
	}

	//Move all of the elements in the Temp array to the Normal array
	for (k = left; k <= right; k++) {
		beams[k] = temp[k];
		setNodes(k, -1);
		draw();
		setNodes(-1, -1);
		sleep(30);
	}
}

void SortingWindow::quickSortHelper(int low, int high) {
		int i = low;
		int j = high;
		int pivot = beams[(i + j) / 2];

		while (i <= j)// partition quick sort 
		{
			while (beams[i] < pivot)
				i++;
			while (beams[j] > pivot)
				j--;
			if (i <= j)
			{
				std::swap(beams[i], beams[j]);
				setNodes(i, j);
				draw();
				setNodes(-1, -1);
				sleep(50);
				i++;
				j--;
				setNodes(i, j);
				draw();
				setNodes(-1, -1);
				sleep(50);
			}
		}
		if (j > low)
			quickSortHelper(low, j);
		if (i < high)
			quickSortHelper(i, high);
	}

//shellsort helper
void SortingWindow::shellSortHelper(int n) {
	for (int gap = n / 2; gap > 0; gap = gap / 2)
	{
		for (int j = gap; j < n; j++)
		{
			int temp = beams[j];
			int i = 0;
			for (i = j; i >= gap && beams[i - gap] > temp; i = i - gap)
			{
				beams[i] = beams[i - gap];
				setNodes(i, i-gap);
				draw();
				setNodes(-1, -1);
				sleep(30);
			}

			beams[i] = temp;
			setNodes(i, temp);
			draw();
			setNodes(-1, -1);
			sleep(30);

		}

	}
}
int SortingWindow::getmax(int n) {
	int max = beams[0];
	for (int i = 1; i < n; i++)
	{
		if (beams[i] > max)
		{
			max = beams[i];
		}
	}
	return max;
}

void SortingWindow::radixSortHelper(int n) {
	int m = getmax(n);
	for (int div = 1; m / div > 0; div = div * 10)
	{
		countsort(n, div);
	}
}

void SortingWindow::countsort(int n, int div) {
	int output[100];
	int count[10] = { 0 };
	for (int i = 0; i < n; i++) {
		int x =(beams[i] / div) % 10;
		count[x]++;

	}

	for (int i = 1; i < 10; i++)
		count[i] = count[i] + count[i - 1];

	for (int i = n - 1; i >= 0; i--)
	{

		output[count[(beams[i] / div) % 10] - 1] = beams[i];
		count[(beams[i] / div) % 10]--;
		setNodes(i, output[count[(beams[i] / div) % 10] - 1]);
		draw();
		setNodes(-1, -1);
		sleep(50);

	}
	for (int i = 0; i < n; i++)
	{

		beams[i] = output[i];
		setNodes(i, output[i]);
		draw();
		setNodes(-1, -1);
		sleep(50);
	}
}