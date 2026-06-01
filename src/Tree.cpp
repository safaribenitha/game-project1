#include "Tree.h"

Tree::Tree(const sf::Vector2f& treePosition) : position(treePosition) {
    trunk.setSize(sf::Vector2f(16.f, 42.f));
    trunk.setFillColor(sf::Color(95, 58, 32));
    trunk.setOrigin(sf::Vector2f(8.f, 21.f));
    trunk.setPosition(sf::Vector2f(position.x, position.y + 15.f));

    canopy.setRadius(34.f);
    canopy.setFillColor(sf::Color(25, 110, 45));
    canopy.setOrigin(sf::Vector2f(34.f, 34.f));
    canopy.setPosition(sf::Vector2f(position.x, position.y - 12.f));
}

void Tree::update(float) {}

void Tree::draw(sf::RenderWindow& window) {
    window.draw(trunk);
    window.draw(canopy);
}

sf::Vector2f Tree::getPosition() const {
    return position;
}

float Tree::getCollisionRadius() const {
    return 48.f;
}
