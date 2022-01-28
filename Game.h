#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "textbox.h"

class GameEngine
{
private:

    sf::RenderWindow *window;
    std::vector<std::string> wordList;
    Textbox inputBox;
    Textbox wordBox;
    int wordIndex;
    int goodLetters;
    int badLetters;
    int timeLimit;
    int wordLimit;
public:
    GameEngine(sf::RenderWindow *orgWindow, int timeLim); //constructor
    ~GameEngine(); //destructor
    //Methods
    void gameLoop();
    void loadWords(std::string name);
    int loadN();
};



GameEngine::GameEngine(sf::RenderWindow *orgWindow, int timeLim ): inputBox(orgWindow, sf::Color::White), wordBox(orgWindow, sf::Color::Cyan)
{
    loadWords("test.txt");
    wordLimit = 5;
    window = orgWindow;
    sf::Font font;
    font.loadFromFile("font.ttf");
    goodLetters = 0;
    badLetters = 0;
    timeLimit = timeLim;

    wordBox.setFont(font);
    wordBox.setPosition({100,100});
    wordIndex = 0;

    inputBox.setFont(font);
    inputBox.setPosition({100,200});
}

GameEngine::~GameEngine() { }


void GameEngine::gameLoop()
{

    int writtenSize = 0, prevWord = wordIndex, wordSize = loadN();
    sf::Clock clock;
    sf::Time limit = sf::seconds(timeLimit), actTime = clock.getElapsedTime();
    sf::Event event;
    while(window->isOpen() )
    {

        while(window->isOpen() && actTime.asSeconds() < limit.asSeconds())
        {


            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    window->close();
                }
                else if(event.type == sf::Event::TextEntered)
                {
                    if (std::isprint(event.text.unicode) && event.text.unicode != ' ')
                    {

                        char temp = event.text.unicode;
                        std::string charTyped(1,temp);
                        inputBox.updateString(charTyped);
                        if(wordList[prevWord][writtenSize] == temp)
                            goodLetters++;
                        else
                            badLetters++;

                        writtenSize++;
                        if(writtenSize == wordSize)
                        {
                            prevWord = wordIndex;
                            wordSize = loadN();
                            writtenSize = 0;
                            inputBox.clearString();
                        }
                    }
                }
            }

            window->clear();
            inputBox.printText();
            wordBox.printText();
            window->display();
            actTime = clock.getElapsedTime();

        }
        window->clear();
        wordBox.clearString();
        std::ostringstream strs;
        strs << "WPM=" << (double(goodLetters + badLetters) / 5.0 - badLetters) / timeLimit * 60;
        wordBox.updateString(strs.str());
        wordBox.printText();
        window->display();
        {
            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    window->close();
                }
            }
        }
    }
}


int GameEngine::loadN()
{
    int n = wordLimit;
    int retIndex = wordIndex;
    wordBox.clearString();
    for(int i = 0; i < n; i ++)
    {
        wordBox.updateString( wordList[ (wordIndex + i) % wordList.size() ] );
        wordBox.updateString(" ");
    }
    wordIndex = (wordIndex + 1) % wordList.size();
    int retSize = wordList[retIndex].size();
    return retSize;
}


void GameEngine::loadWords(std::string name)
{
    std::ifstream iFile(name);
    if(iFile.is_open())
    {
        std::string line;
        while( getline(iFile, line) )
        {
            wordList.push_back(line);
        }
        iFile.close();
    }
    else
        throw(1);
}
