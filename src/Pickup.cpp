#include "Pickup.h"
#include <cmath>

Pickup::Pickup(const sf::Vector2f& pickupPosition, const sf::Color& color) : position(pickupPosition) {
    shape.setRadius(13.f);
    shape.setOrigin(sf::Vector2f(13.f, 13.f));
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    shape.setPosition(position);
}

void Pickup::update(float deltaTime) {
    pulseTimer += deltaTime;
    const float scale = 1.f + 0.12f * std::sin(pulseTimer * 5.f);
    shape.setScale(sf::Vector2f(scale, scale));
}

void Pickup::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Pickup::getPosition() const {
    return position;
}

float Pickup::getCollisionRadius() const {
    return 18.f;
}
