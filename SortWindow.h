#pragma once
#include "Window.h"
#include "WindowManager.h"
#include "Button.h"
#include "Menu.h"
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum class Sort
{
    IS,
    SLS,
    QS,
    MS,
    SS,
    RS,
    HS
};

class SortingWindow :public Window
{
public:
    SortingWindow(WindowManager& windowManager, sf::RenderWindow& window, Sort sortOpt);
    ~SortingWindow();
    void processEvents();
    void update(const sf::Time& dt);
    void draw();
    void sort();
    void reset();
    bool isSorted();
    void sleep(int& delay);
    void selectionSort();
    void heapSort();
    void insertionSort();
    void MergeSort();
    void ShellSort();
    void radixSort();
    void quickSort();
    void setNodes(int i, int j);
private:
    Sort sortOpt;
    sf::Font font;
    std::vector<Button::buttonPtr> buttons;
    bool isSelected[4];
    bool isClicked;
    int mouseX, mouseY;
    bool sorted; 
    int size;
    int prev, next;
    std::vector<float> beams;
};

