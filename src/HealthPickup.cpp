#include "HealthPickup.h"
#include "Vampire.h"

HealthPickup::HealthPickup(const sf::Vector2f& position)
    : Pickup(position, sf::Color(210, 30, 55)) {}

void HealthPickup::apply(Vampire& vampire) {
    vampire.heal(healAmount);
    destroy();
}
