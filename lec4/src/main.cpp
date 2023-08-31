#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


// make a text class that will be drawed and updated and each shape gotta have one
class FontClass {
private:
    std::string fontName;
    int fontSize;
    sf::Color fontColor;
    sf::Font font;
    
public:
    FontClass() : fontSize(0), fontColor(sf::Color::Black) {
    }

    void setFont(const std::string& name, int size, int r, int g, int b) {
        fontName = name;
        fontSize = size;
        fontColor = sf::Color(r, g, b);

        if (!font.loadFromFile(fontName)) {
            std::cout << "Cannot load " << fontName << std::endl;
        }
    }

    sf::Font& getFont() {
        return font;
    }

    const sf::Color& getColor() const {
        return fontColor;
    }

    int getFontSize() const {
        return fontSize;
    }
};



// Shape
class Shape {
protected:
    std::string name;
    int x, y;
    float sx;
    float sy;
    int R, G, B;
    FontClass font;
    sf::Text text;

public:
    Shape(std::string name, int x, int y, float sx, float sy, int r, int g, int b, FontClass &font)
    : name(name)
    , x(x)
    , y(y)
    , sx(sx)
    , sy(sy)
    , R(r), G(g), B(b)
    , font(font)
    {
        text.setFont(font.getFont());
        text.setFillColor(font.getColor());
        text.setCharacterSize(font.getFontSize());
    }
    
};


// circle
class Circle : public Shape 
{
private:
    int radius;
    sf::CircleShape circle;
    sf::Vector2f cirlceCenter;
    sf::FloatRect textBounds;

public:
    Circle(const std::string& name, int x, int y, float sx, float sy, int r, int g, int b, int radius, FontClass &font)
    : Shape(name, x, y, sx, sy, r, g, b, font)
    , radius(radius)
    {
        circle.setRadius(radius);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color(R, G, B));
        text.setString(name);
        
    }
    void update()
    {
        cirlceCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
        textBounds   =  text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(cirlceCenter);
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
        win.draw(text);
    }
};

// rect
class Rect : public Shape 
{
private:
    int width;
    int hieght;
    sf::RectangleShape rect;
    sf::Vector2f rectangleCenter;
    sf::FloatRect textBounds;
public:
    Rect(const std::string& name, int x, int y, float sx, float sy, int r, int g, int b, int w, int h, FontClass &font)
    : Shape(name, x, y, sx, sy, r, g, b, font)
    , width(w)
    , hieght(h)
    {
        rect.setSize(sf::Vector2f(width, hieght));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color(R, G, B));
        text.setString(name);

    }
    
    void update()
    {
        sf::Vector2f rectangleCenter = rect.getPosition() + 0.5f * rect.getSize();
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(rectangleCenter);

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
        win.draw(text);
    }
};


// Game Engine
class GameEngine {
public:
    GameEngine()
    : width(600), height(600)
    {
        std::string title = "C4003";
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
    void SetWindowSize(int w, int h)
    {
        window.setSize(sf::Vector2u(w, h));
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
int main(int argc, char* argv[])
{
    int w, h;
    GameEngine game;
    FontClass font;

    std::ifstream file("config.txt");
    if (!file.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return -1;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "window")
        {
            iss >> w >> h;
        }
        else if (command == "font")
        {
            std::string fontPath;
            int size, r, g, b;
            iss >> fontPath >> size >> r >> g >> b;
            font.setFont(fontPath, size, r, g, b);
        }
        else if (command == "circle")
        {
            Circle circle("CBlue", 200, 200, 0.02, 0.04, 0, 0, 255, 100, font);
            game.set_circle(circle);
        }
        else if (command == "rectangle")
        {
            Rect rect("RRed", 200, 200, 0.1, 0.15, 255, 0, 0, 50, 25, font);
            game.set_rectangle(rect);        
        }
    }   
    game.SetWindowSize(w, h);
    game.run();
    return 0;
 
}
