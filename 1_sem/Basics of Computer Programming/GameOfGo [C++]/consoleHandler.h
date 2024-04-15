#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

unsigned short askForBoardSize(short boardStartX, short boardsStartY);

void movePlayer(int input, unsigned short* x, unsigned short* y, short boardStartXPos, short boardStartYPos, unsigned short boardSize);

void renderGameWindow(char boardSide, unsigned short* xCoordinate, unsigned short* yCoordinate, unsigned short boardSize, const int* gameBoard, const float* scores, int turn, int key, int doubleKey, int firstTurn);

int askForHandicap(int* gameBoard, unsigned short boardSize);

int showGameMenu();

#endif //CONSOLEHANDLER_H
