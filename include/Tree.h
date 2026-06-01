#pragma once

#include "GameObject.h"

/**
 * Static tree obstacle that protects the vampire from sun damage while nearby.
 */
class Tree : public GameObject {
public:
    explicit Tree(const sf::Vector2f& position);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const override;
    float getCollisionRadius() const override;

private:
    sf::Vector2f position;
    sf::RectangleShape trunk;
    sf::CircleShape canopy;
};
