#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


// Shape
class Shape {
protected:
    std::string name;
    int x, y;
    float sx;
    float sy;
    int R, G, B;

public:
    Shape(std::string name, int x, int y, float sx, float sy, int r, int g, int b)
    : name(name)
    , x(x)
    , y(y)
    , sx(sx)
    , sy(sy)
    , R(r), G(g), B(b)
    {
    }
};
// circle
class Circle : public Shape 
{
private:
    int radius;
    sf::CircleShape circle;
public:
    Circle(const std::string& name, int x, int y, float sx, float sy, int r, int g, int b, int radius)
    : Shape(name, x, y, sx, sy, r, g, b)
    , radius(radius)
    {
        circle.setRadius(radius);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color(R, G, B));
    }
    void update()
    {
        // handle this shit later 
        if (circle.getPosition().y < 0 | circle.getPosition().y + 2 * (circle.getRadius()) > 600 )
        {
            
            sy *= -1;
        }
        else if (circle.getPosition().x < 0 | circle.getPosition().x + 2 * ( circle.getRadius()) > 800)
        {
            
            sx *= - 1;
        }
        circle.move(sx, sy);
    }
    void draw(sf::RenderWindow &win)
    {
        win.draw(circle);
    }
};

// rect
class Rect : public Shape 
{
private:
    int width;
    int hieght;
    sf::RectangleShape rect;
public:
    Rect(const std::string& name, int x, int y, float sx, float sy, int r, int g, int b, int w, int h)
    : Shape(name, x, y, sx, sy, r, g, b)
    , width(w)
    , hieght(h)
    {
        rect.setSize(sf::Vector2f(width, hieght));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color(R, G, B));
    }
    
    void update()
    {

        if (rect.getPosition().x < 0 | rect.getPosition().x + rect.getSize().x > 800)
        {
            sx *= - 1;
        }
        else if(rect.getPosition().y < 0 | rect.getPosition().y + rect.getSize().y > 600)
        {
            sy *= - 1;
        }
        rect.move(sx, sy);
    }
    void draw(sf::RenderWindow& win)
    {
        win.draw(rect);
    }
};


// Game Engine
class GameEngine {
public:
    GameEngine(int width, int height, const std::string& title)
    : width(width), height(height)
    {
        window.create(sf::VideoMode(width, height), title);
    }

    void run()
    {
        sf::Clock clock;
        while(window.isOpen())
        {
            processInput();
            update();
            render();

        }
    }
    void set_circle(Circle& cirlce)
    {
        circles.push_back(cirlce);
    }

    void set_rectangle(Rect & rectangle)
    {
        rects.push_back(rectangle);
    }
private:
    int width;
    int height;
    std::vector <Circle> circles;
    std::vector <Rect> rects;
    sf::RenderWindow window;

    void processInput()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }
    }

    void update()
    {
         for (auto &a : circles)
        {
            a.update();
        }
        for(auto &a : rects)
        {
            a.update();   
        }
    }

    void render()
    {
        window.clear(sf::Color::White);
        // Render game objects here
        for (auto &a : circles)
        {
            a.draw(window);   
        }
        for(auto &a : rects)
        {
            a.draw(window);   
        }
        window.display();
    }
};


int main(int argc, char * argv[])
{
    const int w = 800;
    const int h = 600;    const std::string title = "C4043";
    Circle circle( "CBlue", 200, 200, 0.02, 0.04, 0, 0, 255, 100);
    Rect  rect("RRed", 200, 200, 0.1, 0.15, 255, 0, 0, 50, 25);
    GameEngine game(w, h, title);
    game.set_circle(circle);
    game.set_rectangle(rect);
    game.run();
    return 0;
}
