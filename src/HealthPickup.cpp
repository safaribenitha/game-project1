#include "HealthPickup.h"
#include "Vampire.h"
#include <cmath>

HealthPickup::HealthPickup(const sf::Vector2f& position)
    : Pickup(position, sf::Color(40, 190, 82)) {}

void HealthPickup::draw(sf::RenderWindow& window) {
    const float pulse = 1.f + 0.08f * std::sin(pulseTimer * 5.f);

    sf::CircleShape glow(25.f);
    glow.setOrigin(sf::Vector2f(25.f, 25.f));
    glow.setPosition(position);
    glow.setScale(sf::Vector2f(pulse, pulse));
    glow.setFillColor(sf::Color(40, 190, 82, 70));
    window.draw(glow);

    sf::RectangleShape vertical(sf::Vector2f(12.f, 34.f));
    vertical.setOrigin(sf::Vector2f(6.f, 17.f));
    vertical.setPosition(position);
    vertical.setScale(sf::Vector2f(pulse, pulse));
    vertical.setFillColor(sf::Color(54, 220, 96));
    vertical.setOutlineColor(sf::Color(236, 255, 232));
    vertical.setOutlineThickness(2.f);
    window.draw(vertical);

    sf::RectangleShape horizontal(sf::Vector2f(34.f, 12.f));
    horizontal.setOrigin(sf::Vector2f(17.f, 6.f));
    horizontal.setPosition(position);
    horizontal.setScale(sf::Vector2f(pulse, pulse));
    horizontal.setFillColor(sf::Color(54, 220, 96));
    horizontal.setOutlineColor(sf::Color(236, 255, 232));
    horizontal.setOutlineThickness(2.f);
    window.draw(horizontal);
}

void HealthPickup::apply(Vampire& vampire) {
    vampire.heal(healAmount);
    destroy();
}
