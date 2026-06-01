#pragma once

#include <SFML/Graphics.hpp>

/**
 * Base abstract interface for every entity in Vampire Survival.
 *
 * The Game class stores every concrete object through std::unique_ptr<GameObject>
 * in one shared container and uses these virtual methods for polymorphic updates
 * and rendering.
 */
class GameObject {
public:
    /** Virtual destructor allows safe deletion through base-class pointers. */
    virtual ~GameObject() = default;

    /** Advance this object by deltaTime seconds. */
    virtual void update(float deltaTime) = 0;

    /** Draw this object into the SFML render window. */
    virtual void draw(sf::RenderWindow& window) = 0;

    /** World-space position used for collision checks and distance displays. */
    virtual sf::Vector2f getPosition() const = 0;

    /** Circular collision radius used by the simple collision system. */
    virtual float getCollisionRadius() const = 0;

    /** Whether the object should remain in the master game-object container. */
    virtual bool isActive() const { return active; }

    /** Mark an object for removal from the master game-object container. */
    virtual void destroy() { active = false; }

protected:
    bool active{true};
};
