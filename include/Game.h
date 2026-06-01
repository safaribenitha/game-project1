#pragma once

#include "GameObject.h"
#include "Tomb.h"
#include "Vampire.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <string>
#include <vector>

/**
 * Supervises the full Vampire Survival application.
 *
 * Game owns the SFML window, clock, random number generator, HUD and the single
 * std::vector<std::unique_ptr<GameObject>> container holding every object.
 */
class Game {
public:
    /** Create a game with a configurable number of randomly placed wolves. */
    explicit Game(unsigned int wolfCount = 8);

    /** Main loop: process input, update simulation and render frames. */
    void run();

    /** Handle close/restart events and global keyboard input. */
    void processInput();

    /** Advance the simulation using sf::Clock deltaTime. */
    void update();

    /** Draw all objects and the HUD. */
    void render();

private:
    void createWorld(unsigned int wolfCount);
    void spawnRandomPickups(unsigned int healthCount, unsigned int daggerCount);
    sf::Vector2f randomPosition(float margin = 40.f);
    float distance(const sf::Vector2f& a, const sf::Vector2f& b) const;
    bool overlaps(const GameObject& a, const GameObject& b) const;
    void handleCollisions();
    void updateHud();
    bool loadHudFont();
    void reset(unsigned int wolfCount);
    void drawBackground();
    void drawHudPanel();

    static constexpr unsigned int WindowWidth = 1024;
    static constexpr unsigned int WindowHeight = 768;

    sf::RenderWindow window;
    sf::Clock clock;
    std::mt19937 randomEngine;

    std::vector<std::unique_ptr<GameObject>> objects;
    Vampire* vampire{nullptr};
    Tomb* tomb{nullptr};

    unsigned int configuredWolfCount;
    int score{0};
    bool won{false};
    bool gameOver{false};

    sf::Font font;
    bool fontLoaded{false};
    std::unique_ptr<sf::Text> hudText;
    std::unique_ptr<sf::Text> messageText;
};
