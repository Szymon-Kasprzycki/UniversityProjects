#ifndef FILEHANDLER_H
#define FILEHANDLER_H

void getFilename(char *filename);

void writeDataToFile(int *gameBoard, int *preventKOBoardState, float *scores, unsigned short boardSize, int turn,
                     unsigned short xCoord, unsigned short yCoord, int handicapUsed, int firstTurn,
                     unsigned short boardStartX, unsigned short boardStartY);

void readDataFromFile(int **gameBoard, int **preventKOBoardState, float *scores, unsigned short *board_size, int *turn,
                      unsigned short *xCoord, unsigned short *yCoord, int *handicapUsed, int *firstTurn, int init,
                      unsigned short boardStartX, unsigned short boardStartY);

#endif //FILEHANDLER_H
