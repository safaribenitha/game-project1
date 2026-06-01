#include "Pickup.h"
#include <cmath>

Pickup::Pickup(const sf::Vector2f& pickupPosition, const sf::Color& color) : position(pickupPosition) {
    glow.setRadius(21.f);
    glow.setOrigin(sf::Vector2f(21.f, 21.f));
    glow.setFillColor(sf::Color(color.r, color.g, color.b, 58));
    glow.setPosition(position);

    shape.setRadius(13.f);
    shape.setOrigin(sf::Vector2f(13.f, 13.f));
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color(255, 247, 210));
    shape.setOutlineThickness(2.f);
    shape.setPosition(position);

    center.setRadius(5.f);
    center.setOrigin(sf::Vector2f(5.f, 5.f));
    center.setFillColor(sf::Color(255, 255, 245, 155));
    center.setPosition(sf::Vector2f(position.x - 3.f, position.y - 4.f));
}

void Pickup::update(float deltaTime) {
    pulseTimer += deltaTime;
    const float scale = 1.f + 0.12f * std::sin(pulseTimer * 5.f);
    shape.setScale(sf::Vector2f(scale, scale));
    glow.setScale(sf::Vector2f(1.05f + 0.18f * std::sin(pulseTimer * 4.f),
                               1.05f + 0.18f * std::sin(pulseTimer * 4.f)));
    center.setScale(sf::Vector2f(scale, scale));
}

void Pickup::draw(sf::RenderWindow& window) {
    window.draw(glow);
    window.draw(shape);
    window.draw(center);
}

sf::Vector2f Pickup::getPosition() const {
    return position;
}

float Pickup::getCollisionRadius() const {
    return 18.f;
}
