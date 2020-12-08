#pragma once
#include "../helper/Window.h"
#include "../helper/WindowManager.h"
#include "../helper/Button.h"
#include "../Menu.h"
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
    RS
};

class SortingWindow :public Window
{
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
    std::vector<int> beams;
    void quickSortHelper(int lb, int ub);
    void shellSortHelper(int n);
    void radixSortHelper(int n);
    void countsort(int n, int div);

public:
    SortingWindow(WindowManager& windowManager, sf::RenderWindow& window, Sort sortOpt);
    ~SortingWindow();
    void processEvents();
    void update(const sf::Time& dt);
    void draw();
    void sort();
    void reset();
    bool isSorted();
    void sleep(int delay);
    void selectionSort();
    void insertionSort();
    void MergeSort();
    void ShellSort();
    void radixSort();
    void quickSort();
    void setNodes(int i, int j); 
    void mergeSortHelper(int low, int high);
    void merge(int left, int middle, int right);
    int  getmax(int n);
};

