#include "Tomb.h"

Tomb::Tomb(const sf::Vector2f& tombPosition) : position(tombPosition) {
    base.setSize(sf::Vector2f(78.f, 48.f));
    base.setFillColor(sf::Color(120, 120, 125));
    base.setOutlineColor(sf::Color(45, 45, 50));
    base.setOutlineThickness(3.f);
    base.setOrigin(39.f, 24.f);
    base.setPosition(position);

    lid.setSize(sf::Vector2f(88.f, 14.f));
    lid.setFillColor(sf::Color(150, 150, 155));
    lid.setOrigin(44.f, 7.f);
    lid.setPosition(position.x, position.y - 31.f);
}

void Tomb::update(float) {}

void Tomb::draw(sf::RenderWindow& window) {
    window.draw(base);
    window.draw(lid);
}

sf::Vector2f Tomb::getPosition() const {
    return position;
}

float Tomb::getCollisionRadius() const {
    return 46.f;
}
