# Go Game Console Application in C++

**Author:** Szymon Kasprzycki, _Gdańsk University of Technology_

## Project Overview

The Go Game Console Application is a C++ implementation of the traditional Go game, designed for two players. It adheres to the core rules of Go, including board sizes, stone placement, capturing, and scoring.

## Features Implemented

1. **Display:** The game board is displayed with a border, including a legend with player information, implemented functionalities list, and current scores.
2. **Cursor Movement:** Players can navigate using arrow keys, with the cursor constrained within the board boundaries. The current cursor position is displayed.
3. **New Game:** The "n" key resets the board and player stones, allowing for starting a new game.
4. **Stone Placement:** Stones can be placed using the "i" key, with prevention of suicidal placements and alternating turns between players.
5. **Simple Capturing:** Single stone captures are detected and player scores are updated accordingly.
6. **Save/Load Game:** Game state can be saved and loaded using the "s" and "l" keys.
7. **Ko Rule Enforcement:** Replication of previous board positions is prevented to avoid Ko fights.
8. **Board Size Selection:** Players can choose between standard and custom board sizes.
9. **Board Scrolling:** Scrolling is enabled for larger boards.
10. **Full Chain Capturing:** Captured stone chains of any size are detected and removed.
11. **Initial Stone Configuration:** Initial handicap stones can be set.
12. **Scoring and Komi:** The game ends with the "f" key, displaying the final score with Komi adjustment.

## Development Details

- Code is organized into functions and commented for clarity.
- Object-oriented programming principles are followed.
- Standard C library is utilized for file handling.
- Constants are used for easy parameter modification.
