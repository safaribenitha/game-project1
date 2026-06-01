#include "Tree.h"

Tree::Tree(const sf::Vector2f& treePosition) : position(treePosition) {
    shadow.setRadius(39.f);
    shadow.setOrigin(sf::Vector2f(39.f, 39.f));
    shadow.setScale(sf::Vector2f(1.25f, 0.38f));
    shadow.setFillColor(sf::Color(0, 0, 0, 70));
    shadow.setPosition(sf::Vector2f(position.x, position.y + 34.f));

    trunk.setSize(sf::Vector2f(16.f, 42.f));
    trunk.setFillColor(sf::Color(112, 73, 42));
    trunk.setOutlineColor(sf::Color(53, 34, 22));
    trunk.setOutlineThickness(2.f);
    trunk.setOrigin(sf::Vector2f(8.f, 21.f));
    trunk.setPosition(sf::Vector2f(position.x, position.y + 15.f));

    canopyBack.setRadius(38.f);
    canopyBack.setFillColor(sf::Color(15, 72, 36));
    canopyBack.setOrigin(sf::Vector2f(38.f, 38.f));
    canopyBack.setPosition(sf::Vector2f(position.x + 4.f, position.y - 6.f));

    canopy.setRadius(34.f);
    canopy.setFillColor(sf::Color(27, 118, 54));
    canopy.setOrigin(sf::Vector2f(34.f, 34.f));
    canopy.setPosition(sf::Vector2f(position.x, position.y - 12.f));

    canopyLeft.setRadius(24.f);
    canopyLeft.setFillColor(sf::Color(35, 133, 64));
    canopyLeft.setOrigin(sf::Vector2f(24.f, 24.f));
    canopyLeft.setPosition(sf::Vector2f(position.x - 24.f, position.y - 5.f));

    canopyRight.setRadius(25.f);
    canopyRight.setFillColor(sf::Color(21, 93, 47));
    canopyRight.setOrigin(sf::Vector2f(25.f, 25.f));
    canopyRight.setPosition(sf::Vector2f(position.x + 26.f, position.y - 4.f));

    canopyHighlight.setRadius(12.f);
    canopyHighlight.setFillColor(sf::Color(88, 169, 79, 120));
    canopyHighlight.setOrigin(sf::Vector2f(12.f, 12.f));
    canopyHighlight.setPosition(sf::Vector2f(position.x - 10.f, position.y - 28.f));
}

void Tree::update(float) {}

void Tree::draw(sf::RenderWindow& window) {
    window.draw(shadow);
    window.draw(trunk);
    window.draw(canopyBack);
    window.draw(canopyLeft);
    window.draw(canopyRight);
    window.draw(canopy);
    window.draw(canopyHighlight);
}

sf::Vector2f Tree::getPosition() const {
    return position;
}

float Tree::getCollisionRadius() const {
    return 48.f;
}
