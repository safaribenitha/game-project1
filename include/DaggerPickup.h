#pragma once

#include "Pickup.h"

/** Dagger pickup that permanently increases vampire attack damage. */
class DaggerPickup : public Pickup {
public:
    explicit DaggerPickup(const sf::Vector2f& position);

    /** Increase the vampire's attack damage. */
    void apply(Vampire& vampire) override;

private:
    int damageBoost{6};
};
