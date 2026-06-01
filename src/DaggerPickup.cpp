#include "DaggerPickup.h"
#include "Vampire.h"

DaggerPickup::DaggerPickup(const sf::Vector2f& position)
    : Pickup(position, sf::Color(225, 225, 70)) {}

void DaggerPickup::apply(Vampire& vampire) {
    vampire.increaseDamage(damageBoost);
    destroy();
}
