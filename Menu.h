#pragma once
#include "Window.h"
#include "WindowManager.h"
#include "Button.h"
#include <vector>
#include <memory>

enum class MenuScreen
{
    Main,
    Sort,
    Graph
};

class Menu :public Window
{
public:
    Menu(WindowManager& windowManager, sf::RenderWindow& window,MenuScreen currentScreen = MenuScreen::Main);
    ~Menu();
    void processEvents();
    void update(const sf::Time& dt);
    void draw();
private:
    sf::Font font;
    std::vector<Button::buttonPtr> buttons;
    MenuScreen currentScreen;
    bool isSelected[15];
    bool isClicked;
    int mouseX, mouseY;
    bool startSort, startGraph;
    sf::Text titleText;
};

