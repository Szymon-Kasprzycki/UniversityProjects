#include <iostream>
#include <vector>

bool containsStarGraph(const std::vector<std::vector<int>>& adjacencyMatrix) {
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        int connectedCount = 0;

        for (int j : adjacencyMatrix[i]) {
            if (j == 1) {++connectedCount;}
        }

        if (connectedCount >= 3) {
            bool isStar = false;
            for (int j = 0; j < adjacencyMatrix.size(); j++) {
                for (int k = j+1; k < adjacencyMatrix.size(); k++) {
                    for (int l = k+1; l < adjacencyMatrix.size(); l++) {
                        if (adjacencyMatrix[i][j] == 1 && adjacencyMatrix[i][l] == 1 && adjacencyMatrix[i][k] == 1) {
                            if (adjacencyMatrix[j][k] == 0 && adjacencyMatrix[j][l] == 0 && adjacencyMatrix[k][l] == 0)
                            {
                                isStar = true;
                                break;
                            }
                        }
                    }
                    if (isStar) {break;}
                }
                if (isStar) {break;}
            }
            if (isStar) {return true;}
        }
    }

    return false;
}

int main() {
    int testAmount;
    int numVertices;

    std::cin >> testAmount;

    for (int i = 0; i < testAmount; ++i) {
        std::cin >> numVertices;
        getchar();

        std::vector<std::vector<int>> adjacencyMatrix(numVertices, std::vector<int>(numVertices));
        for (int k = 0; k < numVertices; ++k) {
            for (int j = 0; j < numVertices; ++j) {
                adjacencyMatrix[k][j] = getchar() - '0';
            }
        }

        if (containsStarGraph(adjacencyMatrix)) {
            std::cout << "0" << std::endl;
        } else {
            std::cout << "1" << std::endl;
        }
    }

    return 0;
}