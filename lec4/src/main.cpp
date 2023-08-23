#include <SFML/Window.hpp>
#include <iostream>


int main()
{
    sf::Window window;
    window.create(sf::VideoMode(800, 600), "Window");
    window.setPosition(sf::Vector2i(10, 50));
    window.setSize(sf::Vector2u(640, 480));
    window.setTitle("Stupid");
    
    bool focus;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        focus = window.hasFocus();
    }
    std::cout << "Hello, world";
    return 0;
}