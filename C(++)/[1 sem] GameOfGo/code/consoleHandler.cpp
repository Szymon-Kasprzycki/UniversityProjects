#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "string.h"
#include "consoleHandler.h"
#include "otherFunctions.h"
#include "constants.h"


void switchTextColor(int color)
{
    if (color == BLACK)
    {
        textbackground(LIGHTGRAY);
        textcolor(BLACK);
    }
    else
    {
        textbackground(BLACK);
        textcolor(LIGHTGRAY);
    }
}


void printInstructions(int const xCoord, int const yCoord)
{
    char instructions[][55] = {"Szymon Kasprzycki 193065","arrows  = move cursor",
                               "i       = place a stone on the board",
                               "enter   = confirm current choice and end player's turn",
                               "esc     = cancel current choice and end player's turn",
                               "s       = save the game state",
                               "l       = load the game state",
                               "n       = start a new game",
                               "f       = finish the game",
                               "q       = exit"};

    for (int i=0; i < sizeof(instructions)/sizeof(instructions[0]); i++)
    {
        gotoxy(xCoord, yCoord + i);
        cputs(instructions[i]);
    }
}


void printKeyPressed(int const xCoord, int const yCoord, int const key, int const firstCharZero)
{
    char txt[50] = "Clicked key code: ";
    if (firstCharZero) sprintf(txt, "Clicked key code: 0x00 0x%02x", key);
    else sprintf(txt, "Clicked key code: 0x%02x", key);
    gotoxy(xCoord, yCoord);
    cputs(txt);
}


void printCurrentPosition(int xPos, int yPos, unsigned short const x, unsigned short const y, short const boardXPos, short const boardYPos)
{
    char text[3][26] = {"Current cursor position: ","x = ","y = "};
    unsigned short nx = x - boardXPos;
    unsigned short ny= y - boardYPos;
    sprintf(text[1], "x = %d", nx);
    sprintf(text[2], "y = %d", ny);
    for (int i = 0; i<sizeof(text)/sizeof(text[0]); i++)
    {
        gotoxy(xPos, yPos+i);
        cputs(text[i]);
    }
}


void printScores(unsigned short xPos, unsigned short yPos, int turn, float const* scores)
{
    gotoxy(xPos, yPos);
    for (int i = 0; i<sizeof(&scores)/sizeof(int); i++)
    {
        char txt[32];
        if (i == (CONSTANTS::BlackStone-1))
        {
            switchTextColor(BLACK);
            sprintf(txt, "%s SCORE: %g", "BLACK", scores[i]);
        }
        else if (i == (CONSTANTS::WhiteStone-1))
        {
            switchTextColor(LIGHTGRAY);
            sprintf(txt, "%s SCORE: %g", "WHITE", scores[i]);
        }
        cputs(txt);
        switchTextColor(LIGHTGRAY);
        cputs(" ");
    }
    gotoxy(xPos, yPos + 2);
    if (turn == CONSTANTS::WhiteStone)
    {
        cputs("WHITE TURN!");
    }
    else if (turn == CONSTANTS::BlackStone)
    {
        switchTextColor(BLACK);
        cputs("BLACK TURN!");
        switchTextColor(LIGHTGRAY);
    }
}


void printBoard(short const boardStartX, short const BoardStartY, unsigned short int const size, const int* data)
{
    int helpSize = size + 2;
    for (int i = 0; i < helpSize; i++)
    {
        for (int j = 0; j < helpSize; j++)
        {
            gotoxy(boardStartX + j, BoardStartY + i);
            if (i % (helpSize - 1) == 0 && j % (helpSize - 1) == 0) cputs("+");
            else if (i == 0 || i == helpSize - 1) cputs("-");
            else if (j == 0 || j == helpSize - 1) cputs("|");
            else if (j>0 && i>0 && j<=size && i<=size)
            {
                int dataRelativeI = i-1;
                int dataRelativeJ = j-1;
                int coord = dataRelativeI*size + dataRelativeJ;
                if (data[coord] == CONSTANTS::WhiteStone)
                {
                    cputs("O");
                }
                else if (data[coord] == CONSTANTS::BlackStone)
                {
                    switchTextColor(BLACK);
                    cputs("O");
                    switchTextColor(WHITE);
                }
            }
        }
    }
}


void move(char direction, unsigned short int* coord, const short boardStartPos, const unsigned short boardSize)
{
    switch (direction)
    {
        case '+':
            if ((*coord) < (boardStartPos + boardSize)) (*coord)++;
            break;
        case '-':
            if ((*coord)-1 > boardStartPos) (*coord)--;
            break;
    }
}


void movePlayer(int input, unsigned short* x, unsigned short* y, short const boardStartXPos, short const boardStartYPos, unsigned short boardSize)
{
    switch (input)
    {
        case 0x48:
            move('-', y, boardStartYPos, boardSize);
            break;
        case 0x50:
            move('+', y, boardStartYPos, boardSize);
            break;
        case 0x4b:
            move('-', x, boardStartXPos, boardSize);
            break;
        case 0x4d:
            move('+', x, boardStartXPos, boardSize);
            break;
    }
}


void spawnCursor(unsigned short const x, unsigned short const y)
{
    gotoxy(x, y);
    textbackground(CONSTANTS::cursorBackgroundColor);
    textcolor(CONSTANTS::cursorTextColor);
    putch(CONSTANTS::cursorSign);
    switchTextColor(LIGHTGRAY);
}


void printHandicapInstructions(int xPos, int yPos)
{
    char instructions[4][40] = {"Please place handicap stones.",
                                "arrows - move cursor",
                                "i - place (or remove) black stone",
                                "enter - accept black stones positions"};
    for (int i = 0; i< sizeof(instructions)/sizeof(instructions[0]); i++)
    {
        gotoxy(xPos, yPos + i);
        cputs(instructions[i]);
    }
}


int generateMenu(char* title, char options[][30], int optionsCount)
{
    _setcursortype(_NOCURSOR);
    int selectedOption = 1;
    int optionChosen = 0;
    int userInput;
    char titleNew[60];

    sprintf(titleNew, "* %s *", title);
    int starsLen = (int)strlen(titleNew);

    do {
        int column = 5;
        int row = 5;
        clrscr();
        gotoxy(column,row);
        for (int i = 0; i < starsLen; i++) putch('*');
        row++;
        gotoxy(column,row);
        cputs(titleNew);
        row++;
        gotoxy(column,row);
        for (int i = 0; i < starsLen; i++) putch('*');

        row+=1;
        for (int i = 0; i < optionsCount; i++)
        {
            row+=1;
            gotoxy(column, row);
            if ((i+1) == selectedOption) switchTextColor(BLACK);
            cputs(*(options + i));
            switchTextColor(LIGHTGRAY);
        }

        row+=15;
        gotoxy(column, row);
        cputs("Instructions:");
        row++;
        gotoxy(column, row);
        cputs("arrows - move between options");
        row++;
        gotoxy(column, row);
        cputs("enter  - choose selected option");
        userInput = getch();

        switch (userInput)
        {
            case 0:
                userInput = getch();
                // if user want to choose higher option
                if (userInput == 0x48 && selectedOption > 1) selectedOption--;
                // if user want to choose lower option
                else if (userInput == 0x50 && selectedOption < optionsCount) selectedOption++;
                break;
            case 0x0d:
                optionChosen = selectedOption;
                break;
        }
    } while (!optionChosen);

    return optionChosen;
}


int showGameMenu()
{
    char title[50] = "GAME OF GO";
    const int optionsCount = 3;
    char options[optionsCount][30] = {"Start new game", "Load game from file", "Quit"};
    return generateMenu(title, options, optionsCount);
}


unsigned short askForCustomSize()
{
    const int row = 5;
    const int column = 5;
    char* keys;

    clrscr();
    _setcursortype(_NORMALCURSOR);

    gotoxy(column, row);
    cputs("Please specify custom board size: ");

    keys = (char *) malloc(sizeof(char));
    keys[0] = '\0';

    int i = 0;
    int input;
    int gettingNumber = 1;
    while (gettingNumber)
    {
        do {
            input = getche();
            if (input == 0x0d) gettingNumber = 0;
            else if (input == 0x08 && i != 0)
            {
                --i;
                keys[i] = '\0';
                keys = (char *) realloc(keys, (i + 2) * sizeof(char));
            }
            else
            {
                keys = (char*) realloc(keys, (i+2)*sizeof(char));
                keys[i] = (char) input;
                keys[i+1] = '\0';
            }
        } while (isCharNumber(input));
        i++;
    }
    int size = concatNumberFromCharArray(keys, i);
    free(keys);

    _setcursortype(_NOCURSOR);
    return size;
}


unsigned short askForBoardSize(short const boardStartX, short const boardStartY) {
    char title[50] = "Please choose board size";
    const int optionsCount = 4;
    char options[optionsCount][30] = {"9x9", "13x13", "19x19", "custom"};

    unsigned short chosenSize = 0;
    int optionChosen;
    int sizeIsProper = 0;
    do {
        optionChosen = generateMenu(title, options, optionsCount);
        switch (optionChosen)
        {
            case 1:
                chosenSize = 9;
                break;
            case 2:
                chosenSize = 13;
                break;
            case 3:
                chosenSize = 19;
                break;
            case 4:
                chosenSize = askForCustomSize();
                break;
        }
        struct text_info screenInformation{};
        gettextinfo(&screenInformation);
        if ((boardStartX + chosenSize) < screenInformation.screenwidth && (boardStartY + chosenSize) < screenInformation.screenheight)
        {
            sizeIsProper = 1;
        }
        else
        {
            clrscr();
            gotoxy(5,5);
            cputs("This size is too big! Press any key to continue...");
            getch();
        }
    } while (!sizeIsProper);

    return chosenSize;
}


int askForHandicap(int* gameBoard, unsigned short boardSize)
{
    const int boardBorderThick = 2;

    char title[50] = "Do you want to use handicap?";
    const int optionsCount = 2;
    char options[optionsCount][30] = {"Yes", "No"};
    int optionChosen = generateMenu(title, options, optionsCount);

    int useHandicap = (optionChosen == 1) ? 1 : 0;
    int input;

    if (useHandicap)
    {
        int choiceMade = 0;
        unsigned short cursorCoordX = 1+ (boardSize + 1) / 2;
        unsigned short cursorCoordY = 1+ (boardSize + 1) / 2;
        while (!choiceMade)
        {
            clrscr();
            printBoard(1, 1, boardSize, gameBoard);
            printHandicapInstructions(60, 2);
            spawnCursor(cursorCoordX, cursorCoordY);
            input = getch();
            if (input == 0)
            {
                input = getch();
                movePlayer(input, &cursorCoordX, &cursorCoordY, 1, 1, boardSize);
            }
            else if (input == 'i')
            {
                int boardRelativeX = cursorCoordX-boardBorderThick;
                int boardRelativeY = cursorCoordY-boardBorderThick;
                int arrayCoordinate = boardRelativeY * boardSize + boardRelativeX;

                gameBoard[arrayCoordinate] = 1 - gameBoard[arrayCoordinate];  // if 0 --> 1-0=1, if 1 --> 1-1=0
            }
            else if (input == '\r' || input == '\n') choiceMade = 1;
        }
    }
    return useHandicap;
}


void renderGameWindow(const char boardSide, unsigned short* xCoordinate, unsigned short* yCoordinate, unsigned short boardSize, const int* gameBoard, const float* scores, int turn, int key, int doubleKey, int firstTurn)
{
    // Coordinates are saved as {x, y}
    short boardStartCoordinates[2];
    short instructionsStartCoordinates[2];
    short scoresStartCoordinates[2];
    short currentPosStartCoordinates[2];
    short keyPressedStartCoordinates[2];
    switch (boardSide)
    {
        case 'R':
            boardStartCoordinates[0] = 60;
            boardStartCoordinates[1] = 2;

            instructionsStartCoordinates[0] = 2;
            instructionsStartCoordinates[1] = 2;

            scoresStartCoordinates[0] = 2;
            scoresStartCoordinates[1] = 16;

            currentPosStartCoordinates[0] = 2;
            currentPosStartCoordinates[1] = 22;

            keyPressedStartCoordinates[0] = 2;
            keyPressedStartCoordinates[1] = 26;
            break;
        case 'L':
            boardStartCoordinates[0] = 2;
            boardStartCoordinates[1] = 2;

            instructionsStartCoordinates[0] = 67;
            instructionsStartCoordinates[1] = 2;

            scoresStartCoordinates[0] = 67;
            scoresStartCoordinates[1] = 16;

            currentPosStartCoordinates[0] = 67;
            currentPosStartCoordinates[1] = 22;

            keyPressedStartCoordinates[0] = 67;
            keyPressedStartCoordinates[1] = 26;
            break;
    }
    if (firstTurn)
    {
        *xCoordinate = boardStartCoordinates[0] + (boardSize+1)/2;
        *yCoordinate = boardStartCoordinates[1] + (boardSize+1)/2;
    }
    clrscr();
    switchTextColor(LIGHTGRAY);
    // Print everything game-related
    printInstructions(instructionsStartCoordinates[0], instructionsStartCoordinates[1]);

    printScores(scoresStartCoordinates[0], scoresStartCoordinates[1], turn, scores);

    printCurrentPosition(currentPosStartCoordinates[0], currentPosStartCoordinates[1], *xCoordinate, *yCoordinate, boardStartCoordinates[0], boardStartCoordinates[1]);

    printKeyPressed(keyPressedStartCoordinates[0], keyPressedStartCoordinates[1], key, doubleKey);

    printBoard(boardStartCoordinates[0], boardStartCoordinates[1], boardSize, gameBoard);

    spawnCursor(*xCoordinate, *yCoordinate);
}