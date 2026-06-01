#pragma once

#include "GameObject.h"

class Vampire;

/**
 * Abstract collectible base class.
 *
 * Concrete pickups implement apply() to change vampire stats when collected.
 */
class Pickup : public GameObject {
public:
    Pickup(const sf::Vector2f& position, const sf::Color& color);
    ~Pickup() override = default;

    /** Animate the pickup with a small pulsing effect. */
    void update(float deltaTime) override;

    void draw(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const override;
    float getCollisionRadius() const override;

    /** Apply the pickup effect to the vampire; implemented by subclasses. */
    virtual void apply(Vampire& vampire) = 0;

protected:
    sf::Vector2f position;
    sf::CircleShape glow;
    sf::CircleShape shape;
    sf::CircleShape center;
    float pulseTimer{0.f};
};
