# Go Game Console Application in C++

**Author:** Szymon Kasprzycki, _Gdańsk University of Technology_

## Project Overview

The SpyHunter2D application is a C++ implementation of the Atari 2600 game Spy Hunter. Detailed information available on [Wikipedia](https://en.wikipedia.org/wiki/Spy_Hunter). Example gameplay on [Youtube](https://www.youtube.com/watch?v=GDVAgddcIyI).

Used sample project (template) provided by teacher, implementing:

- Time increment calculation.
- Graphics display in BMP format.
- Drawing pixels, lines, rectangles.
- Text display.

## Program Controls

- **Arrows:** Move player in given direction.
- **Esc:** Quit the program.
- **N:** Start a new game.
- **P:** Pause/Continue.
- **F:** Finish the game.

## Features Implemented

1. **Aesthetic Presentation:** Display game board with author's information in upper space.
2. **Elapsed Time and Score:** Display during gameplay; reset on new game.
3. **Basic Functionality:** Implement player movement and road form with collisions.
4. **Control Support:** Support esc and n controls.
5. **Scoring Mechanism:** Maintain score according to game mechanics.
6. **Road Width Change:** Implement dynamic road width.
7. **Pause Functionality (1 pt):** Allow pausing and continuing the game.

## Development Details

- Used "graphics" library SDL2 (2.0.7) included in the template
