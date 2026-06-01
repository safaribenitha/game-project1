#include "Tree.h"

Tree::Tree(const sf::Vector2f& treePosition) : position(treePosition) {
    trunk.setSize(sf::Vector2f(16.f, 42.f));
    trunk.setFillColor(sf::Color(95, 58, 32));
    trunk.setOrigin(8.f, 21.f);
    trunk.setPosition(position.x, position.y + 15.f);

    canopy.setRadius(34.f);
    canopy.setFillColor(sf::Color(25, 110, 45));
    canopy.setOrigin(34.f, 34.f);
    canopy.setPosition(position.x, position.y - 12.f);
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
