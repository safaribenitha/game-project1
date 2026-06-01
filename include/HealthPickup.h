#pragma once

#include "Pickup.h"

/** Health pickup that restores vampire HP when collected. */
class HealthPickup : public Pickup {
public:
    explicit HealthPickup(const sf::Vector2f& position);

    /** Draw a green medical cross so this pickup is easy to identify. */
    void draw(sf::RenderWindow& window) override;

    /** Restore a fixed amount of vampire health. */
    void apply(Vampire& vampire) override;

private:
    int healAmount{25};
};
