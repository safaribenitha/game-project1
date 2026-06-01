#include "DaggerPickup.h"
#include "Vampire.h"
#include <cmath>

DaggerPickup::DaggerPickup(const sf::Vector2f& position)
    : Pickup(position, sf::Color(205, 212, 218)) {}

void DaggerPickup::draw(sf::RenderWindow& window) {
    const float pulse = 1.f + 0.08f * std::sin(pulseTimer * 5.f);

    sf::CircleShape glow(23.f);
    glow.setOrigin(sf::Vector2f(23.f, 23.f));
    glow.setPosition(position);
    glow.setScale(sf::Vector2f(pulse, pulse));
    glow.setFillColor(sf::Color(220, 225, 230, 64));
    window.draw(glow);

    sf::ConvexShape blade(4);
    blade.setPoint(0, sf::Vector2f(0.f, -23.f));
    blade.setPoint(1, sf::Vector2f(7.f, 2.f));
    blade.setPoint(2, sf::Vector2f(0.f, 12.f));
    blade.setPoint(3, sf::Vector2f(-7.f, 2.f));
    blade.setOrigin(sf::Vector2f(0.f, 0.f));
    blade.setPosition(position);
    blade.setScale(sf::Vector2f(pulse, pulse));
    blade.setRotation(sf::degrees(38.f));
    blade.setFillColor(sf::Color(210, 218, 225));
    blade.setOutlineColor(sf::Color(82, 90, 96));
    blade.setOutlineThickness(2.f);
    window.draw(blade);

    sf::RectangleShape guard(sf::Vector2f(24.f, 5.f));
    guard.setOrigin(sf::Vector2f(12.f, 2.5f));
    guard.setPosition(position + sf::Vector2f(5.f, 8.f));
    guard.setRotation(sf::degrees(38.f));
    guard.setScale(sf::Vector2f(pulse, pulse));
    guard.setFillColor(sf::Color(120, 96, 58));
    window.draw(guard);

    sf::RectangleShape grip(sf::Vector2f(6.f, 17.f));
    grip.setOrigin(sf::Vector2f(3.f, 0.f));
    grip.setPosition(position + sf::Vector2f(10.f, 12.f));
    grip.setRotation(sf::degrees(38.f));
    grip.setScale(sf::Vector2f(pulse, pulse));
    grip.setFillColor(sf::Color(70, 45, 34));
    window.draw(grip);
}

void DaggerPickup::apply(Vampire& vampire) {
    vampire.increaseDamage(damageBoost);
    destroy();
}
