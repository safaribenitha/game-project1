#include "Character.h"
#include <algorithm>
#include <stdexcept>

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
    if (sprite) {
        sprite->setOrigin(sf::Vector2f(frameSize.x / 2.f, frameSize.y / 2.f));
        sprite->setPosition(position);
    }
}

void Character::draw(sf::RenderWindow& window) {
    sf::CircleShape shadow(17.f);
    shadow.setOrigin(sf::Vector2f(17.f, 17.f));
    shadow.setScale(sf::Vector2f(1.35f, 0.42f));
    shadow.setPosition(sf::Vector2f(position.x, position.y + 18.f));
    shadow.setFillColor(sf::Color(0, 0, 0, 85));
    window.draw(shadow);

    if (sprite) {
        window.draw(*sprite);
    }
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
    if (sprite) {
        sprite->setPosition(position);
    }
}

void Character::animate(float deltaTime) {
    animationTimer += deltaTime;
    if (animationTimer >= frameDuration) {
        animationTimer = 0.f;
        currentFrame = (currentFrame + 1) % frameCount;
        if (sprite) {
            sprite->setTextureRect(sf::IntRect({currentFrame * static_cast<int>(frameSize.x), 0},
                                               {static_cast<int>(frameSize.x), static_cast<int>(frameSize.y)}));
        }
    }
}

void Character::addDamage(int amount) {
    damage += amount;
}

void Character::buildSpriteSheet(const sf::Color& primaryColor, const sf::Color& secondaryColor) {
    sf::Image sheet(sf::Vector2u(frameSize.x * static_cast<unsigned int>(frameCount), frameSize.y),
                    sf::Color::Transparent);
    const bool vampireLike = primaryColor.b > primaryColor.r;

    for (int frame = 0; frame < frameCount; ++frame) {
        const sf::Color bodyColor = (frame == 0) ? primaryColor : secondaryColor;
        const unsigned int xOffset = frame * frameSize.x;
        const unsigned int bob = (frame == 0) ? 0U : 1U;
        const sf::Color outline(24, 20, 26, 230);
        const sf::Color highlight(std::min(255, bodyColor.r + 42),
                                  std::min(255, bodyColor.g + 42),
                                  std::min(255, bodyColor.b + 42));

        for (unsigned int y = 5 + bob; y < 29 + bob; ++y) {
            for (unsigned int x = 8; x < 24; ++x) {
                if (x == 8 || x == 23 || y == 5 + bob || y == 28 + bob) {
                    sheet.setPixel(sf::Vector2u(xOffset + x, y), outline);
                } else {
                    sheet.setPixel(sf::Vector2u(xOffset + x, y), bodyColor);
                }
            }
        }

        for (unsigned int y = 8 + bob; y < 23 + bob; ++y) {
            for (unsigned int x = 10; x < 14; ++x) {
                sheet.setPixel(sf::Vector2u(xOffset + x, y), highlight);
            }
        }

        if (vampireLike) {
            for (unsigned int y = 8 + bob; y < 29 + bob; ++y) {
                sheet.setPixel(sf::Vector2u(xOffset + 7, y), sf::Color(45, 7, 54));
                sheet.setPixel(sf::Vector2u(xOffset + 24, y), sf::Color(45, 7, 54));
            }
            for (unsigned int x = 10; x < 22; ++x) {
                sheet.setPixel(sf::Vector2u(xOffset + x, 12 + bob), sf::Color(235, 235, 226));
            }
        } else {
            for (unsigned int y = 7 + bob; y < 15 + bob; ++y) {
                sheet.setPixel(sf::Vector2u(xOffset + 6, y), bodyColor);
                sheet.setPixel(sf::Vector2u(xOffset + 25, y), bodyColor);
            }
            for (unsigned int y = 16 + bob; y < 21 + bob; ++y) {
                for (unsigned int x = 21; x < 28; ++x) {
                    sheet.setPixel(sf::Vector2u(xOffset + x, y), sf::Color(75, 75, 80));
                }
            }
        }

        for (unsigned int y = 2 + bob; y < 11 + bob; ++y) {
            for (unsigned int x = 11; x < 21; ++x) {
                sheet.setPixel(sf::Vector2u(xOffset + x, y), sf::Color(229, 214, 202));
            }
        }

        sheet.setPixel(sf::Vector2u(xOffset + 13, 6 + bob), vampireLike ? sf::Color(210, 24, 45) : sf::Color(245, 210, 80));
        sheet.setPixel(sf::Vector2u(xOffset + 19, 6 + bob), vampireLike ? sf::Color(210, 24, 45) : sf::Color(245, 210, 80));
        sheet.setPixel(sf::Vector2u(xOffset + 15, 10 + bob), outline);
        sheet.setPixel(sf::Vector2u(xOffset + 16, 10 + bob), outline);

        if (vampireLike) {
            sheet.setPixel(sf::Vector2u(xOffset + 14, 11 + bob), sf::Color::White);
            sheet.setPixel(sf::Vector2u(xOffset + 18, 11 + bob), sf::Color::White);
        }

        const unsigned int footShift = (frame == 0) ? 0U : 2U;
        for (unsigned int y = 27; y < 31; ++y) {
            for (unsigned int x = 7 + footShift; x < 13 + footShift; ++x) {
                sheet.setPixel(sf::Vector2u(xOffset + x, y), bodyColor);
            }
            for (unsigned int x = 19 - footShift; x < 25 - footShift; ++x) {
                sheet.setPixel(sf::Vector2u(xOffset + x, y), bodyColor);
            }
        }
    }

    if (!texture.loadFromImage(sheet)) {
        throw std::runtime_error("Failed to create character sprite texture.");
    }
    sprite.emplace(texture);
    sprite->setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(frameSize.x), static_cast<int>(frameSize.y)}));
    sprite->setScale(sf::Vector2f(1.6f, 1.6f));
}
