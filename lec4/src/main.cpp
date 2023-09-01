#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


class Shape 
{
protected:
    std::string name;
    int  R, G, B;
    float  x, y, sx, sy;
public:
    Shape(const std::string& name ,float x, float y, float sx, float sy, int R, int G, int B)
    : name(name)
    , x(x)
    , y(y)
    , sx(sx)
    , sy(sy)
    , R(R)
    , G(G)
    , B(B)
    {
    }
};
class Rect : public Shape 
{
private:
    int W, H;
    sf::RectangleShape rect;
public:
    Rect(const std::string& name ,float x, float y, float sx, float sy, int R, int G, int B, float w, float h)
    : Shape(name, x, y, sx, sy, R, G, B)
    , W(w)
    , H(h)
    {
        rect.setSize(sf::Vector2f(w, h));
        rect.setFillColor(sf::Color(R, G, B));
        rect.setPosition(x, y);
    }
    void draw(sf::RenderWindow & win)
    {
        
        win.draw(rect);
    }
    void update(int win_width, int win_heigth)
    {
        rect.move(sx, sy);
    }
};

class Circle : Shape 
{
private: 
    float radius;
    sf::CircleShape cirlce;
public:
    Circle(const std::string& name ,float x, float y, float sx, float sy, int R, int G, int B, float raduis)
    : Shape(name, x, y, sx, sy, R, G, B)
    , radius(radius)
    {
        cirlce.setRadius(raduis);
        cirlce.setFillColor(sf::Color(R, G, B));
        cirlce.setPosition(x, y);
    }
    void draw(sf::RenderWindow & win)
    {
        win.draw(cirlce);
    }
    void update(int win_width, int win_heigth)
    {
        if(x <= 0 || x + radius >= win_width)
        {
            std::cout << "do something" << std::endl;
        }
        else if (y <= 0 || y + radius >= win_heigth)
        {
            std::cout << "do something again" << std::endl;
        }
        cirlce.move(sf::Vector2f(sx, sy));
    }
};


int main() {
    // Read the config file
    std::ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config.txt" << std::endl;
        return 1;
    }

    int width = 0, height = 0;
    std::string name;
    float x, y, sx, sy, w, h, radius;
    int R, G, B;
    std::vector <Circle> cirlces;
    std::vector <Rect> rects;

    std::string line;
    std::string command;
    while (std::getline(configFile, line)) {
        std::istringstream sss(line);
        sss >> command;
        if (command == "window")
        {
            sss >> width >> height;
        }
        else if (command == "circle")
        {
            sss >> name >> x >> y >> sx >> sy >> R >> G >> B >> radius;
            Circle circle(name, x, y, sx, sy, R, G, B, radius);
            cirlces.push_back(circle);
        }
        else if (command == "rectangle")
        {
            sss >> name >> x >> y >> sx >> sy >> R >> G >> B >> w >> h;
            Rect rect(name, x, y, sx, sy, R, G, B, w, h);
            rects.push_back(rect);
        }
    }

    configFile.close();
   
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML Example");
    
    while (window.isOpen()) 
    {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear(sf::Color::White);
        for (auto &rec : rects)
        {
            rec.update(width, height);
            rec.draw(window);
        }
        for(auto &cir : cirlces)
        {
            cir.update(width, height);
            cir.draw(window);
        }
        
        // Draw your game objects here
        
        // Display the contents of the window
        window.display();
    }

    return 0;
}
