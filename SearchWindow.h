#pragma once
#include "Window.h"
#include "WindowManager.h"
#include "Button.h"
#include "Menu.h"
#include <thread>
#include <chrono>
#include "Cell.h"
#include <vector>
#include <memory>

enum class Search
{
    PR,
    KR,
    DIJ,
    FW,
    BFS,
    DFS
};

class SearchWindow :public Window
{
public:
    SearchWindow(WindowManager& windowManager, sf::RenderWindow& window, Search searchOpt);
    ~SearchWindow();
    void processEvents();
    void update(const sf::Time& dt);
    void draw();
    void reset();
    void sleep(int delay);
    void search();
    void breadthFirstSearch();
    void depthFirstSearch();
private:
    int sizeX, sizeY;
    sf::Font mFont;
    std::vector<Button::buttonPtr>mButtons;
    Search searchOpt;
    bool isSelected[4];
    bool isClicked;
    int mouseX, mouseY;
    bool startSort;
    std::vector<Cell> grid;
    std::vector<int> items;
    int selected;
    std::vector<int> getNeighbours(int node) {
        std::vector<int> neighbour;
        int dx[4] = { 0, 1, 0, -1 };
        int dy[4] = { 1, 0, -1, 0 };
        for (int i = 0; i < 4; i++) {
            int x = node / this->sizeY;
            int y = node % this->sizeY;
            x += dx[i];
            y += dy[i];
            if ((x>=0 && y>=0) && (x<this->sizeX && y<this->sizeY)) {
                if(!grid[x * this->sizeY + y].isBlock())
                    neighbour.push_back(x * this->sizeY + y);
            }
        }
        return neighbour;
    }
    void getPath() {
        Cell* node = &grid[items[1]];
        std::vector<Cell*> path;
        while (node != &grid[items[0]]) {
            path.push_back(node);
            if (node->getParent() == NULL) {
                noPath();
                return;
            }
            node = node->getParent();
            
        }
        path.push_back(&grid[items[0]]);
        setPath(path);
        return;
    }
    void noPath() {
        int delay = 100;
        for (Cell& cell : grid) {
            if (!cell.isBlock())
                cell.setFill(1);
        }
        grid[items[0]].setFill(3);
        grid[items[1]].setFill(3);
        draw();
    }
    void setPath(std::vector<Cell*>& path) {
        int delay = 100;
        for (Cell& cell : grid) {
            if(!cell.isBlock())
                cell.setFill(1);
        }
        draw();
        sleep(delay);
        for (Cell* cell : path) {
            cell->setFill(2);
        }
        draw();
    }
};



