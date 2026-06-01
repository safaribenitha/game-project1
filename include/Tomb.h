#pragma once

#include "GameObject.h"

/**
 * Goal object. Reaching the tomb before dying wins the game.
 */
class Tomb : public GameObject {
public:
    explicit Tomb(const sf::Vector2f& position);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const override;
    float getCollisionRadius() const override;

private:
    sf::Vector2f position;
    sf::CircleShape shadow;
    sf::RectangleShape base;
    sf::RectangleShape lid;
    sf::RectangleShape face;
    sf::RectangleShape crossVertical;
    sf::RectangleShape crossHorizontal;
    sf::RectangleShape crack;
};
