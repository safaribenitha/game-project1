#include "Game.h"
#include <cstdlib>
#include <exception>
#include <iostream>

/**
 * Application entry point.
 *
 * Optional command-line argument: number of wolves to spawn.
 */
int main(int argc, char** argv) {
    unsigned int wolfCount = 8;
    if (argc > 1) {
        const int parsed = std::atoi(argv[1]);
        if (parsed > 0) {
            wolfCount = static_cast<unsigned int>(parsed);
        }
    }

    try {
        Game game(wolfCount);
        game.run();
    } catch (const std::exception& exception) {
        std::cerr << "Vampire Survival failed: " << exception.what() << '\n';
        return 1;
    }

    return 0;
}
