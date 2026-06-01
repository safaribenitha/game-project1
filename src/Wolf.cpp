#include "Wolf.h"
#include "Vampire.h"
#include <cmath>

Wolf::Wolf(const sf::Vector2f& startPosition, Vampire* targetVampire)
    : Character(startPosition, 45, 12, 120.f, sf::Color(90, 90, 95), sf::Color(130, 130, 135)),
      target(targetVampire) {}

void Wolf::update(float deltaTime) {
    attackTimer += deltaTime;

    if (target != nullptr && target->isAlive()) {
        sf::Vector2f direction = target->getPosition() - position;
        const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 1.f) {
            direction.x /= length;
            direction.y /= length;
            moveBy(direction * speed, deltaTime);
        }
    }

    animate(deltaTime);
}

void Wolf::draw(sf::RenderWindow& window) {
    sf::CircleShape shadow(21.f);
    shadow.setOrigin(sf::Vector2f(21.f, 21.f));
    shadow.setScale(sf::Vector2f(1.75f, 0.42f));
    shadow.setPosition(sf::Vector2f(position.x, position.y + 19.f));
    shadow.setFillColor(sf::Color(0, 0, 0, 88));
    window.draw(shadow);

    // The wolf is drawn as a low, grey animal silhouette instead of a humanoid sprite.
    sf::CircleShape body(20.f);
    body.setOrigin(sf::Vector2f(20.f, 20.f));
    body.setScale(sf::Vector2f(1.35f, 0.72f));
    body.setPosition(position);
    body.setFillColor(sf::Color(70, 73, 78));
    body.setOutlineColor(sf::Color(30, 31, 35));
    body.setOutlineThickness(2.f);
    window.draw(body);

    sf::CircleShape head(13.f);
    head.setOrigin(sf::Vector2f(13.f, 13.f));
    head.setPosition(sf::Vector2f(position.x - 25.f, position.y - 6.f));
    head.setFillColor(sf::Color(82, 85, 90));
    head.setOutlineColor(sf::Color(30, 31, 35));
    head.setOutlineThickness(2.f);
    window.draw(head);

    sf::ConvexShape ear(3);
    ear.setPoint(0, sf::Vector2f(0.f, -16.f));
    ear.setPoint(1, sf::Vector2f(8.f, 0.f));
    ear.setPoint(2, sf::Vector2f(-7.f, 0.f));
    ear.setPosition(sf::Vector2f(position.x - 31.f, position.y - 17.f));
    ear.setFillColor(sf::Color(55, 57, 62));
    window.draw(ear);

    sf::ConvexShape snout(3);
    snout.setPoint(0, sf::Vector2f(-16.f, 0.f));
    snout.setPoint(1, sf::Vector2f(0.f, -7.f));
    snout.setPoint(2, sf::Vector2f(0.f, 7.f));
    snout.setPosition(sf::Vector2f(position.x - 35.f, position.y - 5.f));
    snout.setFillColor(sf::Color(62, 64, 69));
    window.draw(snout);

    sf::ConvexShape tail(3);
    tail.setPoint(0, sf::Vector2f(0.f, 0.f));
    tail.setPoint(1, sf::Vector2f(24.f, -11.f));
    tail.setPoint(2, sf::Vector2f(17.f, 9.f));
    tail.setPosition(sf::Vector2f(position.x + 23.f, position.y - 4.f));
    tail.setFillColor(sf::Color(58, 60, 65));
    window.draw(tail);

    const float legBob = std::sin(attackTimer * 8.f) * 2.f;
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape leg(sf::Vector2f(5.f, 18.f));
        leg.setOrigin(sf::Vector2f(2.5f, 0.f));
        leg.setPosition(sf::Vector2f(position.x - 15.f + i * 10.f, position.y + 8.f + ((i % 2 == 0) ? legBob : -legBob)));
        leg.setFillColor(sf::Color(45, 47, 51));
        window.draw(leg);
    }

    sf::CircleShape eye(2.2f);
    eye.setOrigin(sf::Vector2f(2.2f, 2.2f));
    eye.setPosition(sf::Vector2f(position.x - 32.f, position.y - 8.f));
    eye.setFillColor(sf::Color(230, 210, 80));
    window.draw(eye);
}

void Wolf::attack(Vampire& vampire) {
    if (canAttack()) {
        vampire.takeDamage(damage);
        attackTimer = 0.f;
    }
}

bool Wolf::canAttack() const {
    return attackTimer >= attackCooldown;
}
