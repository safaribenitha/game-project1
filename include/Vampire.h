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

    /** Store the tomb position so W can guide the vampire toward the goal. */
    void setAutoMoveTarget(const sf::Vector2f& targetPosition);

    /** Dagger pickups permanently improve this value. */
    void increaseDamage(int amount);

private:
    bool hiddenFromSun{false};
    sf::Vector2f autoMoveTarget{900.f, 680.f};
    float sunDamagePerSecond{1.2f};
    float sunDamageAccumulator{0.f};
};
