class Textbox
{
private:
    std::string inputText;
    sf::Font textFont;
    sf::Text text;
    sf::RenderWindow *window;
public:
    Textbox(sf::RenderWindow *orgWindow, sf::Color color);
    void setFont(sf::Font font);
    void setPosition(sf::Vector2f pos);
    void printText();
    void clearString();
    void updateString(std::string newText);
    std::string getText();
};

Textbox::Textbox(sf::RenderWindow *orgWindow, sf::Color color){
    window = orgWindow;
    text.setString("");
    //text.setCharacterSize(size);
    text.setColor(color);
    //charLimit = limit;
}

void Textbox::setFont(sf::Font font)
{
    textFont = font;
    text.setFont(textFont);
}

void Textbox::setPosition(sf::Vector2f pos)
{
    text.setPosition(pos);
}


void Textbox::printText()
{
    text.setString(inputText);
    window->draw(text);
}
void Textbox::clearString()
{
    inputText = "";
}
void Textbox::updateString(std::string newText)
{
    inputText += newText;
}

std::string Textbox::getText()
{
    return inputText;
}
