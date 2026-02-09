#include "background.h"

#include <stdexcept>

// Initialize static data member
sf::Texture Background::texture;

Background::Background(float x, float y) : Entity(texture) {
    // Load the texture
    if (!this->texture.loadFromFile("background.jpg")) {
        throw std::runtime_error("Failed to load background.jpg");
    }

    this->sprite.setTexture(texture, true);

    // Set the initial position and velocity of the background
    // Use (x, y) for the initial position of the background
    this->sprite.setPosition({x, y});
}

// Compute the background's new position
void Background::update() {
    // Nothing to do here
}

void Background::draw(sf::RenderWindow &window) {
    // Ask the window to draw the sprite for us
    window.draw(sprite);
}
