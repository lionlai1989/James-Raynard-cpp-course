// Code for a "breakout" game
// Based on a talk by Vittorio Romeo
// Uses the SFML graphics library

// 1. Related header (Not applicable for main.cc usually)

// 2. Standard Library
#include <optional>
#include <string>

// 3. Third-party Library
#include <SFML/Graphics.hpp>

// 4. Local Project Headers
#include "constants.h"

using namespace std::literals;

// The main function for the program
int main() {
    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow game_window{
        sf::VideoMode({constants::window_width, constants::window_height}),
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
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>();
                     keyPressed && keyPressed->code == sf::Keyboard::Key::Escape)
                game_window.close();
        }

        // Calculate the updated graphics
        // This space left intentionally blank!

        // Display the updated graphics
        game_window.display();
    }
}
