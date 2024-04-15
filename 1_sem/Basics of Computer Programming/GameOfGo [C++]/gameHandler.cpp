#include "gameHandler.h"
#include <stdlib.h>
#include <stdio.h>
#include "conio2.h"
#include "consoleHandler.h"
#include "fileHandler.h"
#include "constants.h"


void setupBoardPosition(short *boardStartX, short *boardStartY, char boardSide)
{
    switch (boardSide)
    {
        case 'R':
            *boardStartX = 60;
            *boardStartY = 2;
            break;
        case 'L':
            *boardStartX = 2;
            *boardStartY = 2;
            break;
        default:
            break;
    }
}


unsigned short getOnBoardXCoordinate(unsigned short x, short boardStartX)
{
    return (x - boardStartX - 1);
}


unsigned short getOnBoardYCoordinate(unsigned short y, short boardStartY)
{
    return (y - boardStartY - 1);
}


void increaseScore(int player, float *scores, float amount)
{
    if (player == CONSTANTS::BlackStone) scores[CONSTANTS::BlackStone-1] += amount;
    else if (player == CONSTANTS::WhiteStone) scores[CONSTANTS::WhiteStone-1] += amount;
}


void switchTurn(int *turn)
{
    if (*turn == CONSTANTS::WhiteStone) *turn = CONSTANTS::BlackStone;
    else *turn = CONSTANTS::WhiteStone;
}


int calculateOccurrences(const int *chainTemp, unsigned short boardSize, int color)
{
    int colored = 0;
    for (int i = 0; i < (boardSize * boardSize); i++)
    {
        if (chainTemp[i] == color) colored++;
    }
    return colored;
}


void resetChain(int *chainTemp, unsigned short boardSize)
{
    for (int i = 0; i < (boardSize * boardSize); i++) chainTemp[i] = 0;
}


// Recursively mark empty space surrounded by color
void markRoundedByColor(int *gameBoard, int *chainTemp, short x, short y, unsigned short boardSize, int color)
{
    if (x < 0 || y < 0 || x > (boardSize - 1) || y > (boardSize - 1)) return;

    int relativeCoord = y * boardSize + x;

    // if point is free and is not marked = mark it
    if (gameBoard[relativeCoord] == CONSTANTS::FreeSpace && chainTemp[relativeCoord] == 0)
    {
        chainTemp[relativeCoord] = CONSTANTS::LibertyMarker;
        // Check every neighbour of this point
        markRoundedByColor(gameBoard, chainTemp, x + 1, y, boardSize, color);
        markRoundedByColor(gameBoard, chainTemp, x - 1, y, boardSize, color);
        markRoundedByColor(gameBoard, chainTemp, x, y + 1, boardSize, color);
        markRoundedByColor(gameBoard, chainTemp, x, y - 1, boardSize, color);
    }

    if (gameBoard[relativeCoord] == (3 - color) && chainTemp[relativeCoord] == 0)
    {
        chainTemp[relativeCoord] = CONSTANTS::OpponentMarker;
    }

    if (gameBoard[relativeCoord] == color && chainTemp[relativeCoord] == 0)
    {
        chainTemp[relativeCoord] = CONSTANTS::PlayerMarker;
    }
}


void calculatePoints(int *gameBoard, unsigned short boardSize, float *scores, int *chainTemp, int color)
{
    for (short i = 0; i < boardSize; i++)
    {
        for (short j = 0; j < boardSize; j++)
        {
            if (gameBoard[i * boardSize + j] == CONSTANTS::FreeSpace)
            {
                markRoundedByColor(gameBoard, chainTemp, j, i, boardSize, color);

                for (int k = 0; k < (boardSize * boardSize); k++)
                {
                    if (chainTemp[k] == 1) gameBoard[k] = CONSTANTS::PointCheckedMarker;
                }

                int colorAmount = calculateOccurrences(chainTemp, boardSize, CONSTANTS::PlayerMarker);
                int secondColorAmount = calculateOccurrences(chainTemp, boardSize, CONSTANTS::OpponentMarker);

                if (!secondColorAmount && colorAmount != 1)
                {
                    int chainLength = calculateOccurrences(chainTemp, boardSize, CONSTANTS::LibertyMarker);
                    scores[color - 1] += (float) chainLength;
                }

                resetChain(chainTemp, boardSize);
            }
        }
    }
    for (int i = 0; i < (boardSize * boardSize); i++)
    {
        if (gameBoard[i] == CONSTANTS::PointCheckedMarker) gameBoard[i] = 0;
    }
}


void markLiberties(int *gameBoard, int *chainTemp, short x, short y, unsigned short boardSize, int color)
{
    if (x < 0 || y < 0 || x > (boardSize - 1) || y > (boardSize - 1)) return;

    int coord = y * boardSize + x;
    if (gameBoard[coord] == (3 - color)) return;

    if (gameBoard[coord] == color && chainTemp[coord] == 0)
    {
        chainTemp[coord] = CONSTANTS::OpponentMarker; // added (1)
        markLiberties(gameBoard, chainTemp, x + 1, y, boardSize, color);
        markLiberties(gameBoard, chainTemp, x - 1, y, boardSize, color);
        markLiberties(gameBoard, chainTemp, x, y + 1, boardSize, color);
        markLiberties(gameBoard, chainTemp, x, y - 1, boardSize, color);
    }
    // if point is free mark as liberty
    else if (gameBoard[coord] == CONSTANTS::FreeSpace) // added (0)
    {
        chainTemp[coord] = CONSTANTS::LibertyMarker; // added (2)
    }
}


void killStones(int *gameBoard, int const *chainTemp, unsigned short boardSize, int color, float *scores)
{
    float points = 0;
    for (int i = 0; i < (boardSize * boardSize); i++)
    {
        if (chainTemp[i] == CONSTANTS::OpponentMarker)
        {
            points++;
            gameBoard[i] = CONSTANTS::FreeSpace;
        }
    }
    increaseScore((3-color), scores, points);
}


void checkStones(int *gameBoard, unsigned short boardSize, float *scores, int *chainTemp, int color)
{
    for (short i = 0; i < boardSize; i++)
    {
        for (short j = 0; j < boardSize; j++)
        {
            if (gameBoard[i * boardSize + j] == color)
            {
                // Recursive mark liberties
                markLiberties(gameBoard, chainTemp, j, i, boardSize, color);
                // Check liberties amount and kill whole chain if it has no liberties
                int libertiesAmount = calculateOccurrences(chainTemp, boardSize, CONSTANTS::LibertyMarker);
                if (libertiesAmount == 0)
                {
                    killStones(gameBoard, chainTemp, boardSize, color, scores);
                }
                // Reset chain variable to zeros
                resetChain(chainTemp, boardSize);
            }
        }

    }
}


void setLastBoardState(int *lastBoardState, const int *gameBoard, int boardSize)
{
    for (int i = 0; i < (boardSize * boardSize); i++)
    {
        lastBoardState[i] = gameBoard[i];
    }
}


int checkKO(const int *lastBoardState, const int *gameBoard, int boardSize)
{
    int KO = 1;
    for (int i = 0; i < (boardSize * boardSize); i++)
    {
        if (lastBoardState[i] != gameBoard[i]) KO = 0;
    }
    return (!KO);
}


int stonePlacePossible(const int *gameBoard, unsigned short x, unsigned short y, unsigned short boardSize, int turn, int *lastBoardState)
{
    int coord = y*boardSize + x;
    if (gameBoard[coord] == 0)
    {
        // Make a copy of gameBoard to simulate move
        int *copyGameBoard;
        copyGameBoard = (int *) calloc(boardSize * boardSize, sizeof(int));
        for (int i = 0; i < (boardSize * boardSize); i++) copyGameBoard[i] = gameBoard[i];
        copyGameBoard[coord] = turn;

        // Allocate memory for analyse after move
        int *temp;
        temp = (int *) calloc(boardSize * boardSize, sizeof(int));
        markLiberties(copyGameBoard, temp, x, y, boardSize, turn);
        int liberties = calculateOccurrences(temp, boardSize, CONSTANTS::LibertyMarker);
        resetChain(temp, boardSize);

        // check the KO rule
        float scores[2];
        int secondColor = 3 - turn;
        checkStones(copyGameBoard, boardSize, scores, temp, secondColor);
        int isNotKo = checkKO(lastBoardState, copyGameBoard, boardSize);

        // check if there is any capture after this move (if there were more opponent stones before this move)
        int opponentStonesBeforeMove = calculateOccurrences(gameBoard, boardSize, secondColor);
        int opponentStonesAfterMove = calculateOccurrences(copyGameBoard, boardSize, secondColor);
        int capturingMove = opponentStonesBeforeMove - opponentStonesAfterMove;

        // deallocate memory
        free(temp);
        free(copyGameBoard);

        return ((liberties != 0 || capturingMove) && isNotKo);
    }
    else return 0;
}


void placeStone(unsigned short xCoord, unsigned short yCoord, unsigned short const boardSize, short boardStartX, short boardStartY, int *gameBoard, int *turn, float *scores, int *lastBoardState)
{
    // Get one-dimensional board identifier of the place
    unsigned short relativeY = getOnBoardYCoordinate(yCoord, boardStartY);
    unsigned short relativeX = getOnBoardXCoordinate(xCoord, boardStartX);
    int coord = relativeY * boardSize + relativeX;

    if (stonePlacePossible(gameBoard, relativeX, relativeY, boardSize, *turn, lastBoardState))
    {
        setLastBoardState(lastBoardState, gameBoard, boardSize);

        gameBoard[coord] = *turn;

        // Wait for confirmation
        int key;
        do { key = getch(); } while (key != 0x0d && key != 0x1b);

        // Move cancelling
        if (key == 0x1b)
        {
            gameBoard[coord] = 0;
            return;
        }

        switchTurn(turn);

        // Handle captures
        int *chainTemp;
        chainTemp = (int *) calloc((boardSize * boardSize), sizeof(int));
        checkStones(gameBoard, boardSize, scores, chainTemp, *turn);
        free(chainTemp);
    }
}


void resetBoard(int **board, unsigned short boardSize)
{
    free(*board);
    *board = (int *) calloc(boardSize * boardSize, sizeof(int));
}


void resetScores(float *scores)
{
    for (int i = 0; i < CONSTANTS::PlayersAmount; i++) scores[i] = 0;
}


void resetGame(int **gameBoard, int **lastBoardState, float *scores, unsigned short *boardSize, int *firstTurn, int *handicapUsed, short boardStartX, short boardStartY)
{
    *boardSize = askForBoardSize(boardStartX, boardStartY);
    resetBoard(gameBoard, *boardSize);
    resetBoard(lastBoardState, *boardSize);
    resetScores(scores);
    *firstTurn = 1;
    *handicapUsed = askForHandicap(*gameBoard, *boardSize);
}


void finishGame(int *gameBoard, float *scores, unsigned short boardSize, const int *handicapUsed)
{
    clrscr();
    int column = 2, row = 1;
    gotoxy(column, row);
    cputs("GAME ENDED!");

    // territory points
    int *tempChain;
    tempChain = (int *) calloc(boardSize * boardSize, sizeof(int));
    calculatePoints(gameBoard, boardSize, scores, tempChain, CONSTANTS::BlackStone);
    calculatePoints(gameBoard, boardSize, scores, tempChain, CONSTANTS::WhiteStone);
    free(tempChain);

    // komi points
    if (*handicapUsed) increaseScore(CONSTANTS::WhiteStone, scores, 6.5);
    else increaseScore(CONSTANTS::WhiteStone, scores, 0.5);

    char txt[35];
    row += 3;
    for (int i = 0; i < CONSTANTS::PlayersAmount; i++)
    {
        gotoxy(column, row + i);
        if (i == CONSTANTS::BlackStone-1) sprintf(txt, "BLACK SCORE: %g", scores[i]);
        else if (i == CONSTANTS::WhiteStone-1) sprintf(txt, "WHITE SCORE: %g", scores[i]);
        cputs(txt);
    }
    row += 6;
    gotoxy(column, row);
    cputs("Press any key to exit...");
    getche();
}


void processGame(int **gameBoard, int **lastBoardState, float *scores, int *userInput, int *firstInputCharZero, unsigned short *xCoord, unsigned short *yCoord, unsigned short *boardSize, short boardStartX, short boardStartY, int *turn, int *firstTurn, int *useHandicap, int *continueGame)
{
    if (*firstTurn) *firstTurn = 0;
    switch (*userInput)
    {
        case 0:
            *firstInputCharZero = 1;
            *userInput = getch();
            movePlayer(*userInput, xCoord, yCoord, boardStartX, boardStartY, *boardSize);
            break;
        case 'i':
            placeStone(*xCoord, *yCoord, *boardSize, boardStartX, boardStartY, *gameBoard, turn, scores,*lastBoardState);
            break;
        case 'n':
            resetGame(gameBoard, lastBoardState, scores, boardSize, firstTurn, useHandicap, boardStartX, boardStartY);
            break;
        case 's':
            writeDataToFile(*gameBoard, *lastBoardState, scores, *boardSize, *turn, *xCoord, *yCoord, *useHandicap,*firstTurn, boardStartX, boardStartY);
            break;
        case 'l':
            int initialiseBoard;
            initialiseBoard = 0;
            readDataFromFile(gameBoard, lastBoardState, scores, boardSize, turn, xCoord, yCoord, useHandicap, firstTurn,initialiseBoard, boardStartX, boardStartY);
            break;
        case 'f':
            finishGame(*gameBoard, scores, *boardSize, useHandicap);
            *continueGame = 0;
            break;
        case 'q':
            *continueGame = 0;
            break;
    }
}