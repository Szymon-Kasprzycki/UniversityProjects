#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "conio2.h"
#include "consoleHandler.h"
#include "fileHandler.h"
#include "gameHandler.h"
#include "constants.h"

#ifndef __cplusplus
Conio2_Init();
#endif

// Implemented points from requirements: a, b, c, d, e, f, g, h, j, k, l


int main()
{
    // VARIABLES
    int firstTurn = 1;
    int keyboardInput = 0;
    int firstCharZero = 0;
    int turn; // TURN 1 -- black, TURN 2 -- white
    short boardStartX, boardStartY;
    unsigned short x, y;
    unsigned short boardSize;
    float scores[2] = {0, 0}; // black, white
    int handicapUsed = 0;
    int continueGame = 1;
    int menuOption;
    int *gameBoard; // dynamic array
    int *lastBoardState; // dynamic array

    // POINTERS
    int *firstTurnPtr = &firstTurn;
    int *keyboardInputPtr = &keyboardInput;
    int *firstCharZeroPtr = &firstCharZero;
    int *turnPtr = &turn;
    short *boardStartXPtr = &boardStartX, *BoardStartYPtr = &boardStartY;
    unsigned short *xPtr = &x, *yPtr = &y;
    unsigned short *boardSizePtr = &boardSize;
    int *useHandicapPtr = &handicapUsed;
    int *continueGamePtr = &continueGame;
    int **gameBoardPtr = &gameBoard;
    int **lastBoardStatePtr = &lastBoardState;

    _setcursortype(_NOCURSOR);
    settitle("Szymon Kasprzycki, 193065");

    setupBoardPosition(boardStartXPtr, BoardStartYPtr, CONSTANTS::BoardSide);

    menuOption = showGameMenu();
    if (menuOption == 1) // start a new game
    {
        boardSize = askForBoardSize(boardStartX, boardStartY);
        gameBoard = (int *) calloc((boardSize * boardSize), sizeof(int));
        lastBoardState = (int *) calloc(boardSize * boardSize, sizeof(int));
        handicapUsed = askForHandicap(gameBoard, boardSize);
    }
    else if (menuOption == 2) // load a game from file
    {
        int initializingGame = 1;
        readDataFromFile(gameBoardPtr, lastBoardStatePtr, scores, boardSizePtr, turnPtr, xPtr, yPtr, useHandicapPtr, firstTurnPtr, initializingGame, boardStartX, boardStartY);
    }
    else continueGame = 0; // quit

    if (continueGame) // main loop of the game
    {
        do {
            if (handicapUsed && firstTurn) turn = CONSTANTS::WhiteStone;
            else if (firstTurn) turn = CONSTANTS::BlackStone;

            renderGameWindow(CONSTANTS::BoardSide, xPtr, yPtr, *boardSizePtr, gameBoard, scores, turn, keyboardInput, firstCharZero, firstTurn);

            firstCharZero = 0;
            keyboardInput = getch();

            processGame(gameBoardPtr, lastBoardStatePtr, scores, keyboardInputPtr, firstCharZeroPtr, xPtr, yPtr, boardSizePtr, boardStartX, boardStartY, turnPtr, firstTurnPtr, useHandicapPtr, continueGamePtr);
        } while (continueGame);
    }

    // deallocate memory
    free(gameBoard);
    free(lastBoardState);
    // Reset the cursor
    clrscr();
    _setcursortype(_NORMALCURSOR);
    return 0;
}