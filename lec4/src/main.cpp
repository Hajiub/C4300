#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class FontClass
{
private:
    sf::Font font;
    sf::Color color;
    int size;
public:
    void setFont(const std::string &font_path, int font_size, int R, int G, int B)
    {
        if (!font.loadFromFile(font_path))
        {
            std::cout << "Cannot load the font" << std::endl;
            
        }
        size = font_size;
        color = sf::Color(R, G, B);
        
    }
    const sf::Font& getFon(void)
    {
        return font;
    }
    const sf::Color& getColor(void)
    {
        return color;
    }
    const int getSize(void)
    {
        return size;
    }
};

class Shape 
{
protected:
    std::string name;
    int  R, G, B;
    float  x, y, sx, sy;
    sf::Text text;
public:
    Shape(const std::string& name ,float x, float y, float sx, float sy, int R, int G, int B, FontClass& font)
    : name(name)
    , x(x)
    , y(y)
    , sx(sx)
    , sy(sy)
    , R(R)
    , G(G)
    , B(B)
    {
        text.setFont(font.getFon());
        text.setFillColor(font.getColor());
        text.setString(name);
        text.setCharacterSize(font.getSize());
    }
};
class Rect : public Shape 
{
private:
    int W, H;
    sf::RectangleShape rect;
    sf::Vector2f rectangleCenter;
public:
    Rect(const std::string& name ,float x, float y, float sx, float sy, int R, int G, int B, float w, float h, FontClass& font)
    : Shape(name, x, y, sx, sy, R, G, B, font)
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
        win.draw(text);
    }
    void update(int win_width, int win_heigth)
    {
        sf::Vector2f rectangleCenter = rect.getPosition() + 0.5f * rect.getSize();
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(rectangleCenter);
        if (rect.getPosition().x < 0 | rect.getPosition().x + rect.getSize().x >= win_width)
        {
            sx *= - 1;
        }
        else if(rect.getPosition().y < 0 | rect.getPosition().y + rect.getSize().y >= win_heigth)
        {
            sy *= - 1;
        }
        rect.move(sx, sy);
    }
};

class Circle : Shape 
{
private: 
    float radius;
    sf::CircleShape circle;
    sf::Vector2f circleCenter;
    
public:
    Circle(const std::string& name ,float x, float y, float sx, float sy, int R, int G, int B, float raduis, FontClass& font)
    : Shape(name, x, y, sx, sy, R, G, B, font)
    , radius(radius)
    {
        circle.setRadius(raduis);
        circle.setFillColor(sf::Color(R, G, B));
        circle.setPosition(x, y);
        
    }
    void draw(sf::RenderWindow & win)
    {
        win.draw(circle);
        win.draw(text);
    }
    void update(int win_width, int win_heigth)
    {
        sf::Vector2f CircleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(CircleCenter);
        if (circle.getPosition().y < 0 | circle.getPosition().y + 2 * (circle.getRadius()) > win_heigth )
        {
            
            sy *= -1;
        }
        else if (circle.getPosition().x < 0 | circle.getPosition().x + 2 * ( circle.getRadius()) > win_width)
        {
            
            sx *= - 1;
        }
        circle.move(sx, sy);
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
    FontClass ft;
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
            Circle circle(name, x, y, sx, sy, R, G, B, radius, ft);
            cirlces.push_back(circle);
        }
        else if (command == "rectangle")
        {
            sss >> name >> x >> y >> sx >> sy >> R >> G >> B >> w >> h;
            Rect rect(name, x, y, sx, sy, R, G, B, w, h, ft);
            rects.push_back(rect);
        }
        else if (command == "font")
        {
            sss >> name >> x >> R >> G >> B;
            ft.setFont(name, x, R, G, B);
        }
    }

    configFile.close();
   
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(width, height), "C4003");
    
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
