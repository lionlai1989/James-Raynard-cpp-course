// Code for a "breakout" game
// Based on a talk by Vittorio Romeo
// Uses the SFML graphics library
#include <SFML/Graphics.hpp>

#include "constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include "background.h"

using namespace std::string_literals;

// The main function for the program
int main() {
    // Create the background object
    Background the_background(0.0f, 0.0f);

    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow game_window{
        sf::VideoMode({Constants::window_width, Constants::window_height}),
        "Simple Breakout Game Version 1"s,
    };

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    game_window.setFramerateLimit(60); // Max rate is 60 frames per second

    // Game loop
    // Clear the screen
    // Check for new events
    // Calculate the updated graphics
    // Display the updated graphics
    while (game_window.isOpen()) {
        // Clear the screen
        game_window.clear(sf::Color::Black);

        // Check for any events since the last loop iteration
        while (const std::optional event = game_window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                game_window.close();
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    game_window.close();
            }
        }

        // Calculate the updated graphics
        the_background.update();

        // Display the updated graphics
        the_background.draw(game_window);
        game_window.display();
    }
}
