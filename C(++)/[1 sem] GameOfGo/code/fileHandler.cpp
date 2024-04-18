#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "fileHandler.h"
#include "constants.h"

// Max windows path length
#define MaxFilenameLength 256


void getFilename(char *filename)
{
    int column = 1, row = 1;

    clrscr();
    _setcursortype(_NORMALCURSOR);

    gotoxy(column, row);
    cputs("Please input file name: ");
    for (int i = 0; i < MaxFilenameLength; i++)
    {
        int character = getch();
        // if not backspace pressed
        if (character != '\b')
        {
            putch(character);
            filename[i] = (char) character;
            // enter was pressed
            if (character == '\r' || character == '\n')
            {
                filename[i] = '\0';
                break;
            }
        }
        else
        {
            // remove previous character
            putch(character);
            putch(' ');
            putch(character);
            // reset previous character in array
            --i;
            filename[i] = '\0';
            // reset iterator
            --i;
        }
    }
    _setcursortype(_NOCURSOR);
}


void writeDataToFile(int *gameBoard, int *preventKOBoardState, float *scores, unsigned short boardSize, int turn, unsigned short xCoord, unsigned short yCoord, int handicapUsed, int firstTurn, unsigned short boardStartX, unsigned short boardStartY)
{
    char filename[MaxFilenameLength];
    getFilename(filename);

    FILE *filePtr;
    filePtr = fopen(filename, "w+");

    if(filePtr == NULL)
    {
        clrscr();
        cputs("Cannot create file! Press any key to continue...");
        getch();
        return;
    }

    fprintf(filePtr, "%hu\n", boardSize);
    fprintf(filePtr, "%d\n", handicapUsed);
    fprintf(filePtr, "%d\n", firstTurn);
    for (int i = 0; i < (boardSize * boardSize); i++) fprintf(filePtr, "%d\n", preventKOBoardState[i]);
    for (int i = 0; i < (boardSize * boardSize); i++) fprintf(filePtr, "%d\n", gameBoard[i]);
    for (int p = 0; p < CONSTANTS::PlayersAmount; p++) fprintf(filePtr, "%g\n", scores[p]);
    fprintf(filePtr, "%d\n", turn);
    // write cursor x, y
    unsigned short relativeX, relativeY;
    relativeX = xCoord - boardStartX;
    relativeY = yCoord - boardStartY;
    fprintf(filePtr, "%hu %hu", relativeX, relativeY);

    fclose(filePtr);
}


void readDataFromFile(int **gameBoard, int **preventKOBoardState, float *scores, unsigned short *board_size, int *turn, unsigned short *xCoord, unsigned short *yCoord, int *handicapUsed, int *firstTurn, int init,unsigned short boardStartX, unsigned short boardStartY)
{
    char filename[MaxFilenameLength];
    getFilename(filename);
    FILE *filePtr;
    filePtr = fopen(filename, "r");

    if(filePtr == nullptr)
    {
        clrscr();
        cputs("File does not exist! Press any key to continue...");
        getch();
        readDataFromFile(gameBoard, preventKOBoardState, scores, board_size, turn, xCoord, yCoord, handicapUsed, firstTurn, init, boardStartX, boardStartY);
        return;
    }

    fscanf(filePtr, "%hu\n", board_size);

    // deallocate memory if it is already allocated
    if (!init)
    {
        if (*gameBoard) free(*gameBoard);
        if (*preventKOBoardState) free(*preventKOBoardState);
    }
    *gameBoard = (int *) calloc(((*board_size) * (*board_size)), sizeof(int));
    *preventKOBoardState = (int *) calloc(((*board_size) * (*board_size)), sizeof(int));

    fscanf(filePtr, "%d\n", handicapUsed);
    fscanf(filePtr, "%d\n", firstTurn);

    for (int i = 0; i < ((*board_size) * (*board_size)); i++) fscanf(filePtr, "%d\n", *preventKOBoardState + i);
    for (int i = 0; i < ((*board_size) * (*board_size)); i++) fscanf(filePtr, "%d\n", *gameBoard + i);
    for (int p = 0; p < CONSTANTS::PlayersAmount; p++) fscanf(filePtr, "%g\n", scores + p);
    fscanf(filePtr, "%d\n", turn);
    // read cursor data
    unsigned short relativeX, relativeY;
    fscanf(filePtr, "%hu %hu", &relativeX, &relativeY);
    *yCoord = boardStartY + relativeY;
    *xCoord = boardStartX + relativeX;

    fclose(filePtr);
}