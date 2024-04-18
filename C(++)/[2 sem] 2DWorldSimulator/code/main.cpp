#include <iostream>
#include "src/.headers/World.h"
#include "src/worldObjects/.headers/Human.h"
#include "src/worldObjects/animals/.headers/Wolf.h"
#include "src/worldObjects/animals/.headers/Sheep.h"
#include "src/worldObjects/animals/.headers/Turtle.h"
#include "src/worldObjects/animals/.headers/Antelope.h"
#include "src/worldObjects/animals/.headers/Fox.h"
#include "src/worldObjects/plants/.headers/Belladonna.h"
#include "src/worldObjects/plants/.headers/SosnowskyHogweed.h"
#include "src/worldObjects/plants/.headers/Grass.h"
#include "src/worldObjects/plants/.headers/Guarana.h"
#include "src/worldObjects/plants/.headers/SowThistle.h"
#include <conio.h>
#include <windows.h>
#include <vector>

#define width 60
#define height 20

using namespace std;

void disableCursor() {
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &ConCurInf);
}

int main() {
    // Create organisms
    HWND hWnd = GetConsoleWindow(); // get the handle to the console window
    SetWindowText(hWnd, "Szymon Kasprzycki 193065"); // set the window title

    auto *world = new World(width, height);
    auto *human = new Human(5, 5, world);

    world->addOrganism(human);
    world->addOrganism(new Wolf(7,7, world));
    world->addOrganism(new Wolf(40,7, world));
    world->addOrganism(new Wolf(12,19, world));
    world->addOrganism(new Sheep(55,3, world));
    world->addOrganism(new Sheep(1,1, world));
    world->addOrganism(new Turtle(15,19, world));
    world->addOrganism(new Turtle(7,5, world));
    world->addOrganism(new Antelope(25,9, world));
    world->addOrganism(new Antelope(30,4, world));
    world->addOrganism(new Fox(30,12, world));
    world->addOrganism(new Fox(50,15, world));
    world->addOrganism(new Grass(35,18, world));
    world->addOrganism(new Grass(10,10, world));
    world->addOrganism(new SosnowskyHogweed(10,9, world));
    world->addOrganism(new SosnowskyHogweed(20,9, world));
    world->addOrganism(new Belladonna(49,18, world));
    world->addOrganism(new Guarana(27,19, world));
    world->addOrganism(new SowThistle(57,13, world));

    // disable cursor
    disableCursor();

    // Loop of moving human // !human->isEndGame()
    world->drawWorld();
    while (!human->isEndGame())
    {
        human->action();
        if (human->isEndGame()) break;
        world->makeTurn();
        system("cls");
        world->drawWorld();
        if (!human->isAlive()) break;
    }

    cout << endl << "Game over!" << endl;
    // Wait for key press
    cout << "Press any key to exit..." << endl;
    _getch();

    // Delete world
    delete world;
    delete human;
    return 0;
}

