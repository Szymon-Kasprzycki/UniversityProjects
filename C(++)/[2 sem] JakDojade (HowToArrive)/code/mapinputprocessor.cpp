#include "mapInputProcessor.h"
#include "iostream"
#include "MyString.h"
#include "MyQueue.h"
#include "helpFuncs.h"

using namespace std;

void mapInputProcessor::readPlaneCityName(MyString &name) {
    while (true) {
        char c;
        c = (char) getchar();
        if (c == ' ') break;
        else if (c == '\n') continue;
        name += c;
    }
}

void mapInputProcessor::readPlaneTime(char *timeS) {
    int i = 0;
    while (true) {
        char c;
        c = (char) getchar();
        if (c == '\n' || c == ' ') break;
        timeS[i] = c;
        i++;
    }
    timeS[i] = '\0';
}


mapInputProcessor::mapInputProcessor() {
    this->iWidth = 0;
    this->iHeight = 0;
    this->planeAmount = 0;
    this->cityAmount = 0;
    this->map = nullptr;
    this->cities = nullptr;
    this->graph = nullptr;
    this->cityHashMap = new HashMap();
}

mapInputProcessor::mapInputProcessor(const mapInputProcessor &src) {
    this->iWidth = src.iWidth;
    this->iHeight = src.iHeight;
    this->planeAmount = src.planeAmount;
    this->cityAmount = src.cityAmount;
    this->map = new char[this->iWidth * this->iHeight];
    for (int i = 0; i < this->iWidth * this->iHeight; i++) {
        this->map[i] = src.map[i];
    }
    this->cities = new City[this->cityAmount];
    for (int i = 0; i < this->cityAmount; i++) {
        this->cities[i] = src.cities[i];
    }
    this->graph = new Graph(*src.graph);
    this->cityHashMap = new HashMap(*src.cityHashMap);
}

mapInputProcessor &mapInputProcessor::operator=(const mapInputProcessor &src) {
    if (this == &src) return *this;
    this->iWidth = src.iWidth;
    this->iHeight = src.iHeight;
    this->planeAmount = src.planeAmount;
    this->cityAmount = src.cityAmount;
    this->map = new char[this->iWidth * this->iHeight];
    for (int i = 0; i < this->iWidth * this->iHeight; i++) {
        this->map[i] = src.map[i];
    }
    this->cities = new City[this->cityAmount];
    for (int i = 0; i < this->cityAmount; i++) {
        this->cities[i] = src.cities[i];
    }
    this->graph = new Graph(*src.graph);
    this->cityHashMap = new HashMap(*src.cityHashMap);
    return *this;
}

mapInputProcessor::~mapInputProcessor() {
    delete[] map;
    delete graph;
    delete cityHashMap;
}

void mapInputProcessor::readDimensions() {
    std::cin >> this->iWidth;
    std::cin >> this->iHeight;
}

void mapInputProcessor::readMap() {
    this->map = new char[this->iWidth * this->iHeight];
    for (int i = 0; i < this->iHeight; i++) {
        for (int j = 0; j < this->iWidth; j++) {
            std::cin >> this->map[(i * this->iWidth) + j];
            if (this->map[(i * this->iWidth) + j] == '*') this->cityAmount++;
        }
    }
}

void mapInputProcessor::readPlaneTravel() {
    std::cin >> this->planeAmount;
    if (this->planeAmount == 0) return;

    char *timeS = new char[4];

    for (int i = 0; i < this->planeAmount; i++) {
        int time;
        MyString cityA;
        MyString cityB;
        readPlaneCityName(cityA);
        readPlaneCityName(cityB);
        readPlaneTime(timeS);
        time = atoi(timeS);

        City *cityAObj = this->cityHashMap->get(cityA);
        City *cityBObj = this->cityHashMap->get(cityB);
        if (cityAObj != nullptr && cityBObj != nullptr) {
            this->graph->addEdge(cityAObj, cityBObj, time, true);
        }
    }
}

void mapInputProcessor::processInput() {
    this->readDimensions();
    this->readMap();
    this->processCities();
    this->processCityConnections();
    this->readPlaneTravel();
}

void mapInputProcessor::processCities() {
    int cityIndex = 0;
    this->cities = new City[this->cityAmount];
    for (int i = 0; i < this->iHeight; i++) {
        for (int j = 0; j < this->iWidth; j++) {
            if (this->map[(i * this->iWidth) + j] == '*') {
                City *city = new City();
                city->name = new MyString();
                city->y = i;
                city->x = j;
                city->index = cityIndex;
                // find city name - check all 8 neighbour cells
                int xNeighbour[8] = {0, 1, -1, 0, 1, -1, 1, -1};
                int yNeighbour[8] = {1, 0, 0, -1, -1, -1, 1, 1};
                for (int l = 0; l < 4; l++) {
                    int neighbourX = j + xNeighbour[l];
                    int neighbourY = i + yNeighbour[l];

                    if (isPointOnMap(neighbourX, neighbourY)) {
                        char sign = this->map[neighbourY * this->iWidth + neighbourX];
                        if (sign == '#' || sign == '*') {
                            city->has_any_route = true; // if city is not isolated (has either # or * neighbour)
                            break;
                        }
                    }
                }
                for (int k = 0; k < 8; k++) {
                    int neighbourX = j + xNeighbour[k];
                    int neighbourY = i + yNeighbour[k];
                    if (isPointOnMap(neighbourX, neighbourY) &&
                        isPartOfCityName(this->map[neighbourY * this->iWidth + neighbourX])) {
                        readCityName(neighbourX, neighbourY, city->name);
                        break;
                    }
                }
                cityIndex++;

                // Add city to hashmap
                this->cityHashMap->add(city);
                this->cities[city->index] = *city;
            }
        }
    }
    this->graph = new Graph(this->cityAmount);
}

void mapInputProcessor::processCityConnections() {
    for (int i = 0; i < this->cityAmount; i++) {
        this->graph->addVertexName(&this->cities[i]);
        if (!this->cities[i].has_any_route) continue;
        for (int j = 0; j < this->cityAmount; j++) {
            if (i == j || j < i) continue; // if j < i then we already checked this edge
            int moveCount = this->getMoveCount(this->cities[i].x, this->cities[i].y, this->cities[j].x,
                                               this->cities[j].y);
            if (moveCount != -1) {
                this->graph->addEdge(&this->cities[i], &this->cities[j], moveCount, false);
            }
        }
    }

}

// Implementation of BFS algorithm to find the shortest path between two points
int mapInputProcessor::getMoveCount(int sX, int sY, int eX, int eY) {
    if (sX == eX && sY == eY) return 0;
    bool found = false;
    int moveCount = 0;
    int leftInLayer = 1;
    int inNextLayer = 0;
    auto *xQueue = new MyQueue();
    auto *yQueue = new MyQueue();
    bool *visited = new bool[this->iWidth * this->iHeight];
    for (int i = 0; i < (this->iWidth * this->iHeight); i++) { visited[i] = false; }

    xQueue->enqueue(sX);
    yQueue->enqueue(sY);
    visited[(sY * this->iWidth) + sX] = true;

    while (!xQueue->isEmpty()) {
        int currentX = xQueue->dequeue();
        int currentY = yQueue->dequeue();

        if (currentX == eX && currentY == eY) {
            found = true;
            break;
        }

        this->getBFSNeighbours(currentX, currentY, xQueue, yQueue, visited, &inNextLayer, eX, eY);
        leftInLayer--;
        if (leftInLayer == 0) {
            leftInLayer = inNextLayer;
            inNextLayer = 0;
            moveCount++;
        }
    }

    delete xQueue;
    delete yQueue;
    delete[] visited;

    if (found) { return moveCount; }
    return -1;
}

void mapInputProcessor::getBFSNeighbours(int x, int y, MyQueue *xQueue, MyQueue *yQueue, bool *visited,
                                         int *nodesInNextLayer, int eX, int eY) const {
    int xNeighbours[4] = {x, x, x + 1, x - 1};
    int yNeighbours[4] = {y + 1, y - 1, y, y};

    for (int i = 0; i < 4; i++) {
        int currentX = xNeighbours[i];
        int currentY = yNeighbours[i];

        // Check if neighbour is on the map
        if (currentX < 0 || currentX >= this->iWidth || currentY < 0 || currentY >= this->iHeight) continue;
        // Check if neighbour is already visited
        if (visited[currentY * this->iWidth + currentX]) continue;
        // Check if neighbour is possible to visit
        // if point is not # or eX, eY, continue
        if (this->map[currentY * this->iWidth + currentX] != '#' && (currentX != eX || currentY != eY))
            continue;

        xQueue->enqueue(currentX);
        yQueue->enqueue(currentY);
        visited[currentY * this->iWidth + currentX] = true;
        (*nodesInNextLayer)++;
    }
}

bool mapInputProcessor::isPointOnMap(int x, int y) const {
    return x >= 0 && x < this->iWidth && y >= 0 && y < this->iHeight;
}

void mapInputProcessor::readCityName(int x, int y, MyString *cityName) const {
    // get to the first letter of the city name
    while (isPointOnMap(x - 1, y) && isPartOfCityName(this->map[y * this->iWidth + x - 1])) { x--; }
    // read the whole city name
    while (isPointOnMap(x, y) && isPartOfCityName(this->map[y * this->iWidth + x])) {
        (*cityName) += this->map[y * this->iWidth + x];
        x++;
    }
}

void mapInputProcessor::processCommands() {
    int commandAmount;
    MyString cityA;
    MyString cityB;
    int mode;
    std::cin >> commandAmount;
    for (int i = 0; i < commandAmount; i++) {
        std::cin >> cityA;
        std::cin >> cityB;
        std::cin >> mode;

        if (cityA == cityB) {
            std::cout << "0" << std::endl;
            continue;
        }

        City *cityAptr = this->cityHashMap->get(cityA);
        City *cityBptr = this->cityHashMap->get(cityB);

        if (cityAptr == nullptr || cityBptr == nullptr) {
            std::cout << "ERROR" << std::endl;
            continue;
        }

        if (mode == 0) {
            int moveCount = this->graph->getShortestPath(cityAptr, cityBptr);
            std::cout << moveCount << std::endl;
        } else if (mode == 1) {
            auto *citiesVisited = new MyString[this->cityAmount];
            int citiesVisitedSize = 0;
            int moveCount = this->graph->getShortestPathWithCities(cityAptr, cityBptr, citiesVisited,
                                                                   &citiesVisitedSize);
            std::cout << moveCount;
            if (citiesVisitedSize != 2) {
                for (int j = citiesVisitedSize - 1; j >= 0; j--) {
                    if (!(citiesVisited[j] == cityA || citiesVisited[j] == cityB)) {
                        std::cout << " " << citiesVisited[j];
                    }
                }
            }
            std::cout << std::endl;
            delete[] citiesVisited;
        }
    }
}