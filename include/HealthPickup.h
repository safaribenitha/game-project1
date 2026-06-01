#pragma once

#include "Pickup.h"

/** Health pickup that restores vampire HP when collected. */
class HealthPickup : public Pickup {
public:
    explicit HealthPickup(const sf::Vector2f& position);

    /** Restore a fixed amount of vampire health. */
    void apply(Vampire& vampire) override;

private:
    int healAmount{25};
};
