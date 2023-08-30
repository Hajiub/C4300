#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


void loadConfig(const std::string& filname)
{
    std::ifstream file(filname);
    if (!file.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }


    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "window")
        {
         
        }
        else if (command == "font")
        {
        }
        else if (command == "circle")
        {
         
        }
        else if (command == "rectangle")
        {
         
        }
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Moving Shape in SFML");
    
    // Circle
    sf::CircleShape circle(50); 
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(375, 275);
    
    // Rectangle
    sf::RectangleShape rect(sf::Vector2f(120, 50));
    rect.setFillColor(sf::Color(255, 0, 0));
    rect.setPosition(100, 200);


    // Font
    sf::Font font;
    if(!font.loadFromFile("fonts/tech.ttf"))
    {
        std::cout << "cannot load the font"<< std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("Rect");
    text.setCharacterSize(18);
    text.setPosition(sf::Vector2f(160.f, 225.f));
    
    sf::Text cirl;
    cirl.setFont(font);
    cirl.setFillColor(sf::Color::White);
    cirl.setString("Circle");
    cirl.setCharacterSize(18);
    
     

    float sx = 0.15f; 
    float sy = 0.1f;
    float rx = 0.1;
    float ry = 0.2;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        if (circle.getPosition().y < 0 | circle.getPosition().y + 2 * (circle.getRadius()) > 600 )
        {
            
            sy *= -1;
        }
        else if (circle.getPosition().x < 0 | circle.getPosition().x + 2 * ( circle.getRadius()) > 800)
        {
            
            sx *= - 1;
        }

        if (rect.getPosition().x < 0 | rect.getPosition().x + rect.getSize().x > 800)
        {
            rx *= - 1;
        }
        else if(rect.getPosition().y < 0 | rect.getPosition().y + rect.getSize().y > 600)
        {
            ry *= - 1;
        }

        sf::Vector2f rectangleCenter = rect.getPosition() + 0.5f * rect.getSize();
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(rectangleCenter);

        sf::Vector2f CircleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
        sf::FloatRect cirlBounds = cirl.getGlobalBounds();
        cirl.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        cirl.setPosition(CircleCenter);
        circle.move(sx, sy);
        rect.move(rx, ry);
        
        
        window.clear(sf::Color::White);
        window.draw(circle);
        window.draw(rect);
        window.draw(text);
        window.draw(cirl);
        window.display();
        
    }
    
    return 0;
}
