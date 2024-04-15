#ifndef TEST_MAPINPUTPROCESSOR_H
#define TEST_MAPINPUTPROCESSOR_H

#include "MyQueue.h"
#include "MyString.h"
#include "City.h"
#include "Graph.h"
#include "HashMap.h"

class mapInputProcessor {
public:
    mapInputProcessor();

    mapInputProcessor(const mapInputProcessor &src);

    ~mapInputProcessor();

    mapInputProcessor &operator=(const mapInputProcessor &src);

    void processInput();

    void processCommands();

private:
    int iWidth;
    int iHeight;
    char *map;
    int cityAmount;
    int planeAmount;
    City *cities;
    Graph *graph;
    HashMap *cityHashMap;

    void readDimensions();

    void readMap();

    void readPlaneTravel();

    void processCities();

    void processCityConnections();

    int getMoveCount(int sX, int sY, int eX, int eY);

    void getBFSNeighbours(int x, int y, MyQueue *xQueue, MyQueue *yQueue, bool *visited, int *nodesInNextLayer, int eX,
                          int eY) const;

    bool isPointOnMap(int x, int y) const;

    void readCityName(int x, int y, MyString *cityName) const;

    static void readPlaneCityName(MyString &name);

    static void readPlaneTime(char *timeS);
};


#endif //TEST_MAPINPUTPROCESSOR_H
