#include "Vampire.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

Vampire::Vampire(const sf::Vector2f& startPosition)
    : Character(startPosition, 100, 18, 210.f, sf::Color(120, 0, 160), sf::Color(170, 20, 210)) {}

void Vampire::update(float deltaTime) {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        direction.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        direction.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        direction.x += 1.f;
    }

    const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.f) {
        direction.x /= length;
        direction.y /= length;
    }

    moveBy(direction * speed, deltaTime);
    animate(deltaTime);
}

void Vampire::applySunDamage(float deltaTime) {
    if (hiddenFromSun) {
        sunDamageAccumulator = 0.f;
        return;
    }

    sunDamageAccumulator += sunDamagePerSecond * deltaTime;
    const int wholeDamage = static_cast<int>(sunDamageAccumulator);
    if (wholeDamage > 0) {
        takeDamage(wholeDamage);
        sunDamageAccumulator -= static_cast<float>(wholeDamage);
    }
}

void Vampire::setHidden(bool hidden) {
    hiddenFromSun = hidden;
}

bool Vampire::isHidden() const {
    return hiddenFromSun;
}

void Vampire::increaseDamage(int amount) {
    addDamage(amount);
}
