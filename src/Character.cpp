#include "Character.h"
#include <algorithm>

namespace {
constexpr float WorldWidth = 1024.f;
constexpr float WorldHeight = 768.f;
}

Character::Character(const sf::Vector2f& startPosition,
                     int maxHealthValue,
                     int baseDamage,
                     float movementSpeed,
                     const sf::Color& primaryColor,
                     const sf::Color& secondaryColor)
    : position(startPosition),
      health(maxHealthValue),
      maxHealth(maxHealthValue),
      damage(baseDamage),
      speed(movementSpeed) {
    buildSpriteSheet(primaryColor, secondaryColor);
    sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
    sprite.setPosition(position);
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Character::getPosition() const {
    return position;
}

float Character::getCollisionRadius() const {
    return 18.f;
}

int Character::getHealth() const {
    return health;
}

int Character::getMaxHealth() const {
    return maxHealth;
}

int Character::getDamage() const {
    return damage;
}

bool Character::isAlive() const {
    return health > 0;
}

void Character::takeDamage(int amount) {
    health = std::max(0, health - amount);
    if (health == 0) {
        destroy();
    }
}

void Character::heal(int amount) {
    health = std::min(maxHealth, health + amount);
}

void Character::moveBy(const sf::Vector2f& velocity, float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.x = std::clamp(position.x, 20.f, WorldWidth - 20.f);
    position.y = std::clamp(position.y, 20.f, WorldHeight - 20.f);
    sprite.setPosition(position);
}

void Character::animate(float deltaTime) {
    animationTimer += deltaTime;
    if (animationTimer >= frameDuration) {
        animationTimer = 0.f;
        currentFrame = (currentFrame + 1) % frameCount;
        sprite.setTextureRect(sf::IntRect(currentFrame * static_cast<int>(frameSize.x),
                                          0,
                                          static_cast<int>(frameSize.x),
                                          static_cast<int>(frameSize.y)));
    }
}

void Character::addDamage(int amount) {
    damage += amount;
}

void Character::buildSpriteSheet(const sf::Color& primaryColor, const sf::Color& secondaryColor) {
    sf::Image sheet;
    sheet.create(frameSize.x * frameCount, frameSize.y, sf::Color::Transparent);

    for (int frame = 0; frame < frameCount; ++frame) {
        const sf::Color bodyColor = (frame == 0) ? primaryColor : secondaryColor;
        const unsigned int xOffset = frame * frameSize.x;

        for (unsigned int y = 6; y < 28; ++y) {
            for (unsigned int x = 9; x < 23; ++x) {
                sheet.setPixel(xOffset + x, y, bodyColor);
            }
        }

        for (unsigned int y = 2; y < 10; ++y) {
            for (unsigned int x = 11; x < 21; ++x) {
                sheet.setPixel(xOffset + x, y, sf::Color(235, 220, 210));
            }
        }

        const unsigned int footShift = (frame == 0) ? 0U : 2U;
        for (unsigned int y = 27; y < 31; ++y) {
            for (unsigned int x = 7 + footShift; x < 13 + footShift; ++x) {
                sheet.setPixel(xOffset + x, y, bodyColor);
            }
            for (unsigned int x = 19 - footShift; x < 25 - footShift; ++x) {
                sheet.setPixel(xOffset + x, y, bodyColor);
            }
        }
    }

    texture.loadFromImage(sheet);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(frameSize.x), static_cast<int>(frameSize.y)));
    sprite.setScale(1.6f, 1.6f);
}
