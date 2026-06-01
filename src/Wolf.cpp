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

void Wolf::attack(Vampire& vampire) {
    if (canAttack()) {
        vampire.takeDamage(damage);
        attackTimer = 0.f;
    }
}

bool Wolf::canAttack() const {
    return attackTimer >= attackCooldown;
}
