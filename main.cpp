#include"Game.h"
#include"Menu.h"
int main()
{
    sf::RenderWindow win;
    win.create({900, 600}, "Typing test");
    Menu menu(&win);
    menu.menuLoop();
    GameEngine GE(&win, menu.getTime());
    GE.gameLoop();
    return 0;
}


