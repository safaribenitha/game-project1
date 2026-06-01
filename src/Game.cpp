#include "Game.h"
#include "DaggerPickup.h"
#include "HealthPickup.h"
#include "Pickup.h"
#include "Tree.h"
#include "Wolf.h"
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <cmath>
#include <optional>
#include <sstream>

Game::Game(unsigned int wolfCount)
    : window(sf::VideoMode(sf::Vector2u(WindowWidth, WindowHeight)), "Vampire Survival"),
      randomEngine(std::random_device{}()),
      configuredWolfCount(wolfCount) {
    window.setFramerateLimit(60);
    fontLoaded = loadHudFont();
    if (fontLoaded) {
        hudText = std::make_unique<sf::Text>(font);
        hudText->setCharacterSize(20);
        hudText->setFillColor(sf::Color::White);
        hudText->setPosition(sf::Vector2f(12.f, 8.f));

        messageText = std::make_unique<sf::Text>(font);
        messageText->setCharacterSize(38);
        messageText->setFillColor(sf::Color(255, 230, 150));
        messageText->setPosition(sf::Vector2f(190.f, 345.f));

        legendText = std::make_unique<sf::Text>(font);
        legendText->setCharacterSize(17);
        legendText->setFillColor(sf::Color(242, 240, 222));
        legendText->setPosition(sf::Vector2f(18.f, 58.f));
        legendText->setString(
            "W = move toward tomb\n"
            "A/S/D = optional steering\n"
            "R = restart\n"
            "Grey wolves chase you\n"
            "Green cross heals\n"
            "Dagger increases damage\n"
            "Reach the tomb to win");
    }
    createWorld(wolfCount);
}

void Game::run() {
    while (window.isOpen()) {
        processInput();
        update();
        render();
    }
}

void Game::processInput() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
            if (keyPressed->code == sf::Keyboard::Key::R) {
                reset(configuredWolfCount);
            }
        }
    }
}

void Game::update() {
    const float deltaTime = clock.restart().asSeconds();
    if (won || gameOver) {
        updateHud();
        return;
    }

    for (const auto& object : objects) {
        object->update(deltaTime);
    }

    if (vampire != nullptr) {
        bool hidden = false;
        for (const auto& object : objects) {
            if (auto* tree = dynamic_cast<Tree*>(object.get())) {
                if (distance(vampire->getPosition(), tree->getPosition()) < tree->getCollisionRadius()) {
                    hidden = true;
                    break;
                }
            }
        }
        vampire->setHidden(hidden);
        vampire->applySunDamage(deltaTime);
    }

    handleCollisions();

    if (vampire == nullptr || !vampire->isAlive()) {
        gameOver = true;
    }

    objects.erase(std::remove_if(objects.begin(), objects.end(),
                                 [this](const std::unique_ptr<GameObject>& object) {
                                     return object.get() != vampire && !object->isActive();
                                 }),
                  objects.end());

    updateHud();
}

void Game::render() {
    drawBackground();

    std::vector<GameObject*> drawOrder;
    drawOrder.reserve(objects.size());
    for (const auto& object : objects) {
        drawOrder.push_back(object.get());
    }
    std::sort(drawOrder.begin(), drawOrder.end(), [](const GameObject* left, const GameObject* right) {
        return left->getPosition().y < right->getPosition().y;
    });

    for (GameObject* object : drawOrder) {
        object->draw(window);
    }
    if (fontLoaded) {
        drawHudPanel();
        window.draw(*hudText);
        drawLegend();
        if (won) {
            messageText->setString("You reached the tomb! Press R to restart.");
            window.draw(*messageText);
        } else if (gameOver) {
            messageText->setString("Game Over! Press R to restart.");
            window.draw(*messageText);
        }
    }
    window.display();
}

void Game::drawLegend() {
    sf::RectangleShape panel(sf::Vector2f(244.f, 158.f));
    panel.setPosition(sf::Vector2f(12.f, 52.f));
    panel.setFillColor(sf::Color(12, 13, 18, 178));
    panel.setOutlineColor(sf::Color(230, 205, 132, 105));
    panel.setOutlineThickness(1.f);
    window.draw(panel);
    window.draw(*legendText);
}

void Game::drawBackground() {
    window.clear(sf::Color(22, 22, 34));

    sf::RectangleShape grass(sf::Vector2f(static_cast<float>(WindowWidth), static_cast<float>(WindowHeight)));
    grass.setFillColor(sf::Color(42, 68, 52));
    window.draw(grass);

    sf::RectangleShape sunWash(sf::Vector2f(static_cast<float>(WindowWidth), static_cast<float>(WindowHeight)));
    sunWash.setFillColor(sf::Color(135, 125, 95, 34));
    window.draw(sunWash);

    const sf::Vector2f sunPosition(900.f, 96.f);
    for (unsigned int i = 0; i < 12; ++i) {
        const float angle = static_cast<float>(i) * 30.f;
        const float radians = angle * 3.14159265f / 180.f;
        sf::RectangleShape ray(sf::Vector2f(12.f, 42.f));
        ray.setOrigin(sf::Vector2f(6.f, 56.f));
        ray.setPosition(sunPosition + sf::Vector2f(std::cos(radians) * 8.f, std::sin(radians) * 8.f));
        ray.setRotation(sf::degrees(angle));
        ray.setFillColor(sf::Color(255, 174, 50, 150));
        window.draw(ray);
    }

    sf::CircleShape sunGlow(74.f);
    sunGlow.setOrigin(sf::Vector2f(74.f, 74.f));
    sunGlow.setPosition(sunPosition);
    sunGlow.setFillColor(sf::Color(255, 176, 45, 72));
    window.draw(sunGlow);

    sf::CircleShape sunCore(43.f);
    sunCore.setOrigin(sf::Vector2f(43.f, 43.f));
    sunCore.setPosition(sunPosition);
    sunCore.setFillColor(sf::Color(255, 219, 74, 235));
    sunCore.setOutlineColor(sf::Color(236, 120, 32, 210));
    sunCore.setOutlineThickness(4.f);
    window.draw(sunCore);

    sf::RectangleShape path(sf::Vector2f(1180.f, 118.f));
    path.setOrigin(sf::Vector2f(590.f, 59.f));
    path.setPosition(sf::Vector2f(555.f, 474.f));
    path.setRotation(sf::degrees(-18.f));
    path.setFillColor(sf::Color(91, 82, 65, 165));
    window.draw(path);

    for (unsigned int x = 24; x < WindowWidth; x += 64) {
        for (unsigned int y = 70; y < WindowHeight; y += 58) {
            sf::CircleShape tuft(3.f + static_cast<float>((x + y) % 4));
            tuft.setOrigin(sf::Vector2f(tuft.getRadius(), tuft.getRadius()));
            tuft.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
            tuft.setFillColor(sf::Color(63, 91, 58, 150));
            window.draw(tuft);
        }
    }

    for (unsigned int i = 0; i < 8; ++i) {
        sf::CircleShape stone(10.f + static_cast<float>(i % 3) * 3.f);
        stone.setOrigin(sf::Vector2f(stone.getRadius(), stone.getRadius()));
        stone.setScale(sf::Vector2f(1.35f, 0.55f));
        stone.setPosition(sf::Vector2f(90.f + i * 118.f, 700.f - static_cast<float>((i * 47) % 360)));
        stone.setFillColor(sf::Color(69, 73, 70, 120));
        window.draw(stone);
    }
}

void Game::drawHudPanel() {
    sf::RectangleShape panel(sf::Vector2f(1000.f, 38.f));
    panel.setPosition(sf::Vector2f(12.f, 8.f));
    panel.setFillColor(sf::Color(12, 13, 18, 178));
    panel.setOutlineColor(sf::Color(230, 205, 132, 135));
    panel.setOutlineThickness(1.f);
    window.draw(panel);
}

void Game::createWorld(unsigned int wolfCount) {
    objects.clear();
    score = 0;
    won = false;
    gameOver = false;

    auto vampireObject = std::make_unique<Vampire>(sf::Vector2f(90.f, WindowHeight * 0.5f));
    vampire = vampireObject.get();
    objects.push_back(std::move(vampireObject));

    auto tombObject = std::make_unique<Tomb>(sf::Vector2f(WindowWidth - 110.f, WindowHeight - 95.f));
    tomb = tombObject.get();
    objects.push_back(std::move(tombObject));
    vampire->setAutoMoveTarget(tomb->getPosition());

    const sf::Vector2f treePositions[] = {
        {210.f, 330.f}, {360.f, 210.f}, {445.f, 510.f}, {620.f, 235.f}, {760.f, 430.f}, {560.f, 650.f}
    };
    for (const auto& position : treePositions) {
        objects.push_back(std::make_unique<Tree>(position));
    }

    for (unsigned int i = 0; i < wolfCount; ++i) {
        objects.push_back(std::make_unique<Wolf>(randomPosition(140.f), vampire));
    }

    spawnRandomPickups(5, 3);
    updateHud();
}

void Game::spawnRandomPickups(unsigned int healthCount, unsigned int daggerCount) {
    for (unsigned int i = 0; i < healthCount; ++i) {
        objects.push_back(std::make_unique<HealthPickup>(randomPosition(60.f)));
    }
    for (unsigned int i = 0; i < daggerCount; ++i) {
        objects.push_back(std::make_unique<DaggerPickup>(randomPosition(60.f)));
    }
}

sf::Vector2f Game::randomPosition(float margin) {
    std::uniform_real_distribution<float> xDistribution(margin, WindowWidth - margin);
    std::uniform_real_distribution<float> yDistribution(margin, WindowHeight - margin);
    return sf::Vector2f(xDistribution(randomEngine), yDistribution(randomEngine));
}

float Game::distance(const sf::Vector2f& a, const sf::Vector2f& b) const {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Game::overlaps(const GameObject& a, const GameObject& b) const {
    return distance(a.getPosition(), b.getPosition()) <= a.getCollisionRadius() + b.getCollisionRadius();
}

void Game::handleCollisions() {
    if (vampire == nullptr || tomb == nullptr) {
        return;
    }

    for (const auto& object : objects) {
        if (auto* wolf = dynamic_cast<Wolf*>(object.get())) {
            if (wolf->isAlive() && overlaps(*vampire, *wolf)) {
                wolf->attack(*vampire);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    wolf->takeDamage(vampire->getDamage());
                    if (!wolf->isAlive()) {
                        score += 100;
                    }
                }
            }
        } else if (auto* pickup = dynamic_cast<Pickup*>(object.get())) {
            if (pickup->isActive() && overlaps(*vampire, *pickup)) {
                pickup->apply(*vampire);
                score += 25;
            }
        }
    }

    if (overlaps(*vampire, *tomb)) {
        won = true;
        score += 500;
    }
}

void Game::updateHud() {
    if (vampire == nullptr || tomb == nullptr) {
        return;
    }

    const int hp = vampire->getHealth();
    const int maxHp = vampire->getMaxHealth();
    const float tombDistance = distance(vampire->getPosition(), tomb->getPosition());

    std::ostringstream stream;
    stream << "HP: " << hp << "/" << maxHp
           << "   Score: " << score
           << "   Tomb: " << static_cast<int>(tombDistance) << " px"
           << "   Damage: " << vampire->getDamage()
           << (vampire->isHidden() ? "   Hidden from sun" : "   In sunlight");

    if (fontLoaded) {
        hudText->setString(stream.str());
    }
    window.setTitle("Vampire Survival - " + stream.str());
}

bool Game::loadHudFont() {
    const std::string paths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    for (const auto& path : paths) {
        if (font.openFromFile(path)) {
            return true;
        }
    }
    return false;
}

void Game::reset(unsigned int wolfCount) {
    vampire = nullptr;
    tomb = nullptr;
    createWorld(wolfCount);
    clock.restart();
}
