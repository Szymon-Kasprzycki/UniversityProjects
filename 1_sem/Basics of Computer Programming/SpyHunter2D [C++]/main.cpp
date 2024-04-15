#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

// CONSTANTS
//              User 
#define FULLSCREEN      false
#define SCREEN_WIDTH    900
#define SCREEN_HEIGHT   900
//              Script
#define NORMAL_SPEED    1            // speed of the car at normal state
#define LOW_SPEED       0.4          // speed of the car at slow gear
#define HIGH_SPEED      1.5          // spped of the car at fast gear
#define RESPAWN_TIME    5            // time with infinite lives at the start (in seconds)
#define CAR_SIZE        120          // car size in pixels
#define BIG_TEXT_SIZE   80           // big font size
#define SMALL_TEXT_SIZE 8            // small font size
#define ROAD_WIDTH      300          // base width of the road
#define ROAD_CHANGE     40           // amount of road width change once
#define MIN_GREEN_WIDTH 80           // minimal width of the grass at each side
#define DEFAULT_POINTS  150          // default point gain value
#define HIGH_POINTS     250          // fast gear point gain value


// DATA TYPES
typedef struct
{
    int* x;
    int* y;
} Coords;


typedef struct
{
    SDL_Window** window;
    SDL_Renderer** renderer;
    SDL_Surface** screen;
    SDL_Texture** scrtex;
    int rc;
} DisplayData;


typedef struct
{
    SDL_Surface* charset;
    SDL_Surface* car;
} Bitmaps;


typedef struct
{
    int livesAmount;
    double lastLifeAdded;
    bool infiniteLives;
    double playerPoints;
    double worldTime;
    Coords carPos;
    double speed;
    double pointGainValue;
} GameData;


typedef struct
{
    bool quit;
    bool pause;
    bool gameOver;
    bool end;
} GameStatus;


typedef struct
{
    double moveValue;
    int amount;
    int length;
    int thickness;
} LinesData;


typedef struct
{
    int width;
    int oldWidth;
    int rectangleHeight;
    int rectanglesAmount;
    int rectanglesChanged;
    double moveValue;
    LinesData lines;
} RoadData;


void loadingError(const char* customErrorDescription, const char* SDLerrorDescription)
{
    printf("[*ERROR*] %s\n[*SDL description*] %s", customErrorDescription, SDLerrorDescription);
}


void disableGame(SDL_Surface* charset, DisplayData* displayThings)
{
    SDL_FreeSurface(charset);
    SDL_FreeSurface(*displayThings->screen);
    SDL_DestroyTexture(*displayThings->scrtex);
    SDL_DestroyRenderer(*displayThings->renderer);
    SDL_DestroyWindow(*displayThings->window);
    SDL_Quit();
}


int loadBitmaps(Bitmaps* bitmaps, DisplayData* displayThings)
{
    bool disable = false;
    // load cs8x8.bmp
    bitmaps->charset = SDL_LoadBMP("./cs8x8.bmp");
    if (bitmaps->charset == NULL)
    {
        loadingError("SDL_LoadBMP(cs8x8.bmp)", SDL_GetError());
        disable = true;
    };
    SDL_SetColorKey(bitmaps->charset, true, 0x000000);

    // load car.bmp
    bitmaps->car = SDL_LoadBMP("./car-res.bmp");
    if (bitmaps->car == NULL)
    {
        loadingError("SDL_LoadBMP(car.bmp)", SDL_GetError());
        disable = true;
    }

    if (disable)
    {
        disableGame(bitmaps->charset, displayThings);
        return 1;
    }
    return 0;
}


int prepareScreen(DisplayData* displayThings)
{
    SDL_Window* winTemp;
    SDL_Renderer* renderTemp;
    SDL_Surface* screenTemp;
    SDL_Texture* scrtexTemp;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        loadingError("SDL_Init error", SDL_GetError());
        return 1;
    }

    if (FULLSCREEN) displayThings->rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &winTemp, &renderTemp);
    else displayThings->rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &winTemp, &renderTemp);

    if (displayThings->rc != 0)
    {
        loadingError("SDL_CreateWindowAndRenderer error", SDL_GetError());
        SDL_Quit();
        return 1;
    };

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderTemp, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderTemp, 0, 0, 0, 255);

    SDL_SetWindowTitle(winTemp, "Spy hunter, Szymon Kasprzycki 193065");

    screenTemp = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    scrtexTemp = SDL_CreateTexture(renderTemp, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH, SCREEN_HEIGHT);

    // disable showing cursor
    SDL_ShowCursor(SDL_DISABLE);

    *displayThings->window = winTemp;
    *displayThings->renderer = renderTemp;
    *displayThings->screen = screenTemp;
    *displayThings->scrtex = scrtexTemp;

    return 0;
}


SDL_Color retrievePixelColor(const SDL_Surface* surface, const int x, const int y)
{
    SDL_Color Color = { 0x00, 0x00, 0x00, 0xFF };
    const Uint8 bytesPerPixel = surface->format->BytesPerPixel;
    // retrieve pixel address at the surface, where surface->pixels is a pointer to the array of pixels and surface->pitch is the length of a pixels bytes row
    Uint8* pixelAddress = (Uint8*)surface->pixels + y * surface->pitch + x * bytesPerPixel;
    Uint32 PixelData = *(Uint32*)pixelAddress; // read pixel data using obtained address
    SDL_GetRGB(PixelData, surface->format, &Color.r, &Color.g, &Color.b); // prepare returning object data
    return Color;
}


void DrawStringWithSize(SDL_Surface* screen, int x, int y, int size, const char* text, SDL_Surface* charset)
{
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = size;
    d.h = size;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitScaled(charset, &s, screen, &d);
        x += size;
        text++;
    };
};


// draw a surface sprite on a surface screen where (x,y) is its center on the screen
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};


void DrawCar(SDL_Surface* screen, SDL_Surface* carSurface, int x, int y) {
    SDL_Rect dest;
    dest.x = x - CAR_SIZE / 2;
    dest.y = y - CAR_SIZE / 2;
    dest.w = CAR_SIZE;
    dest.h = CAR_SIZE;
    SDL_BlitScaled(carSurface, NULL, screen, &dest);
};


void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = color;
};


// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
    for (int i = 0; i < l; i++) {
        DrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};


// draw a rectangle of size l by k starting in point (x, y)
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
    int i;
    DrawLine(screen, x, y, k, 0, 1, outlineColor);
    DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    DrawLine(screen, x, y, l, 1, 0, outlineColor);
    DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for (i = y + 1; i < y + k - 1; i++)
        DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};


void checkCollision(SDL_Surface* surface, GameData* gameData, GameStatus* gameStatus)
{
    bool collision;
    SDL_Color checkedColor;
    checkedColor = retrievePixelColor(surface, *(gameData->carPos.x), *(gameData->carPos.y));
    if (!(
        (checkedColor.r == 116 && checkedColor.g == 116 && checkedColor.b == 116) ||
        (checkedColor.r == 255 && checkedColor.g == 255 && checkedColor.b == 255) ||
        (checkedColor.r == 0 && checkedColor.g == 0 && checkedColor.b == 0))
        ) collision = true;
    else collision = false;

    if (collision && !(gameData->infiniteLives))
    {
        if (gameData->livesAmount > 1)
        {
            *(gameData->carPos.x) = SCREEN_WIDTH / 2;
            gameData->livesAmount -= 1;
        }
        else
        {
            gameStatus->gameOver = true;
        }
    }
    else if (collision && gameData->infiniteLives) *(gameData->carPos.x) = SCREEN_WIDTH / 2;
}


void DrawRoadLines(SDL_Surface* screen, RoadData* road)
{
    Uint32 white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
    double gap = (double)(SCREEN_HEIGHT - road->lines.amount * road->lines.length) / road->lines.amount;
    int len = road->lines.length;
    int xPos = SCREEN_WIDTH / 2 - road->lines.thickness / 2;
    for (int i = 0; i < road->lines.amount; i++)
    {
        double yPos = road->lines.moveValue + gap * i + i * road->lines.length;
        if (yPos + road->lines.length >= SCREEN_HEIGHT) // if line would be drawn under the screen - shrink its length
        {
            len = SCREEN_HEIGHT - (int)yPos;
        }
        if (len < road->lines.length && len > 0) // if line is smaller than full line, move its piece to the top
        {
            DrawRectangle(screen, xPos, 0, road->lines.thickness, road->lines.length - len, white, white);
        }
        DrawRectangle(screen, xPos, (int)yPos, road->lines.thickness, len, white, white);
    }
}


void DrawRoad(SDL_Surface* screen, RoadData* road)
{
    Uint32 green = SDL_MapRGB(screen->format, 0x00, 0x99, 0x00);
    Uint32 grey = SDL_MapRGB(screen->format, 0x99, 0x99, 0x99);
    Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    int curbWidth = 15;
    int drawWidth = road->oldWidth;
    SDL_FillRect(screen, NULL, green);
    // road is drawn splitted to `road->rectanglesAmount` rectangles vertically, each rectangle can get different width (thats how road changes its width)
    for (int i = 0; i < road->rectanglesAmount; i++)
    {
        if (i < road->rectanglesChanged) drawWidth = road->width;
        else drawWidth = road->oldWidth;
        DrawRectangle(screen, (SCREEN_WIDTH - drawWidth) / 2 - curbWidth, i * (SCREEN_HEIGHT / road->rectanglesAmount), curbWidth, road->rectangleHeight, grey, grey);
        DrawRectangle(screen, (SCREEN_WIDTH - drawWidth) / 2, i * (SCREEN_HEIGHT / road->rectanglesAmount), drawWidth, road->rectangleHeight, black, black);
        DrawRectangle(screen, (SCREEN_WIDTH - drawWidth) / 2 + drawWidth, i * (SCREEN_HEIGHT / road->rectanglesAmount), curbWidth, road->rectangleHeight, grey, grey);
    }

    DrawRoadLines(screen, road);
}


void renderInformationBox(SDL_Surface* screen, SDL_Surface* charset, GameData* gameData)
{
    Uint32 red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
    Uint32 blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
    char text[128];
    int textSize = 10;
    DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 46, red, blue);
    // upper rectangle
    sprintf(text, "Szymon Kasprzycki 193065         Lives: %d", gameData->livesAmount);
    DrawStringWithSize(screen, screen->w / 2 - (int)strlen(text) * textSize / 2, 10, textSize, text, charset);
    sprintf(text, "Esc - exit, \030 - high speed gear, \031 - low speed gear");
    DrawStringWithSize(screen, screen->w / 2 - (int)strlen(text) * textSize / 2, 30, textSize, text, charset);
    // implemented letters
    textSize = 8;
    sprintf(text, "IMPLEMENTED POINTS: A, B, C, D, E, F, H, I, M");
    DrawStringWithSize(screen, screen->w - (int)strlen(text) * textSize - 5, screen->h - textSize - 5, textSize, text, charset);
    // elapsed time
    textSize = 14;
    sprintf(text, "Time: %.1lf s", gameData->worldTime);
    DrawStringWithSize(screen, 10, 60, textSize, text, charset);
    // player points
    textSize = 14;
    sprintf(text, "Player points: %.0lf", gameData->playerPoints);
    DrawStringWithSize(screen, screen->w - (int)strlen(text) * textSize - 10, 60, textSize, text, charset);
}


int changeRoadWidth(int width)
{
    bool changeCondition = true;
    while (changeCondition)
    {
        int n = rand() % 2;
        if (n == 0 && width >= ROAD_WIDTH / 2 + ROAD_CHANGE)
        {
            width -= ROAD_CHANGE;
            changeCondition = false;
        }
        else if (n == 1 && width <= SCREEN_WIDTH - MIN_GREEN_WIDTH * 2 - ROAD_CHANGE)
        {
            width += ROAD_CHANGE;
            changeCondition = false;
        }
    }
    return width;
}


void updateGameData(GameData* gameData, double delta)
{
    // update game time and points
    gameData->worldTime += delta;
    gameData->playerPoints += delta * gameData->pointGainValue;
    // check if player should receive additional life
    if ((long int)gameData->playerPoints == gameData->lastLifeAdded + 1000)
    {
        if (!gameData->infiniteLives) ++(gameData->livesAmount);
        gameData->lastLifeAdded = (long int)gameData->playerPoints;
    }
    // check if player should still have infinite lives
    if (gameData->worldTime > RESPAWN_TIME && gameData->infiniteLives) gameData->infiniteLives = false;
}


void renderGameFrame(DisplayData* displayThings, RoadData* road, GameData* gameData, GameStatus* gameStatus,
    Bitmaps* bitmaps, double framesCounter)
{
    Uint32 black = SDL_MapRGB((*(displayThings->screen))->format, 0x00, 0x00, 0x00);
    SDL_FillRect(*(displayThings->screen), NULL, black);

    road->moveValue += gameData->speed;
    if (road->moveValue >= SCREEN_HEIGHT && road->rectanglesChanged == 0)
    {
        road->rectanglesChanged = 1;
        // change the width of the road
        road->width = changeRoadWidth(road->oldWidth);
        road->moveValue = 0;
    }
    // increase number of rectangles that should have changed width on the next frame
    else if (road->rectanglesChanged > 0 && road->rectanglesChanged < 10)
    {
        if ((long int)framesCounter % 100 == 0) road->rectanglesChanged++;
    }
    // if all road rectangles have changed width already -> reset process
    else
    {
        road->rectanglesChanged = 0;
        road->oldWidth = road->width;
    }

    DrawRoad(*displayThings->screen, road);
    // update road lines
    road->lines.moveValue += gameData->speed;
    if (road->lines.moveValue >= 85) road->lines.moveValue = 0;

    checkCollision(*displayThings->screen, gameData, gameStatus);

    DrawCar(*displayThings->screen, bitmaps->car, *gameData->carPos.x, *gameData->carPos.y);

    renderInformationBox(*displayThings->screen, bitmaps->charset, gameData);
}


void renderGameOver(SDL_Surface* screen, SDL_Surface* charset)
{
    Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    char* text = "GAME OVER";
    int textSize = BIG_TEXT_SIZE;
    SDL_FillRect(screen, NULL, black);
    DrawStringWithSize(screen, SCREEN_WIDTH / 2 - (int)strlen(text) * textSize / 2, screen->h / 2 - textSize / 2, textSize, text, charset);
    text = "Press esc to exit";
    textSize = BIG_TEXT_SIZE / 4;
    DrawStringWithSize(screen, SCREEN_WIDTH / 2 - (int)strlen(text) * textSize / 2, screen->h / 2 + BIG_TEXT_SIZE - 20, textSize, text, charset);
    text = "Press n to start new game";
    DrawStringWithSize(screen, SCREEN_WIDTH / 2 - (int)strlen(text) * textSize / 2, screen->h / 2 + BIG_TEXT_SIZE + 20, textSize, text, charset);
}


void renderGameEnd(SDL_Surface* screen, SDL_Surface* charset)
{
    Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    char* text = "GAME ENDED";
    int textSize = BIG_TEXT_SIZE;
    SDL_FillRect(screen, NULL, black);
    DrawStringWithSize(screen, SCREEN_WIDTH / 2 - (int)strlen(text) * textSize / 2, screen->h / 2 - textSize / 2, textSize, text, charset);
    text = "Press esc to exit";
    textSize = BIG_TEXT_SIZE / 4;
    DrawStringWithSize(screen, SCREEN_WIDTH / 2 - (int)strlen(text) * textSize / 2, screen->h / 2 + BIG_TEXT_SIZE - 20, textSize, text, charset);
    text = "Press n to start new game";
    DrawStringWithSize(screen, SCREEN_WIDTH / 2 - (int)strlen(text) * textSize / 2, screen->h / 2 + BIG_TEXT_SIZE + 20, textSize, text, charset);
}


void renderPause(SDL_Surface* screen, SDL_Surface* charset)
{
    Uint32 grey = SDL_MapRGB(screen->format, 0x11, 0x11, 0x11);
    int rectH, rectW, rectX, rectY;
    rectH = BIG_TEXT_SIZE * 3;
    rectW = SCREEN_WIDTH - 2 * 20;
    rectX = 20;
    rectY = SCREEN_HEIGHT / 2 - 40;
    DrawRectangle(screen, rectX, rectY, rectW, rectH, grey, grey);
    char* text = "PAUSED";
    DrawStringWithSize(screen, screen->w / 2 - (int)strlen(text) * BIG_TEXT_SIZE / 2, screen->h / 2, BIG_TEXT_SIZE, text, charset);
    text = "press p to resume";
    DrawStringWithSize(screen, screen->w / 2 - (int)strlen(text) * BIG_TEXT_SIZE / 4, screen->h / 2 + (int)(BIG_TEXT_SIZE * 1.5), BIG_TEXT_SIZE / 2, text, charset);
}


void updateScreen(DisplayData* displayThings)
{
    SDL_UpdateTexture(*displayThings->scrtex, NULL, (*displayThings->screen)->pixels, (*displayThings->screen)->pitch);
    SDL_RenderCopy(*displayThings->renderer, *(displayThings->scrtex), NULL, NULL);
    SDL_RenderPresent(*displayThings->renderer);
}


void ResetGame(RoadData* road, GameStatus* gameStatus, GameData* gameData, double* framesCounter)
{
    *framesCounter = 0;
    gameData->playerPoints = 0;
    gameData->worldTime = 0;
    gameData->livesAmount = 1;
    gameData->infiniteLives = true;
    gameData->lastLifeAdded = 0;
    *(gameData->carPos.x) = SCREEN_WIDTH / 2;
    gameStatus->pause = false;
    gameStatus->gameOver = false;
    gameStatus->end = false;
    road->rectanglesChanged = 0;
    road->width = ROAD_WIDTH;
    road->oldWidth = ROAD_WIDTH;
    road->moveValue = 0;
    road->lines.moveValue = 0;
}


void handleEvents(SDL_Event* event, GameStatus* gameStatus, GameData* gameData, RoadData* road, double* framesCounter)
{
    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_ESCAPE) gameStatus->quit = 1;
            else if (event->key.keysym.sym == SDLK_UP)
            {
                gameData->pointGainValue = HIGH_POINTS;
                gameData->speed = HIGH_SPEED;
            }
            else if (event->key.keysym.sym == SDLK_DOWN) gameData->speed = LOW_SPEED;
            else if (event->key.keysym.sym == SDLK_p) gameStatus->pause = !(gameStatus->pause);
            else if (event->key.keysym.sym == SDLK_LEFT) (*gameData->carPos.x) -= 15;
            else if (event->key.keysym.sym == SDLK_RIGHT) (*gameData->carPos.x) += 15;
            else if (event->key.keysym.sym == SDLK_n) ResetGame(road, gameStatus, gameData, framesCounter);
            else if (event->key.keysym.sym == SDLK_f) gameStatus->end = true;
            break;
        case SDL_KEYUP:
            gameData->pointGainValue = DEFAULT_POINTS;
            if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN) gameData->speed = NORMAL_SPEED;
            break;
        case SDL_QUIT:
            gameStatus->quit = 1;
            break;
        };
    };
}


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
    double timeDelta, framesCounter, timeOne, timeTwo;
    SDL_Event event;

    DisplayData displayThings = {};
    displayThings.window = (SDL_Window**)malloc(sizeof(SDL_Window*));
    displayThings.renderer = (SDL_Renderer**)malloc(sizeof(SDL_Renderer*));
    displayThings.screen = (SDL_Surface**)malloc(sizeof(SDL_Surface*));
    displayThings.scrtex = (SDL_Texture**)malloc(sizeof(SDL_Texture*));
    displayThings.rc = 0;

    LinesData lines = {};
    lines.amount = 9;
    lines.length = 50;
    lines.thickness = 6;
    lines.moveValue = 0;

    RoadData road = {};
    road.width = ROAD_WIDTH;
    road.oldWidth = ROAD_WIDTH;
    road.rectanglesAmount = 10;
    road.rectangleHeight = SCREEN_HEIGHT / road.rectanglesAmount;
    road.rectanglesChanged = 0;
    road.moveValue = 0;
    road.lines = lines;

    Coords carPos = {};
    carPos.x = (int*)malloc(sizeof(int));
    carPos.y = (int*)malloc(sizeof(int));
    *(carPos.x) = SCREEN_WIDTH / 2;
    *(carPos.y) = SCREEN_HEIGHT / 2;

    Bitmaps bitmaps = {};

    GameStatus gameStatus = {};
    gameStatus.gameOver = false;
    gameStatus.pause = false;
    gameStatus.quit = false;
    gameStatus.end = false;

    GameData gameData = {};
    gameData.carPos = carPos;
    gameData.infiniteLives = true;
    gameData.lastLifeAdded = 0;
    gameData.livesAmount = 1;
    gameData.playerPoints = 0;
    gameData.speed = NORMAL_SPEED;
    gameData.worldTime = 0;
    gameData.pointGainValue = DEFAULT_POINTS;

    int errorStatus = prepareScreen(&displayThings);
    if (errorStatus == 1)
    {
        printf("There was a problem with SDL initialization!");
        return 1;
    }

    errorStatus = loadBitmaps(&bitmaps, &displayThings);
    if (errorStatus == 1)
    {
        printf("There was a problem with bitmaps loading!");
        return 1;
    }

    framesCounter = 0;
    timeOne = SDL_GetTicks();

    while (!gameStatus.quit)
    {
        timeTwo = SDL_GetTicks();
        timeDelta = (timeTwo - timeOne) * 0.001; // timeDelta is time between two frames in seconds
        timeOne = timeTwo;

        if (!gameStatus.pause && !gameStatus.gameOver && !gameStatus.end)
        {
            updateGameData(&gameData, timeDelta);
            renderGameFrame(&displayThings, &road, &gameData, &gameStatus, &bitmaps, framesCounter);
        }
        else if (gameStatus.pause && !gameStatus.gameOver && !gameStatus.end) renderPause(*displayThings.screen, bitmaps.charset);
        else if (gameStatus.end) renderGameEnd(*displayThings.screen, bitmaps.charset);
        else renderGameOver(*displayThings.screen, bitmaps.charset);

        updateScreen(&displayThings);

        handleEvents(&event, &gameStatus, &gameData, &road, &framesCounter);

        framesCounter += 1;
    };

    disableGame(bitmaps.charset, &displayThings);
    free(displayThings.renderer);
    free(displayThings.window);
    free(displayThings.screen);
    free(displayThings.scrtex);
    free(carPos.x);
    free(carPos.y);
    return 0;
};