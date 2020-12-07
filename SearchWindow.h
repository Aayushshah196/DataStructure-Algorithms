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
    //char dfsUtil(int node, std::stack<int>* vertexStack);
    
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
    // returns vector of neighbor node for given node
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
    //Checks if a path is possible for the given source and destination
    //if found sets Path condition
    //else sets no Path condition
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
    }

    //sets the nodes color if no path is found 
    void noPath() {
        for (Cell& cell : grid) {
            if (!cell.isBlock())
                cell.setFill(1);
        }
        grid[items[0]].setFill(3);
        grid[items[1]].setFill(3);
        draw();
    }

    //sets the path color if a path is found 
    void setPath(std::vector<Cell*>& path) {
        for (Cell& cell : grid) {
            if(!cell.isBlock())
              cell.setFill(1);
        }
        for (Cell* cell : path) {
            cell->setFill(2);
        }
        draw();
    }

};