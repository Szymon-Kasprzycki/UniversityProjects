#include "Constants.h"
#include "conio2.h"

const char CONSTANTS::BoardSide = 'R'; // 'R' -> board on right side, 'L' -> board on left side
const int CONSTANTS::PlayersAmount = 2;
const int CONSTANTS::BlackStone = 1; // number representing black on the game board
const int CONSTANTS::WhiteStone = 2; // number representing white on the game board
const int CONSTANTS::FreeSpace = 0; // number representing free point on the game board
const int CONSTANTS::LibertyMarker = 1; // number representing the chain liberty on the temporary array
const int CONSTANTS::OpponentMarker = 5; // number representing the opponent stone on the temporary array
const int CONSTANTS::PlayerMarker = 6; // number representing the player stone on the temporary array
const int CONSTANTS::PointCheckedMarker = 9; // number representing already checked stone on the game board (temporary marked)
const short CONSTANTS::cursorBackgroundColor = RED;
const short CONSTANTS::cursorTextColor = WHITE;
const char CONSTANTS::cursorSign = '*';