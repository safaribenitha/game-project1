#pragma once

#include "Pickup.h"

/** Dagger pickup that permanently increases vampire attack damage. */
class DaggerPickup : public Pickup {
public:
    explicit DaggerPickup(const sf::Vector2f& position);

    /** Draw a small silver dagger instead of a generic pickup circle. */
    void draw(sf::RenderWindow& window) override;

    /** Increase the vampire's attack damage. */
    void apply(Vampire& vampire) override;

private:
    int damageBoost{6};
};
