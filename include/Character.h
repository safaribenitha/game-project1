#pragma once

#include "GameObject.h"
#include <string>
#include <optional>

/**
 * Abstract animated character class shared by the player vampire and wolves.
 *
 * Character owns a generated sprite sheet, health, damage, speed and animation
 * state while leaving movement/combat behavior to derived classes.
 */
class Character : public GameObject {
public:
    Character(const sf::Vector2f& startPosition,
              int maxHealth,
              int baseDamage,
              float movementSpeed,
              const sf::Color& primaryColor,
              const sf::Color& secondaryColor);
    ~Character() override = default;

    /** Draw the animated sprite for all characters polymorphically. */
    void draw(sf::RenderWindow& window) override;

    sf::Vector2f getPosition() const override;
    float getCollisionRadius() const override;

    int getHealth() const;
    int getMaxHealth() const;
    int getDamage() const;
    bool isAlive() const;

    /** Reduce health by damage and deactivate the character if health reaches 0. */
    virtual void takeDamage(int amount);

    /** Restore health without exceeding maxHealth. */
    virtual void heal(int amount);

protected:
    /** Move by a velocity vector while keeping the character inside the play area. */
    void moveBy(const sf::Vector2f& velocity, float deltaTime);

    /** Step through a two-frame generated sprite animation. */
    void animate(float deltaTime);

    /** Increase this character's outgoing damage. */
    void addDamage(int amount);

    sf::Vector2f position;
    int health;
    int maxHealth;
    int damage;
    float speed;

private:
    void buildSpriteSheet(const sf::Color& primaryColor, const sf::Color& secondaryColor);

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    sf::Vector2u frameSize{32U, 32U};
    int frameCount{2};
    int currentFrame{0};
    float animationTimer{0.f};
    float frameDuration{0.22f};
};
