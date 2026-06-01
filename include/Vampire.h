#pragma once

#include "Character.h"

/**
 * Player-controlled vampire.
 *
 * The vampire moves with the keyboard, loses health in sunlight unless hidden
 * by trees, can receive pickup bonuses and must reach the tomb to win.
 */
class Vampire : public Character {
public:
    explicit Vampire(const sf::Vector2f& startPosition);

    /** Poll keyboard state and move the vampire using delta-time movement. */
    void update(float deltaTime) override;

    /** Apply sun damage only when the vampire is not hiding behind a tree. */
    void applySunDamage(float deltaTime);

    void setHidden(bool hidden);
    bool isHidden() const;

    /** Dagger pickups permanently improve this value. */
    void increaseDamage(int amount);

private:
    bool hiddenFromSun{false};
    float sunDamagePerSecond{6.f};
    float sunDamageAccumulator{0.f};
};
