#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

void setupBoardPosition(short *boardStartX, short *boardStartY, char boardSide);

void processGame(int **gameBoard, int **lastBoardState, float *scores, int *userInput, int *firstInputCharZero,
                 unsigned short *xCoord, unsigned short *yCoord, unsigned short *boardSize, short boardStartX,
                 short boardStartY, int *turn, int *firstTurn, int *useHandicap, int *continueGame);

#endif //GAMEHANDLER_H
