#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class GameEngine {
public:
    GameEngine(int screenWidth, int screenHeight, const std::string& title)
        : screenWidth(screenWidth), screenHeight(screenHeight)
    {
        window.create(sf::VideoMode(screenWidth, screenHeight), title);
    }

    void setCircle(const sf::CircleShape& circleShape) {
        circle = circleShape;
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Time deltaTime = clock.restart();
            
            processInput();
            update(deltaTime);
            render();
        }
    }

private:
    int screenWidth;
    int screenHeight;
    sf::RenderWindow window;
    sf::CircleShape circle;  // The game object (circle)
    sf::Vector2f circleVelocity = sf::Vector2f(0.0f, 0.0f);  // Initial velocity
    float gravity = 1000.0f; // Gravity force

    void processInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && circle.getPosition().y + circle.getRadius() >= screenHeight) {
                    circleVelocity.y = -500.0f; // Apply upward velocity on space key press
                }
            }
        }
    }

    void update(sf::Time deltaTime) {
        // Apply gravity to the circle
        float timeInSeconds = deltaTime.asSeconds();
        float acceleration = gravity * timeInSeconds;
        circleVelocity.y += acceleration;
        
        // Update the position of the circle based on its velocity
        circle.move(circleVelocity * timeInSeconds);

        // Keep the circle within the screen bounds
        if (circle.getPosition().y + circle.getRadius() > screenHeight) {
            circle.setPosition(circle.getPosition().x, screenHeight - circle.getRadius());
            circleVelocity.y = 0.0f; // Reset vertical velocity when hitting the ground
        }
    }

    void render() {
        window.clear();
        
        // Render the circle
        window.draw(circle);
        
        window.display();
    }
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const std::string title = "Game Engine using SFML";

    sf::CircleShape circle(30.0f); // Radius of the circle
    circle.setPosition(screenWidth / 2.0f, screenHeight / 2.0f); // Initial position

    GameEngine game(screenWidth, screenHeight, title);
    game.setCircle(circle);

    game.run();

    return 0;
}
