#include "Tomb.h"

Tomb::Tomb(const sf::Vector2f& tombPosition) : position(tombPosition) {
    shadow.setRadius(51.f);
    shadow.setOrigin(sf::Vector2f(51.f, 51.f));
    shadow.setScale(sf::Vector2f(1.22f, 0.32f));
    shadow.setFillColor(sf::Color(0, 0, 0, 92));
    shadow.setPosition(sf::Vector2f(position.x, position.y + 31.f));

    base.setSize(sf::Vector2f(78.f, 48.f));
    base.setFillColor(sf::Color(117, 119, 118));
    base.setOutlineColor(sf::Color(45, 45, 50));
    base.setOutlineThickness(3.f);
    base.setOrigin(sf::Vector2f(39.f, 24.f));
    base.setPosition(position);

    lid.setSize(sf::Vector2f(88.f, 14.f));
    lid.setFillColor(sf::Color(164, 164, 158));
    lid.setOutlineColor(sf::Color(66, 66, 69));
    lid.setOutlineThickness(2.f);
    lid.setOrigin(sf::Vector2f(44.f, 7.f));
    lid.setPosition(sf::Vector2f(position.x, position.y - 31.f));

    face.setSize(sf::Vector2f(58.f, 30.f));
    face.setFillColor(sf::Color(145, 146, 141, 130));
    face.setOrigin(sf::Vector2f(29.f, 15.f));
    face.setPosition(sf::Vector2f(position.x - 2.f, position.y - 2.f));

    crossVertical.setSize(sf::Vector2f(6.f, 24.f));
    crossVertical.setFillColor(sf::Color(58, 58, 62, 170));
    crossVertical.setOrigin(sf::Vector2f(3.f, 12.f));
    crossVertical.setPosition(sf::Vector2f(position.x - 18.f, position.y - 4.f));

    crossHorizontal.setSize(sf::Vector2f(20.f, 5.f));
    crossHorizontal.setFillColor(sf::Color(58, 58, 62, 170));
    crossHorizontal.setOrigin(sf::Vector2f(10.f, 2.5f));
    crossHorizontal.setPosition(sf::Vector2f(position.x - 18.f, position.y - 9.f));

    crack.setSize(sf::Vector2f(3.f, 24.f));
    crack.setFillColor(sf::Color(43, 43, 47, 150));
    crack.setOrigin(sf::Vector2f(1.5f, 12.f));
    crack.setRotation(sf::degrees(-18.f));
    crack.setPosition(sf::Vector2f(position.x + 18.f, position.y + 3.f));
}

void Tomb::update(float) {}

void Tomb::draw(sf::RenderWindow& window) {
    window.draw(shadow);
    window.draw(base);
    window.draw(face);
    window.draw(crossVertical);
    window.draw(crossHorizontal);
    window.draw(crack);
    window.draw(lid);
}

sf::Vector2f Tomb::getPosition() const {
    return position;
}

float Tomb::getCollisionRadius() const {
    return 46.f;
}
