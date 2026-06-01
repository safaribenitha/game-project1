#pragma once

#include "Character.h"

class Vampire;

/**
 * Enemy wolf that automatically chases and attacks the vampire.
 */
class Wolf : public Character {
public:
    Wolf(const sf::Vector2f& startPosition, Vampire* targetVampire);

    /** Move toward the vampire and update attack cooldown/animation. */
    void update(float deltaTime) override;

    /** Damage the vampire when close enough and the cooldown has elapsed. */
    void attack(Vampire& vampire);

    bool canAttack() const;

private:
    Vampire* target;
    float attackCooldown{1.0f};
    float attackTimer{0.f};
};
