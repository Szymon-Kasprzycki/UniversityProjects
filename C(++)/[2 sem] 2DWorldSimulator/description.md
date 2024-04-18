# 2D Virtual World Simulator

**Author:** Szymon Kasprzycki, _Gdańsk University of Technology_

## Project Overview

The main goal of this project is to implement a 2D virtual world simulator where simple life forms exist within a two-dimensional grid. The virtual world consists of organisms, including animals and plants, each with unique behaviors depending on their species. The simulator operates in turns, with organisms performing actions based on their characteristics and interactions with other organisms.

## Features

- **Grid Structure:** The virtual world is represented by a two-dimensional grid, with each cell capable of holding only one organism.
- **Organism Behavior:** Organisms perform actions during each turn, including movement, multiplication, and interactions with other organisms.
- **Collision Resolution:** In case of a collision between organisms, the outcome is determined based on factors such as strength, initiative, and species-specific behavior.
- **Human Player:** The simulation includes a human player as a specific type of animal, allowing player-controlled movement and special abilities activation.
- **Message Display:** The program interface includes a text box for displaying messages about events occurring within the simulated world.

## Implementation features

- **World Management:** Implement a class named "World" responsible for managing gameplay and organism life cycles, including methods for turn processing and world visualization.
- **Organism Hierarchy:** Define an abstract class named "Organism" as the base class for animals and plants, with common attributes and methods such as strength, initiative, position, and actions.
- **Animal Behavior:** Implement common behaviors for all animals in the "Animal" class, including default movement and multiplication.
- **Human Class:** Extend the "Animal" class to create the "Human" class, allowing player-controlled movement and special ability activation.
- **Species-Specific Classes:** Implement subclasses of animals and plants, each with unique characteristics and behaviors defined by strength, initiative, and actions.
- **World Interaction:** Implement mechanisms for organisms to affect the world state, such as spawning new organisms or modifying existing ones.
- **Visualization:** Visualize the virtual world in the console, representing each organism with a different ASCII symbol and updating the display at each turn.

## Project Structure

The project includes the following components:

- **World:** Manages the gameplay and life cycles of organisms.
- **Organism:** Abstract class serving as the base for animals and plants.
- **Animal:** Class implementing common behaviors for all animals.
- **Human:** Subclass of Animal representing the player-controlled character.
- **Species-Specific Classes:** Subclasses of animals and plants with unique behaviors.
- **Message Display:** Text box for displaying events and outcomes within the virtual world.

## Project grading

- **3 Points:** Implementation of world management, organism behavior, and human control.
- **4 Points:** Addition of breeding for animals, planting for plants, and implementation of human special ability.
- **5 Points:** Implementation of saving and loading game state functionality.
