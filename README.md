# Vampire Survival

Vampire Survival is a small C++/SFML survival game. You control a vampire racing across a sunlight field to reach a tomb before wolves and sunlight kill you.

## Features

- Abstract `GameObject` base class with polymorphic `update` and `draw` methods.
- Abstract `Character` class shared by `Vampire` and `Wolf`.
- A single `std::vector<std::unique_ptr<GameObject>>` stores every object in the world.
- Random wolf and pickup spawning.
- Delta-time movement with `sf::Clock`.
- Keyboard vampire movement.
- Wolf chasing and attack behavior.
- Health, sun damage, tree hiding, pickups, dagger damage boosts, score, win and game-over states.
- Simple generated sprite-sheet animation for both Vampire and Wolf.

## Controls

| Key | Action |
| --- | --- |
| W | Move the vampire toward the tomb |
| A/S/D or Arrow Keys | Additional movement controls |
| Space | Attack nearby wolves |
| R | Restart after winning or losing |
| Escape | Quit |

## Build Requirements

- C++17 compiler
- CMake 3.16 or newer
- SFML 3.0 or newer development libraries

### Ubuntu/Debian SFML install

```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

### Build

```bash
cmake -S . -B build
cmake --build build
```

### Run

```bash
./build/VampireSurvival
```

You can pass the number of wolves as a command-line argument:

```bash
./build/VampireSurvival 12
```

## Complete File Structure

```text
VampireSurvival/
├── CMakeLists.txt
├── README.md
├── main.cpp
├── include/
│   ├── Character.h
│   ├── DaggerPickup.h
│   ├── Game.h
│   ├── GameObject.h
│   ├── HealthPickup.h
│   ├── Pickup.h
│   ├── Tomb.h
│   ├── Tree.h
│   ├── Vampire.h
│   └── Wolf.h
└── src/
    ├── Character.cpp
    ├── DaggerPickup.cpp
    ├── Game.cpp
    ├── HealthPickup.cpp
    ├── Pickup.cpp
    ├── Tomb.cpp
    ├── Tree.cpp
    ├── Vampire.cpp
    └── Wolf.cpp
```

## Game Goal

Reach the tomb before dying. Wolves move toward the vampire and attack on contact. The sun steadily damages the vampire unless you hide near trees. Collect health pickups to recover HP and dagger pickups to increase attack damage.
