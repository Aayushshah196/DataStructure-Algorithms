#pragma once
#include <stack>
#include "Window.h"
#include <memory>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    void pushScene(std::unique_ptr<Window> scene);
    void popScene();
    void changeScene(std::unique_ptr<Window> scene);
    sf::Font& getFont();
    void processEvents();
    void update(sf::Time dt);
    void draw();

    std::unique_ptr<Window> getCurrentState();

    bool isRunning();
    void quit();
private:
    std::stack<std::unique_ptr<Window>> scenes;
    bool running;
    sf::Font font;
};