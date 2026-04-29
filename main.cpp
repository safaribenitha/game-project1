#include <iostream>
#include <string>
using namespace std;

class Character {
protected:
    string name;
    int health;
    int attackPower;

public:
    Character(string n, int h, int a)
        : name(n), health(h), attackPower(a) {}
    string getName() const {
        return name;
    }

    virtual void attack(Character& target) {
        cout << name << " attacks " << target.name
             << " for " << attackPower << " damage!\n";
        target.takeDamage(attackPower);
    }
     void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const {
        return health > 0;
    }

    virtual void displayStatus() const {
        cout << name << " | Health: " << health << "\n";
    }

    virtual ~Character() {}
};
class Player : public Character {
public:
    Player(string n) : Character(n, 100, 20) {}

    void attack(Character& target) override {
        cout << name << " uses a powerful strike on "
             << target.getName() << " for " << attackPower
             << " damage!\n";
        target.takeDamage(attackPower);
    }
};

class Enemy : public Character {
public:
    Enemy(string n, int h, int a)
        : Character(n, h, a) {}

    void attack(Character& target) override {
        cout << name << " claws at " << target.getName()
             << " for " << attackPower << " damage!\n";
        target.takeDamage(attackPower);
            }
};

int main() {
    Player player("Hero");
    Enemy enemy("Goblin", 60, 15);

    cout << "=== BATTLE START ===\n\n";

    while (player.isAlive() && enemy.isAlive()) {
        player.displayStatus();
        enemy.displayStatus();
        cout << "\nPress Enter to attack...";
        cin.get();

        player.attack(enemy);
  if (enemy.isAlive()) {
            enemy.attack(player);
        }

        cout << "\n---------------------\n\n";
    }

    if (player.isAlive()) {
        cout << "You won! The goblin has been defeated.\n";
    } else {
        cout << "Game Over! The goblin defeated you.\n";
    }

    return 0;
}