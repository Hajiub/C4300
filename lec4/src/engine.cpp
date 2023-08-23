#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Game engine
class GameEngine {
public:
    GameEngine(int screenWidth, int screenHeight, const std::string& title)
        : screenWidth(screenWidth), screenHeight(screenHeight)
    {
        window.create(sf::VideoMode(screenWidth, screenHeight), title);
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

    void processInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void update(sf::Time deltaTime) {
        // Update game logic here
    }

    void render() {
        window.clear();
        // Render game objects here
        window.display();
    }
};

// Shapes
// Rect
// Cricle 
// ConfigFromfile


int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const std::string title = "Game Engine using SFML";

    GameEngine game(screenWidth, screenHeight, title);
    game.run();

    return 0;
}
