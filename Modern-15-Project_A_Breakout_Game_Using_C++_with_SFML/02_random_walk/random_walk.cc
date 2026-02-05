#include <optional>
#include <random>
#include <string>

#include <SFML/Graphics.hpp>

#include "constants.h"

using namespace std;
using namespace std::literals;

// Class to represent the creature moving around the screen
class Creature {
    // Static random number engine and Bernoulli distribution objects
    static mt19937 mt;
    static bernoulli_distribution bd;

    // Define some properties of the creature
    // SFML uses float internally
    float vx{4.0f};
    float vy{4.0f};
    sf::Vector2f velocity;

    // We use the SFML CircleShape
    sf::CircleShape circle;

  public:
    // Interface of the class

    // Constructor
    // Arguments are the initial coordinates of the centre of the ball
    // SFML uses the computer graphics convention
    // (0, 0) is the top left corner of the screen
    // x increases to the right
    // y increases downwards
    Creature(float x, float y) {
        // Set the initial position and velocity
        // Use (x, y) for the initial position
        velocity = {vx, vy};
        circle.setPosition({x, y});

        // Set the graphical properties
        circle.setRadius(5.0f);
        circle.setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow &window) {
        // Ask the window to draw the shape for us
        window.draw(circle);
    }

    // Compute the creature's new position
    void update() {
        // Change the direction of movement at random
        vx = bd(mt) ? vx : -vx;
        vy = bd(mt) ? vy : -vy;

        // Move the creature to its new position
        circle.move({vx, vy});
    }
};

// Initialize static members
mt19937 Creature::mt;
bernoulli_distribution Creature::bd;

// The main function for the program
int main() {
    // Create a creature object in the middle of the screen
    Creature the_creature(constants::window_width / 2.0, constants::window_height / 2.0);

    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow window{sf::VideoMode({constants::window_width, constants::window_height}),
                            "Random Walk"s};

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    window.setFramerateLimit(60); // Max rate is 60 frames per second

    // Game loop
    // Clear the screen
    // Check for user input
    // Calculate the updated graphics
    // Display the updated graphics

    while (true) {
        // Clear the screen
        window.clear(sf::Color::Black);

        // Check for any events

        // If the user pressed "Escape", or clicked on "close", we close the window
        // This will terminate the program
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
            break;
        }

        // Calculate the updated graphics
        the_creature.update();

        // Display the updated graphics
        the_creature.draw(window);
        window.display();
    }
}
