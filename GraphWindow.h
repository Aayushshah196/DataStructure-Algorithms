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
#include "Node.h"
#include "Edge.h"

enum class Graph
{
    PR, KR
};

class GraphWindow :public Window
{
public:
    GraphWindow(WindowManager& windowManager, sf::RenderWindow& window, Graph mst_algo);
    ~GraphWindow();
    void processEvents();
    void update(const sf::Time& dt);
    void draw();
    void reset();
    void sleep(int delay);
    Node* find(Node* val);
    void union_set(Node* node1, Node* node2);
    void kruskals();
    void prims();

private:
    std::vector<Node*> visited;
    std::vector<Edge*> edgeset;
    Graph mst_algo;

    //Add new node to the vector visited
    void addNode(Node* node1)
    {
        for (Node* node2 : visited)
        {
            if (node2 == node1)
                return;
        }
        visited.push_back(node1);
    }
    //Checks if both nodes of edge has been visited or not
    bool checkVisit(Edge* edge1)
    {
        bool checkNode1 = std::find(visited.begin(), visited.end(), edge1->getNode1()) != visited.end();
        bool checkNode2 = std::find(visited.begin(), visited.end(), edge1->getNode2()) != visited.end();
        if(checkNode1 && checkNode2)
        {
            edgeset.pop_back();
            return true;
        }
        return false;
    }
    //Adds new edge to the minimum spanning tree vector
    void addMst(Edge* tmpedge)
    {
        bool first = std::find(visited.begin(), visited.end(), tmpedge->getNode1()) != visited.end();
        bool sec = std::find(visited.begin(), visited.end(), tmpedge->getNode2()) != visited.end();
        if ((!first && sec) || (first && !sec))
        {
            mst.push_back(tmpedge);
        }
        edgeset.pop_back();
    }
    //adds edge to the edgeset vector
    void addEdge(Node* node1)
    {
        for(Edge* edge1 : edges)
        {
            if((edge1->getNode1()==node1) || (edge1->getNode2()==node1))
            {
                bool edge_in_edgeset = std::find(edgeset.begin(), edgeset.end(), edge1) != edgeset.end();
                bool edge_in_mst = std::find(mst.begin(), mst.end(), edge1) != mst.end();
                if(!edge_in_edgeset && !edge_in_mst)
                {
                    edgeset.push_back(edge1);
                }
            }
        }
        std::sort(edgeset.begin(), edgeset.end(), [](Edge* edge1, Edge* edge2) { return edge1->getWeight() > edge2->getWeight(); });
    }
    sf::Font& mFont;
    std::vector<Button::buttonPtr> mButtons;
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;
    std::vector<Edge*> mst;
    bool isSelected[6];
    bool isClicked, canInsert, drawLine, isMst;
    int prevX, prevY;
    int mouseX, mouseY;
    int selected;
    void createGraph();
    void createEdge(int& a, int& b, int& c, int& d);
    void createNode(int& x, int& y);
};



