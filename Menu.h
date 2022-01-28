#include <SFML/Graphics.hpp>
#include <iostream>
#include<vector>
#include<sstream>
//#include"textbox2.h"

class Menu
{
private:
    sf::RenderWindow *window;
    Textbox nameBox;
    Textbox timeBoxOut;
    Textbox timeBoxIn;
    int gameTime;
public:
    Menu(sf::RenderWindow *orgWindow);
    void menuLoop();
    int getTime();
    void countDown();
};

Menu::Menu(sf::RenderWindow *orgWindow) : timeBoxOut(orgWindow, sf::Color::White), timeBoxIn(orgWindow, sf::Color::Green), nameBox(orgWindow, sf::Color::White)
{
    gameTime = 0;
    window = orgWindow;
    sf::Font font;
    font.loadFromFile("font.ttf");

    nameBox.setFont(font);
    nameBox.setPosition({100,100});
    nameBox.updateString("Typing test");

    timeBoxOut.setFont(font);
    timeBoxOut.setPosition({100,200});
    timeBoxOut.updateString("Time of test (sec.): ");

    timeBoxIn.setFont(font);
    timeBoxIn.setPosition({100,300});
}

void Menu::menuLoop()
{

    sf::Event event;
    bool enterPressed = false;
    int maxdigits = 3;
    int digits = 0;
    while(window->isOpen() && !enterPressed)
    {
        while(window->pollEvent(event) && !enterPressed)
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
            else if(event.type == sf::Event::TextEntered)
            {
                if (std::isprint(event.text.unicode))
                {

                    char temp = event.text.unicode;
                    if(temp < 58 && temp > 47 && digits < maxdigits)
                    {
                        int tempNum = temp - '0';
                        std::string charTyped(1,temp);
                        timeBoxIn.updateString(charTyped);
                        gameTime = gameTime * 10 + tempNum;
                        digits++;
                    }
                }
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Return)
                {
                    enterPressed = true;
                    countDown();
                }
                else if(event.key.code == sf::Keyboard::BackSpace)
                {
                    digits--;
                    if(digits < 0)
                        digits = 0;
                    gameTime = gameTime / 10;
                    std::string strTemp = timeBoxIn.getText();
                    timeBoxIn.clearString();
                    if(!strTemp.empty())
                    {
                        strTemp.pop_back();
                    }
                    timeBoxIn.updateString(strTemp);
                }
            }

            window->clear();


            nameBox.printText();
            timeBoxOut.printText();
            timeBoxIn.printText();
            window->display();
        }

    }

}

int Menu::getTime()
{
    if (gameTime > 0)
        return gameTime;
    return 60;
}

void Menu::countDown()
{
    int n = 3;
    nameBox.clearString();
    nameBox.updateString("Countdown:");

    for (int i = n; i > 0 ; i --)
    {
        window->clear();
        timeBoxIn.clearString();
        std::string charCount(1,(char)(i + '0'));
        timeBoxIn.updateString(charCount);
        timeBoxIn.printText();
        nameBox.printText();
        window->display();
        sf::sleep(sf::seconds(1));
    }
}
