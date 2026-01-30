#include "game.h"
#include "surface.h"
#include "cmath"
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Tmpl8
{
    void Game::Init() {}
    void Game::Shutdown() {}

    Surface tiles("assets/tiles.png");
    
    int spritesheetWidth = 261; //how big is the spritesheet with the tiles
    int tileSize = 64; //how mat pixels big are the tiles
    int spritesheetSpace = 1; //how big is the aerea between 2 sprites in the tile sprite
    int mapHeight = 6; //how may tiles in height is the map
    int mapWidth = 6; //how many tiles in width is the map
    int characterSize = 40; //how many pixels is the character
    int characterCenter = characterSize / 2; //defines the chatrzcter center
    int level = 0; //what level are you on
    int money = 0; //money total
    int mgil = 0; //money gained in level
    bool mb = false; //is the money counter in lvl 11 big (for the flashy animation)
    bool stickUnlocked = false; //is the stickman unlocked (basegame = from level 5)
    int characterState = 0; //what state is the character(0 = cube, 1 = ball, 2 = triangle, 3 = stickman)

    bool isPT = false; //is a transition playing
    int maxFT = 0; //max frames of transition
    int currentFT = 0; //current frame of transition
    Sprite* currentT = 0; //currentanimation
    float Ttimer = 0.0f; //transformation timer
    float TFtime = 1.0f / 60.0f; //transformation frames time
    int targetCS = -1; //targeted character state
    bool TrKeyIsPressed = false; //is a transformation key(c, v, b, n) pressed


    bool eIsPressed = false; //is e pressed
    bool finished = false; //have you completed the game atleast ones
    bool srm = false; //is speedrun mode enabled
    bool srf = false; //speedrunning full game
    bool srl = false; //speedrunning specific level
    std::vector<float> fastestTime = { 9999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999 }; //fastest time on each level

    bool holdingItem = false; // is the player holding an item
    int itemHolding = -1; //what item is the player holding

    int dA = 4; //door amount
    int iA = 2; //item amount

    bool begin = false; //is the level created
    auto startTime = std::chrono::steady_clock::now(); //time started counting
    auto currentTime = std::chrono::steady_clock::now(); //current time
    auto time = std::chrono::duration<float>(currentTime - startTime).count(); //time between started and current time

    std::vector<int> dX; //door x
    std::vector<int> dY; //door y
    std::vector<int> dC; //0 is no criteria, 1-4 is character criteria, 5-10 is key criteria (see doorsprite for order)
    std::vector<bool> dL; //is the door locked
    std::vector<bool> dO; //is the door opened
    std::vector<int> dF; //door frame
    std::vector<bool> dH; //door hidden
    int dFu[11] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40}; //door frames that define an up door
    int dFl[11] = {1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41}; //door frames that define a left door
    int dFd[11] = {2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42}; //door frames that define a down door
    int dFr[11] = {3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43}; //door frames that define a right door

    std::vector<int> iX; //item x
    std::vector<int> iY; //item y
    std::vector<int> iF; //item frame
    std::vector<bool> iPU; //is the item picked up
    std::vector<bool> iU; //is the item used
    std::vector<bool> iH; //is the item hidden

    std::vector<int> tutX = { tileSize * 1 - tileSize, tileSize * 1 - tileSize, tileSize * 4 - tileSize, tileSize * 8 - tileSize, tileSize * 5 - tileSize, tileSize * 1 - tileSize, tileSize * 2 - tileSize/2, tileSize * 9 - tileSize, tileSize * 7 - tileSize, tileSize * 13 - tileSize }; //tutorial text baloon x
    std::vector<int> tutY = { tileSize * 3 - tileSize, tileSize * 4 - tileSize, tileSize * 1 - tileSize, tileSize * 4 - tileSize, tileSize * 7 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 9 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize }; //tutorial text baloon y
    std::vector<bool> tutH = { true, true, true, true, true, true, true, true, true, true }; //is the tutorial text baloon hidden

    //test map
    std::vector<std::string> map = {
         "aax aax aax aax aax aax",
         "aax aa- aa- aa- aa- aax",
         "aax aa- aa- aa- aa- aax",
         "aax aa- aa- aa- aa- aax",
         "aax aa- aa- aa- aa- aax",
         "aax aax aax aax aax aax",
    };

    Sprite character(new Surface("assets/character sprites.png"), 4); //character sprite creation
    int px = (tileSize * 2 - tileSize) + ((tileSize - characterSize) / 2), py = (tileSize * 2 - tileSize) + ((tileSize - characterSize) / 2); //sets the character pos

    Sprite doors(new Surface("assets/doors.png"), 44); //door sprite creation
    Sprite items(new Surface("assets/items.png"), 8); //item sprite creation
    Sprite tutorial(new Surface("assets/tutorial.png"), 10); //tutorial sprite creation
    Sprite tfp(new Surface("assets/thanks for playing.png"), 1); //"thanks for playing" sprite creation
    Sprite lvlbuttons(new Surface("assets/level buttons.png"), 11); //level buttons sprite creation

    //transformation sprite creation
    Sprite CtB(new Surface("assets/cube to ball.png"), 45);
    Sprite CtT(new Surface("assets/cube to triangle.png"), 50);
    Sprite CtS(new Surface("assets/cube to stickfigure.png"), 55);

    Sprite BtC(new Surface("assets/ball to cube.png"), 45);
    Sprite BtT(new Surface("assets/ball to triangle.png"), 35);
    Sprite BtS(new Surface("assets/ball to stickfigure.png"), 55);

    Sprite TtC(new Surface("assets/triangle to cube.png"), 50);
    Sprite TtB(new Surface("assets/triangle to ball.png"), 35);
    Sprite TtS(new Surface("assets/triangle to stickfigure.png"), 55);

    Sprite StC(new Surface("assets/stickfigure to cube.png"), 55);
    Sprite StB(new Surface("assets/stickfigure to ball.png"), 55);
    Sprite StT(new Surface("assets/stickfigure to triangle.png"), 55);


    bool CheckPos(int x, int y)
    {
        int tx = x / tileSize, ty = y / tileSize;
        return map[ty][tx * 4 + 2] != 'x';
    }


    void DrawTile(int tx, int ty, Surface* screen, int x, int y)
    {
        if (x >= screen->GetWidth() - tileSize || x < 0 || y >= screen->GetHeight() - tileSize || y < 0) return;
        Pixel* src = tiles.GetBuffer() + 1 + tx * (tileSize + spritesheetSpace) + (1 + ty * (tileSize + spritesheetSpace)) * spritesheetWidth;
        Pixel* dst = screen->GetBuffer() + x + y * 800;
        for (int i = 0; i < tileSize; i++, src += spritesheetWidth, dst += 800)
            for (int j = 0; j < tileSize; j++)
                dst[j] = src[j];
    }

    void checkItem(int px, int py)
    {
        for (int i = 0; i < iA; i++)
        {
            if (px + characterCenter >= iX[i] && px + characterCenter <= iX[i] + 64 && py + characterCenter >= iY[i] && py + characterCenter <= iY[i] + 64 && iH[i] == false && iU[i] == false)
            {
                if (itemHolding != i)
                {
                    if (iF[i] == 0)
                    {
                        iPU[i] = true;
                        iX[i] = -64;
                        iY[i] = -64;
                        money++;
                        mgil++;
                        return;
                    }
                    else if (iF[i] == 1)
                    {
                        itemHolding = -1;
                        holdingItem = false;
                        iU[i] = true;
                        begin = false;

                        if (srl == true)
                        {
                            if (time < fastestTime[level]) fastestTime[level] = time;
                            level = 12;
                        }
                        else if (srf = true && level == 10)
                        {
                            if (time < fastestTime[0]) fastestTime[0] = time;
                            level = 12;
                        }
                        else
                        {
                            level++;
                        }
                        return;
                    }
                    else if (holdingItem == false)
                    {
                        iPU[i] = true;
                        itemHolding = i;
                        holdingItem = true;
                        return;
                    }
                    else if (holdingItem == true)
                    {
                        // dropping previous item at this item's position
                        int prev = itemHolding;
                        iX[prev] = iX[i];
                        iY[prev] = iY[i];
                        iPU[prev] = false;
                        // picking up new item
                        iPU[i] = true;
                        itemHolding = i;
                        holdingItem = true;
                        return;
                    }
                    
                }
            }
            if (itemHolding == i)
            {
                int prev = itemHolding;
                iX[prev] = floor((px + characterCenter) / tileSize) * tileSize;
                iY[prev] = floor((py + characterCenter) / tileSize) * tileSize;
                iPU[prev] = false;
                holdingItem = false;
                itemHolding = -1;
            }
        }
    }

    bool checkDoor(int nx, int ny)
    {
        for (int i = 0; i < dA; i++)
        {
            if (dC[i] < 5 && dC[i] > 0 && dC[i] != (characterState + 1))
            {
                dL[i] = true;
            }
            else if (dC[i] < 5 && dC[i] > 0 && dC[i] == (characterState + 1))
            {
                dL[i] = false;
            }

            if (itemHolding >=0 && dC[i] >= 5 && dC[i] == (iF[itemHolding] + 3) && dL[i] == true && nx + characterCenter >= dX[i] && nx + characterCenter <= dX[i] + 64 && ny + characterCenter >= dY[i] && ny + characterCenter <= dY[i] + 64)
            {
                dL[i] = false;
                iU[itemHolding] = true;
                holdingItem = false;
                itemHolding = -1;
            }

            //open door when unlocked
            if (dL[i] == false && dO[i] == false)
            {
                for (int j = 0; j < 11; j++)
                {
                    if (dF[i] == dFu[j])
                    {
                        dF[i] = dF[i] + 1;
                        dO[i] = true;
                    }
                    else if (dF[i] == dFl[j])
                    {
                        dF[i] = dF[i] + 1;
                        dO[i] = true;
                    }
                    else if (dF[i] == dFd[j])
                    {
                        dF[i] = dF[i] + 1;
                        dO[i] = true;
                    }
                    else if (dF[i] == dFr[j])
                    {
                        dF[i] = dF[i] - 3;
                        dO[i] = true;
                    }
                }
            }
            //close door when locked
            if (dL[i] == true && dO[i] == true)
            {
                for (int j = 0; j < 11; j++)
                {
                    if (dF[i] == dFu[j])
                    {
                        dF[i] = dF[i] + 3;
                        dO[i] = false;
                    }
                    else if (dF[i] == dFl[j])
                    {
                        dF[i] = dF[i] - 1;
                        dO[i] = false;
                    }
                    else if (dF[i] == dFd[j])
                    {
                        dF[i] = dF[i] - 1;
                        dO[i] = false;
                    }
                    else if (dF[i] == dFr[j])
                    {
                        dF[i] = dF[i] - 1;
                        dO[i] = false;
                    }
                }
            }

            if (dL[i] == true)
            {
                for (int j = 0; j < 11; j++)
                {
                    //doors up
                    if (dF[i] == dFu[j] && nx + characterSize >= dX[i] && nx <= dX[i] + 64 && ny + characterSize >= dY[i] && ny <= dY[i] + 12)
                    {
                        return false;
                    }
                    //doors left
                    else if (dF[i] == dFl[j] && nx + characterSize >= dX[i] && nx <= dX[i] + 12 && ny >= dY[i] && ny <= dY[i] + 64)
                    {
                        return false;
                    }
                    //doors down
                    else if (dF[i] == dFd[j] && nx >= dX[i] && nx <= dX[i] + 64 && ny + characterSize >= dY[i] + 52 && ny <= dY[i] + 64)
                    {
                        return false;
                    }
                    //doors right
                    else if (dF[i] == dFr[j] && nx + characterSize >= dX[i] + 52 && nx <= dX[i] + 64 && ny >= dY[i] && ny <= dY[i] + 64)
                    {
                        return false;
                    }
                }
            }
        }
        if (level == 0 && dL[3] == false) iH[1] = false;
        return true;
    }

    void createLevel(Surface* screen,int startmidX,int startmidY, int plx, int ply)
    {
        if (begin == false)
        {
            if (level == 0)
            {
                px = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 6 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                
                dA = 4;
                iA = 2;

                dX = { tileSize * 3 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 5 - tileSize };
                dY = { tileSize * 4 - tileSize, tileSize * 2 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize };
                dC = { 1, 3, 2, 6 };
                dL = { true, true, true, true };
                dO = { false, false, false, false };
                dF = { 4, 15, 10, 25 };

                iX = { tileSize * 7 - tileSize, tileSize * 3 - tileSize };
                iY = { tileSize * 6 - tileSize, tileSize * 6 - tileSize };
                iF = { 3, 1 };
                iPU = { false, false };
                iU = { false, false };
                iH = { false, true };

                mapHeight = 8;
                mapWidth = 8;
                map = {
                    "bax aax aax aax aax aax aax aax",
                    "bax aax ad- bb- bb- bb- dd- aax",
                    "bax aax ab- aax aax aax ab- aax",
                    "aax aax ab- aax aax aax ab- aax",
                    "aax ad- dg- dd- aax aax ab- aax",
                    "aax bc- aa- cg- bb- bb- cd- aax",
                    "aax bd- cc- cd- aax aax aax aax",
                    "aax aax aax aax aax bax bax bax"
                };
            }

            else if (level == 1)
            {
                px = (tileSize * 5 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 11 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true || srf == true) startTime = std::chrono::steady_clock::now();

                dA = 3;
                iA = 3;

                dX = { tileSize * 2 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize };
                dY = { tileSize * 4 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize };
                dC = { 3, 2, 5 };
                dL = { true, true, true };
                dO = { false, false, false };
                dF = { 12, 10, 20 };

                iX = { tileSize * 2 - tileSize, tileSize * 4 - tileSize, tileSize * 8 - tileSize };
                iY = { tileSize * 2 - tileSize, tileSize * 3 - tileSize, tileSize * 3 - tileSize };
                iF = { 0, 2, 1 };
                iPU = { false, false, false };
                iU = { false, false, false };
                iH = { false, false, false };

                mapHeight = 13;
                mapWidth = 10;
                map = {
                    "aax aax aax bax bax aax aax aax aax aax",
                    "aax de- aax aax aax aax ad- ac- dd- aax",
                    "aax ab- aax de- aax aax bc- aa- dc- aax",
                    "aax ab- aax ab- aax aax bc- cc- cd- aax",
                    "aax bd- bb- dc- aax ad- cd- aax aax aax",
                    "aax aax aax ab- aax ab- aax aax bax bax",
                    "bax bax aax bd- ac- cd- aax bax bax bax",
                    "bax bax aax aax ab- aax aax bax bax bax",
                    "bax bax aax aax ab- aax aax bax bax bax",
                    "bax bax aax ad- aa- dd- aax bax bax bax",
                    "bax bax aax bc- aa- dc- aax bax bax bax",
                    "bax bax aax bd- cc- cd- aax bax bax bax",
                    "bax bax aax aax aax aax aax bax bax bax"
                };
            }

            else if (level == 2)
            {
                px = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 5;
                iA = 5;

                dX = { tileSize * 8 - tileSize, tileSize * 8 - tileSize, tileSize * 8 - tileSize, tileSize * 6 - tileSize, tileSize * 5 - tileSize };
                dY = { tileSize * 3 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize };
                dC = { 7, 2, 10, 3, 8 };
                dL = { true, true, true, true, true };
                dO = { false, false, false, false, false };
                dF = { 31, 11, 43, 15, 33 };

                iX = { tileSize * 9 - tileSize, tileSize * 5 - tileSize, tileSize * 9 - tileSize, tileSize * 9 - tileSize, tileSize * 3 - tileSize };
                iY = { tileSize * 3 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 7 - tileSize };
                iF = { 7, 4, 0, 5, 1 };
                iPU = { false, false, false, false, false };
                iU = { false, false, false, false, false };
                iH = { false, false, false, false, false };

                mapHeight = 9;
                mapWidth = 10;
                map = {
                    "aax aax aax aax aax bax bax bax bax bax",
                    "aax ad- ac- dd- aax aax aax aax aax aax",
                    "aax bc- aa- cg- bb- bb- ac- bb- ce- aax",
                    "aax bd- cc- cd- aax aax ab- aax aax aax",
                    "aax aax aax aax ae- bb- da- bb- ce- aax",
                    "aax ad- ac- dd- aax aax ab- aax aax aax",
                    "aax bc- aa- cg- bb- bb- cc- bb- ce- aax",
                    "aax bd- cc- cd- aax aax aax aax aax aax",
                    "aax aax aax aax aax aax bax bax bax bax"
                };

            }

            else if (level == 3)
            {
                px = (tileSize * 4 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 9;
                iA = 10;

                dX = { tileSize * 4 - tileSize, tileSize * 3 - tileSize, tileSize * 5 - tileSize, tileSize * 4 - tileSize, tileSize * 3 - tileSize, tileSize * 4 - tileSize, tileSize * 5 - tileSize, tileSize * 3 - tileSize, tileSize * 4 - tileSize };
                dY = { tileSize * 5 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 7 - tileSize, tileSize * 8 - tileSize, tileSize * 9 - tileSize, tileSize * 9 - tileSize, tileSize * 10 - tileSize, tileSize * 11 - tileSize };
                dC = { 3, 10, 9, 2, 6, 1, 7, 8, 3 };
                dL = { true, true, true, true, true, true, true, true, true };
                dO = { false, false, false, false, false, false, false, false, false };
                dF = { 12, 41, 39, 8, 25, 4, 31, 33, 12 };

                iX = { tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 6 - tileSize, tileSize * 2 - tileSize, tileSize * 4 - tileSize, //keys
                    tileSize * 8 - tileSize, tileSize * 8 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, //coins
                    tileSize * 7 - tileSize };//diamond
                iY = { tileSize * 6 - tileSize, tileSize * 8 - tileSize, tileSize * 9 - tileSize, tileSize * 10 - tileSize, tileSize * 12 - tileSize, //keys
                    tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 7 - tileSize, tileSize * 5 - tileSize, //coins
                    tileSize * 6 - tileSize }; //diamond
                iF = { 6, 5, 3, 7, 4, 0, 0, 0, 0, 1 };
                iPU = { false, false, false, false, false, false, false, false, false, false };
                iU = { false, false, false, false, false, false, false, false, false, false };
                iH = { false, false, false, false, false, false, false, false, false, false };

                mapHeight = 13;
                mapWidth = 9;
                map = {
                    "bax aax aax aax aax aax bax bax bax",
                    "bax aax ad- ac- dd- aax bax bax bax",
                    "bax aax bc- aa- dc- aax bax bax bax",
                    "bax aax bd- bg- cd- aax aax aax aax",
                    "aax aax aax ab- aax ad- ac- dd- aax",
                    "aax ae- bb- da- bb- ag- aa- dc- aax",
                    "aax aax aax ab- aax bd- cc- cd- aax",
                    "aax ae- bb- dc- aax aax aax aax aax",
                    "aax aax aax bc- bb- ce- aax bax bax",
                    "aax ae- bb- dc- aax aax aax bax bax",
                    "aax aax aax ab- aax bax bax bax bax",
                    "bax bax aax be- aax bax bax bax bax",
                    "bax bax aax aax aax bax bax bax bax"
                };
            }

            else if (level == 4)
            {
                px = (tileSize * 5 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 17 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 18; //18
                iA = 8; //8

                dX = { tileSize * 3 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize, tileSize * 7 - tileSize, tileSize * 8 - tileSize, tileSize * 9 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 11 - tileSize, tileSize * 12 - tileSize, tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 16 - tileSize, tileSize * 17 - tileSize, tileSize * 17 - tileSize, tileSize * 19 - tileSize, tileSize * 20 - tileSize, tileSize * 21 - tileSize };
                dY = { tileSize * 11 - tileSize, tileSize * 14 - tileSize, tileSize * 14 - tileSize, tileSize * 11 - tileSize, tileSize * 14 - tileSize, tileSize * 12 - tileSize, tileSize * 8 - tileSize, tileSize * 14 - tileSize, tileSize * 9 - tileSize, tileSize * 16 - tileSize, tileSize * 8 - tileSize, tileSize * 4 - tileSize, tileSize * 7 - tileSize, tileSize * 9 - tileSize, tileSize * 12 - tileSize, tileSize * 6 - tileSize, tileSize * 5 - tileSize, tileSize * 11 - tileSize };
                dC = { 7, 2, 3, 5, 1, 3, 1, 2, 2, 1, 6, 3, 2, 1, 2, 1, 8, 3 };
                dL = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
                dO = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                dF = { 28, 9, 13, 20, 5, 13, 6, 11, 9, 4, 24, 15, 10, 7, 9, 5, 32, 13 };

                iX = { tileSize * 3 - tileSize, tileSize * 7 - tileSize, tileSize * 12 - tileSize, tileSize * 23 - tileSize, tileSize * 2 - tileSize, tileSize * 10 - tileSize, tileSize * 14 - tileSize, tileSize * 20 - tileSize };
                iY = { tileSize * 8 - tileSize, tileSize * 10 - tileSize, tileSize * 18 - tileSize, tileSize * 11 - tileSize, tileSize * 14 - tileSize, tileSize * 6 - tileSize, tileSize * 12 - tileSize, tileSize * 3 - tileSize };
                iF = { 2, 3, 4, 5, 0, 0, 0, 1 };
                iPU = { false, false, false, false, false, false, false, false };
                iU = { false, false, false, false, false, false, false, false };
                iH = { false, false, false, false, false, false, false, false };

                mapHeight = 19;
                mapWidth = 24;
                map = {
                    "bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax aax aax aax aax aax bax bax",
                    "bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax aax ad- ac- dd- aax bax bax",
                    "bax bax bax bax bax bax bax bax bax bax bax aax aax aax aax aax aax aax bc- aa- dc- aax bax bax",
                    "bax bax bax bax bax bax bax bax bax bax bax aax ad- bb- bb- dd- aax aax bd- bg- cd- aax bax bax",
                    "bax bax bax bax bax bax bax bax aax aax aax aax ab- aax aax ab- aax aax aax ab- aax aax bax bax",
                    "bax bax bax bax bax bax bax bax aax de- aax aax ab- aax aax bc- bb- bb- bb- cd- aax bax bax bax",
                    "bax aax aax aax bax bax bax bax aax ab- aax aax ab- aax aax ab- aax aax aax aax aax bax bax bax",
                    "bax aax de- aax bax bax bax bax aax ab- aax aax ab- aax aax ab- aax aax aax aax aax bax bax bax",
                    "bax aax ab- aax bax aax aax aax aax bc- bb- bb- cd- aax aax bd- bb- bb- bb- dd- aax bax bax bax",
                    "bax aax ab- aax bax aax de- aax aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax",
                    "bax aax ab- aax aax aax ab- aax aax ab- aax bax aax aax aax aax aax aax aax bc- bb- bb- ce- aax",
                    "bax aax bd- bb- ac- bb- cc- bb- bb- cd- aax bax aax ae- bb- bb- bb- bb- bb- cd- aax aax aax aax",
                    "aax aax aax aax ab- aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax bax bax bax",
                    "aax ae- bb- bb- da- bb- bb- bb- bb- bb- bb- dd- aax bax bax bax bax bax bax bax bax bax bax bax",
                    "aax aax aax aax ab- aax aax aax aax aax aax ab- aax bax bax bax bax bax bax bax bax bax bax bax",
                    "bax bax aax ad- dg- dd- aax bax bax bax aax ab- aax bax bax bax bax bax bax bax bax bax bax bax",
                    "bax bax aax bc- aa- dc- aax bax bax bax aax ab- aax bax bax bax bax bax bax bax bax bax bax bax",
                    "bax bax aax bd- cc- cd- aax bax bax bax aax be- aax bax bax bax bax bax bax bax bax bax bax bax",
                    "bax bax aax aax aax aax aax bax bax bax aax aax aax bax bax bax bax bax bax bax bax bax bax aax"
                };
            }

            else if (level == 5)
            {
                px = (tileSize * 7 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 10 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(1);
                characterState = 1;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                stickUnlocked = true;

                dA = 9;
                iA = 27;

                dX = { tileSize * 3 - tileSize, tileSize * 3 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 7 - tileSize, tileSize * 9 - tileSize, tileSize * 9 - tileSize, tileSize * 9 - tileSize, tileSize * 10 - tileSize };
                dY = { tileSize * 3 - tileSize, tileSize * 17 - tileSize, tileSize * 10 - tileSize, tileSize * 8 - tileSize, tileSize * 12 - tileSize, tileSize * 5 - tileSize, tileSize * 10 - tileSize, tileSize * 15 - tileSize, tileSize * 10 - tileSize };
                dC = { 10, 8, 4, 1, 3, 7, 9, 6, 5 };
                dL = { true, true, true, true, true, true, true, true, true };
                dO = { false, false, false, false, false, false, false, false, false };
                dF = { 42, 32, 19, 6, 12, 31, 39, 27, 23 };

                iX = { tileSize * 3 - tileSize, tileSize * 3 - tileSize, tileSize * 7 - tileSize, tileSize * 7 - tileSize, tileSize * 11 - tileSize, tileSize * 11 - tileSize, //keys
                    tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 4 - tileSize, tileSize * 4 - tileSize, tileSize * 4 - tileSize, tileSize * 4 - tileSize, tileSize * 4 - tileSize, tileSize * 4 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 12 - tileSize, tileSize * 12 - tileSize, tileSize * 12 - tileSize, tileSize * 12 - tileSize, //coins
                    tileSize * 12 - tileSize }; //diamond
                iY = { tileSize * 5 - tileSize, tileSize * 15 - tileSize, tileSize * 5 - tileSize, tileSize * 15 - tileSize, tileSize * 5 - tileSize, tileSize * 15 - tileSize, //keys
                    tileSize * 4 - tileSize, tileSize * 6 - tileSize, tileSize * 9 - tileSize, tileSize * 11 - tileSize, tileSize * 14 - tileSize, tileSize * 16 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize, tileSize * 9 - tileSize, tileSize * 11 - tileSize, tileSize * 14 - tileSize, tileSize * 16 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize, tileSize * 14 - tileSize, tileSize * 16 - tileSize, tileSize * 4 - tileSize, tileSize * 6 - tileSize, tileSize * 14 - tileSize, tileSize * 16 - tileSize, //coins
                    tileSize * 10 - tileSize }; // diamond
                iF = { 3, 6, 5, 7, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
                iPU = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                iU = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                iH = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

                mapHeight = 19;
                mapWidth = 14;
                map = {
                    "bax aax aax aax aax aax aax aax bax bax bax bax bax bax",
                    "bax aax ad- bb- bb- bb- dd- aax bax bax bax bax bax bax",
                    "aax aax ab- aax aax aax ab- aax aax aax aax aax aax bax",
                    "aax ad- dg- dd- aax ad- dg- dd- aax ad- ac- dd- aax bax",
                    "aax bc- aa- dc- aax bc- aa- cg- bb- ag- aa- dc- aax bax",
                    "aax bd- cc- cd- aax bd- bg- cd- aax bd- cc- cd- aax bax",
                    "aax aax aax aax aax aax ab- aax aax aax aax aax aax bax",
                    "aax aax aax aax aax aax ab- aax aax aax aax aax aax aax",
                    "aax ad- ac- dd- aax ad- dg- dd- aax aax ad- ac- dd- aax",
                    "aax bc- aa- cg- bb- ag- aa- cg- bb- bb- ag- aa- dc- aax",
                    "aax bd- cc- cd- aax bd- bg- cd- aax aax bd- cc- cd- aax",
                    "aax aax aax aax aax aax ab- aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax ab- aax aax aax aax aax aax bax",
                    "aax ad- ac- dd- aax ad- dg- dd- aax ad- ac- dd- aax bax",
                    "aax bc- aa- dc- aax bc- aa- cg- bb- ag- aa- dc- aax bax",
                    "aax bd- bg- cd- aax bd- bg- cd- aax bd- cc- cd- aax bax",
                    "aax aax ab- aax aax aax ab- aax aax aax aax aax aax bax",
                    "bax aax bd- bb- bb- bb- cd- aax bax bax bax bax bax bax",
                    "bax aax aax aax aax aax aax aax bax bax bax bax bax bax"
                };

            }

            else if (level == 6)
            {
                px = (tileSize * 5 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 5 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 10;
                iA = 8;

                dX = { tileSize * 7 - tileSize, tileSize * 7 - tileSize, tileSize * 8 - tileSize, tileSize * 9 - tileSize, tileSize * 10 - tileSize, tileSize * 11 - tileSize, tileSize * 12 - tileSize, tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 15 - tileSize };
                dY = { tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize, tileSize * 5 - tileSize };
                dC = { 4, 6, 10, 3, 1, 9, 8, 7, 2, 5 };
                dL = { true, true, true, true, true, true, true, true, true, true };
                dO = { false, false, false, false, false, false, false, false, false, false };
                dF = { 17, 27, 43, 15, 7, 39, 35, 31, 11, 23 };

                iX = { tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 17 - tileSize };
                iY = { tileSize * 2 - tileSize, tileSize * 3 - tileSize, tileSize * 4 - tileSize, tileSize * 5 - tileSize, tileSize * 6 - tileSize, tileSize * 7 - tileSize, tileSize * 8 - tileSize, tileSize * 5 - tileSize };
                iF = { 2, 0, 7, 3, 6, 4, 5, 1 };
                iPU = { false, false, false, false, false, false, false, false };
                iU = { false, false, false, false, false, false, false, false };
                iH = { false, false, false, false, false, false, false, false };

                mapHeight = 9;
                mapWidth = 19;
                map = {
                    "aax aax aax aax aax aax bax bax bax bax bax bax bax bax bax bax bax bax bax",
                    "aax ad- bb- bb- dd- aax bax bax bax bax bax bax bax bax bax bax bax bax bax",
                    "aax ab- aax aax ab- aax aax bax bax bax bax bax bax bax aax aax aax aax aax",
                    "aax ab- aax ad- dg- dd- aax aax aax aax aax aax aax aax aax ad- ac- dd- aax",
                    "aax ab- aax bc- aa- cg- bb- bb- bb- bb- bb- bb- bb- bb- bb- ag- aa- dc- aax",
                    "aax ab- aax bd- bg- cd- aax aax aax aax aax aax aax aax aax bd- cc- cd- aax",
                    "aax ab- aax aax ab- aax aax bax bax bax bax bax bax bax aax aax aax aax aax",
                    "aax bd- bb- bb- cd- aax bax bax bax bax bax bax bax bax bax bax bax bax bax",
                    "aax aax aax aax aax aax bax bax bax bax bax bax bax bax bax bax bax bax bax"
                };

            }

            else if (level == 7)
            {
                px = (tileSize * 11 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 15;
                iA = 9;

                dX = { tileSize * 4 - tileSize, tileSize * 4 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 8 - tileSize, tileSize * 9 - tileSize, tileSize * 9 - tileSize, tileSize * 11 - tileSize, tileSize * 11 - tileSize, tileSize * 13 - tileSize, tileSize * 13 - tileSize, tileSize * 13 - tileSize, tileSize * 17 - tileSize, tileSize * 18 - tileSize, tileSize * 18 - tileSize };
                dY = { tileSize * 4 - tileSize, tileSize * 10 - tileSize, tileSize * 7 - tileSize, tileSize * 7 - tileSize, tileSize * 14 - tileSize, tileSize * 7 - tileSize, tileSize * 12 - tileSize, tileSize * 9 - tileSize, tileSize * 11 - tileSize, tileSize * 7 - tileSize, tileSize * 12 - tileSize, tileSize * 15 - tileSize, tileSize * 7 - tileSize, tileSize * 4 - tileSize, tileSize * 10 - tileSize };
                dC = { 2, 1, 4, 5, 3, 6, 8, 9, 1, 6, 7, 10, 2, 4, 3};
                dL = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
                dO = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                dF = { 9, 5, 17, 21, 14, 25, 33, 38, 6, 27, 31, 41, 11, 19, 15 };

                iX = { tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 4 - tileSize, tileSize * 11 - tileSize, tileSize * 18 - tileSize, tileSize * 20 - tileSize, tileSize * 20 - tileSize, tileSize * 9 - tileSize, tileSize * 11 - tileSize };
                iY = { tileSize * 6 - tileSize, tileSize * 8 - tileSize, tileSize * 7 - tileSize, tileSize * 7 - tileSize, tileSize * 7 - tileSize, tileSize * 6 - tileSize, tileSize * 8 - tileSize, tileSize * 15 - tileSize, tileSize * 15 - tileSize };
                iF = { 4, 5, 7, 3, 2, 3, 6, 0, 1 };
                iPU = { false, false, false, false, false, false, false, false, false };
                iU = { false, false, false, false, false, false, false, false, false };
                iH = { false, false, false, false, false, false, false, false, false };

                mapHeight = 17;
                mapWidth = 21;
                map = {
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax aax aax ad- ac- dd- aax aax aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax aax aax bc- aa- dc- aax aax aax aax aax aax aax aax aax",
                    "aax ad- bb- bb- bb- dd- aax aax aax bd- bg- cd- aax aax aax ad- bb- bb- bb- dd- aax",
                    "aax ab- aax aax aax ab- aax aax aax aax ab- aax aax aax aax ab- aax aax aax ab- aax",
                    "aax be- aax aax aax ab- aax aax aax ad- dg- dd- aax aax aax ab- aax aax aax be- aax",
                    "aax aax aax ae- bb- da- bb- bb- bb- ag- aa- cg- bb- bb- bb- da- bb- ce- aax aax aax",
                    "aax de- aax aax aax ab- aax aax aax bd- bg- cd- aax aax aax ab- aax aax aax de- aax",
                    "aax ab- aax aax aax ab- aax aax aax aax ab- aax aax aax aax ab- aax aax aax ab- aax",
                    "aax bd- bb- bb- bb- cd- aax aax aax aax ab- aax aax aax aax bd- bb- bb- bb- cd- aax",
                    "aax aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax ad- bb- bb- cc- bb- bb- dd- aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax ab- aax aax aax aax aax ab- aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax ab- aax ad- ac- dd- aax ab- aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax bd- ce- bcx aa- cg- bb- cd- aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax aax aax bd- cc- cd- aax aax aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
                };

            }

            else if (level == 8)
            {
                px = (tileSize * 6 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 30;
                iA = 34;

                dX = { tileSize * 5 - tileSize, tileSize * 7 - tileSize, //red
                    tileSize * 4 - tileSize, tileSize * 6 - tileSize, tileSize * 8 - tileSize, //blue
                    tileSize * 3 - tileSize, tileSize * 5 - tileSize, tileSize * 7 - tileSize, tileSize * 9 - tileSize, //purple
                    tileSize * 15 - tileSize, tileSize * 17 - tileSize, tileSize * 19 - tileSize, tileSize * 21 - tileSize, tileSize * 23 - tileSize, //yellow
                    tileSize * 14 - tileSize, tileSize * 16 - tileSize, tileSize * 18 - tileSize, tileSize * 20 - tileSize, tileSize * 22 - tileSize, tileSize * 24 - tileSize, //white
                    tileSize * 13 - tileSize, tileSize * 15 - tileSize, tileSize * 17 - tileSize, tileSize * 19 - tileSize, tileSize * 21 - tileSize, tileSize * 23 - tileSize, tileSize * 25 - tileSize, //black
                    tileSize * 8 - tileSize, tileSize * 10 - tileSize, tileSize * 11 - tileSize }; //secret
                dY = { tileSize * 10 - tileSize, tileSize * 10 - tileSize, //red
                    tileSize * 17 - tileSize, tileSize * 17 - tileSize, tileSize * 17 - tileSize, //blue
                    tileSize * 24 - tileSize, tileSize * 24 - tileSize, tileSize * 24 - tileSize, tileSize * 24 - tileSize, //purple
                    tileSize * 20 - tileSize, tileSize * 20 - tileSize, tileSize * 20 - tileSize, tileSize * 20 - tileSize, tileSize * 20 - tileSize, //yellow
                    tileSize * 13 - tileSize, tileSize * 13 - tileSize, tileSize * 13 - tileSize, tileSize * 13 - tileSize, tileSize * 13 - tileSize, tileSize * 13 - tileSize, //white
                    tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, //black
                    tileSize * 3 - tileSize, tileSize * 15 - tileSize, tileSize * 22 - tileSize }; //secret
                dC = { 5, 5, 6, 6, 6, 8, 8, 8, 8, 7, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 4, 2, 3 };
                dL = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
                dO = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                dH = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true };
                dF = { 22, 22, 26, 26, 26, 34, 34, 34, 34, 28, 28, 28, 28, 28, 40, 40, 40, 40, 40, 40, 36, 36, 36, 36, 36, 36, 36, 17, 9, 13 };

                iX = { tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 6 - tileSize, tileSize * 19 - tileSize, tileSize * 19 - tileSize, tileSize * 19 - tileSize, //keys
                    tileSize * 5 - tileSize, tileSize * 11 - tileSize, tileSize * 16 - tileSize, tileSize * 19 - tileSize, tileSize * 27 - tileSize, tileSize * 28 - tileSize, tileSize * 28 - tileSize, tileSize * 28 - tileSize, tileSize * 28 - tileSize, //coins
                    tileSize * 28 - tileSize, //diamond
                    tileSize * 12 - tileSize, tileSize * 13 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 10 - tileSize, tileSize * 11 - tileSize, tileSize * 11 - tileSize, tileSize * 11 - tileSize, tileSize * 12 - tileSize, tileSize * 12 - tileSize }; //secret
                iY = { tileSize * 8 - tileSize, tileSize * 15 - tileSize, tileSize * 22 - tileSize, tileSize * 8 - tileSize, tileSize * 15 - tileSize, tileSize * 22 - tileSize, //keys
                    tileSize * 29 - tileSize, tileSize * 29 - tileSize, tileSize * 29 - tileSize, tileSize * 27 - tileSize, tileSize * 2 - tileSize, tileSize * 6 - tileSize, tileSize * 11 - tileSize, tileSize * 15 - tileSize, tileSize * 20 - tileSize, //coins
                    tileSize * 27 - tileSize, //diamond
                    tileSize * 12 - tileSize, tileSize * 2 - tileSize, tileSize * 2 - tileSize, tileSize * 3 - tileSize, tileSize * 4 - tileSize, tileSize * 5 - tileSize, tileSize * 6 - tileSize, tileSize * 7 - tileSize, tileSize * 8 - tileSize, tileSize * 9 - tileSize, tileSize * 10 - tileSize, tileSize * 11 - tileSize, tileSize * 12 - tileSize, tileSize * 2 - tileSize, tileSize * 11 - tileSize, tileSize * 12 - tileSize, tileSize * 2 - tileSize, tileSize * 11 - tileSize }; //secret
                iF = { 2, 3, 5, 6, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //visible
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0 }; //secret
                iPU = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                iU = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                iH = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };

                mapHeight = 30;
                mapWidth = 30;
                map = {
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                    "aax aax aax aax ad- ac- dd- aax aax aax aax aax aax aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax",
                    "aax aax aax aax bc- aa- dc- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                    "aax aax aax aax bd- bg- cd- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                    "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                    "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                    "aax aax aax ad- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax",
                    "aax aax aax bc- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax",
                    "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- ccx cc- bg- cc- ccx cc- ccx cc- ccx cc- ccx cc- cd- aax ab- aax aax",
                    "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                    "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                    "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                    "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                    "aax aax ad- ac- acx ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax ab- aax aax",
                    "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax",
                    "aax aax bd- bg- cc- bg- cc- bg- cd- aax aax aax bd- cc- ccx cc- ccx cc- bg- cc- ccx cc- ccx cc- cd- aax aax ab- aax aax",
                    "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                    "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                    "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                    "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                    "aax ad- ac- acx ac- acx ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax aax ab- aax aax",
                    "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax",
                    "aax bd- bg- cc- bg- cc- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- cc- bg- cc- cc- cc- cc- cd- aax aax aax ab- aax aax",
                    "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax aax ab- aax aax",
                    "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax aax ab- aax aax",
                    "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax ad- dg- dd- aax",
                    "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax bc- aa- dc- aax",
                    "aax aax acx aax ab- aax acx aax acx aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax bd- cc- cd- aax",
                    "aax aax aax aax bd- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- cd- aax aax aax aax aax aax aax aax aax aax aax",
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
                };

            }

            else if (level == 9)
            {
                px = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 3;
                iA = 28;

                dX = { tileSize * 24 - tileSize, tileSize * 28 - tileSize, tileSize * 28 - tileSize };
                dY = { tileSize * 17 - tileSize, tileSize * 25 - tileSize, tileSize * 26 - tileSize };
                dC = { 10, 6, 5 };
                dL = { true, true, true };
                dO = { false, false, false };
                dF = { 40, 26, 22 };

                iX = { tileSize * 14 - tileSize, tileSize * 27 - tileSize, tileSize * 29 - tileSize, //keys
                    tileSize * 22 - tileSize, tileSize * 22 - tileSize, tileSize * 22 - tileSize, tileSize * 22 - tileSize, tileSize * 23 - tileSize, tileSize * 23 - tileSize, tileSize * 23 - tileSize, tileSize * 23 - tileSize, tileSize * 24 - tileSize, tileSize * 24 - tileSize, tileSize * 24 - tileSize, tileSize * 24 - tileSize, tileSize * 25 - tileSize, tileSize * 25 - tileSize, tileSize * 25 - tileSize, tileSize * 25 - tileSize, tileSize * 26 - tileSize, tileSize * 26 - tileSize, tileSize * 26 - tileSize, tileSize * 26 - tileSize, tileSize * 27 - tileSize, tileSize * 27 - tileSize, tileSize * 27 - tileSize, tileSize * 27 - tileSize, //coins
                    tileSize * 28 - tileSize }; //diamond
                iY = { tileSize * 25 - tileSize, tileSize * 10 - tileSize, tileSize * 6 - tileSize, //keys
                    tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 15 - tileSize, tileSize * 16 - tileSize, tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 15 - tileSize, tileSize * 16 - tileSize, tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 15 - tileSize, tileSize * 16 - tileSize, tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 15 - tileSize, tileSize * 16 - tileSize, tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 15 - tileSize, tileSize * 16 - tileSize, tileSize * 13 - tileSize, tileSize * 14 - tileSize, tileSize * 15 - tileSize, tileSize * 16 - tileSize, 
                    tileSize * 28 - tileSize};
                iF = { 3, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
                iPU = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                iU = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
                iH = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

                mapHeight = 30;
                mapWidth = 30;
                map = {
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                    "aax ad- ac- dd- aax aax aax aax ad- bb- bb- bb- bb- ac- bb- bb- bb- bb- bb- dd- aax ad- bb- bb- bb- bb- bb- bb- dd- aax",
                    "aax bc- aa- cg- bb- dd- aax aax ab- aax aax aax aax ab- aax aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax",
                    "aax bd- bg- cd- aax bd- bb- bb- cc- bb- bb- dd- aax ab- aax aax aax aax aax ab- aax ab- aax ad- bb- bb- dd- aax ab- aax",
                    "aax aax ab- aax aax aax aax aax aax aax aax be- aax bd- bb- bb- dd- aax aax bc- bb- cd- aax ab- aax aax ab- aax ab- aax",
                    "aax aax ab- aax aax aax aax aax aax de- aax aax aax aax aax aax ab- aax aax ab- aax aax aax ab- aax aax ab- aax be- aax",
                    "aax ad- cc- bb- ac- bb- bb- dd- aax bd- dd- aax bax bax bax aax ab- aax aax ab- aax ad- bb- dc- aax aax ab- aax aax aax",
                    "aax ab- aax aax ab- aax aax ab- aax aax ab- aax aax aax aax aax bc- bb- bb- dc- aax ab- aax ab- aax aax bd- bb- dd- aax",
                    "aax ab- aax aax ab- aax aax bd- bb- bb- dc- aax ad- bb- bb- bb- dc- aax aax ab- aax ab- aax ab- aax aax aax aax ab- aax",
                    "aax ab- aax aax ab- aax aax aax aax aax ab- aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ad- ce- aax ab- aax",
                    "aax bd- ac- bb- cd- aax de- aax aax aax ab- aax ab- aax aax aax bc- ac- ac- dc- aax be- aax bd- bb- cd- aax aax ab- aax",
                    "aax aax ab- aax aax aax ab- aax ad- bb- cd- aax bd- bb- ce- aax bc- aa- aa- dc- aax aax aax aax aax aax aax aax ab- aax",
                    "aax aax ab- aax ad- bb- cd- aax ab- aax aax aax aax aax aax aax bc- aa- aa- dc- aax ad- ac- ac- ac- ac- dd- aax ab- aax",
                    "aax aax ab- aax ab- aax aax aax ab- aax aax aax ad- ac- bb- bb- cc- bg- cc- dc- aax bc- aa- aa- aa- aa- dc- aax ab- aax",
                    "aax aax bd- bb- cd- aax ae- bb- cc- bb- dd- aax bd- cd- aax aax aax ab- aax ab- aax bc- aa- aa- aa- aa- dc- aax ab- aax",
                    "aax aax aax aax aax aax aax aax aax aax ab- aax aax aax aax de- aax ab- aax ab- aax bd- cc- bg- cc- cc- cd- aax ab- aax",
                    "aax ad- bb- bb- bb- bb- bb- bb- bb- bb- cc- bb- bb- dd- aax bd- bb- dc- aax ab- aax aax aax ab- aax aax aax aax ab- aax",
                    "aax ab- aax aax aax aax aax aax aax aax aax aax aax ab- aax aax aax ab- aax bd- bb- dd- aax bd- bb- bb- dd- aax ab- aax",
                    "aax bc- bb- bb- bb- bb- bb- bb- bb- ac- bb- bb- bb- cc- bb- dd- aax ab- aax aax aax ab- aax aax aax aax ab- aax ab- aax",
                    "aax ab- aax aax aax aax aax aax aax ab- aax aax aax aax aax ab- aax ab- aax de- aax bd- bb- bb- bb- bb- cd- aax ab- aax",
                    "aax ab- aax ad- bb- bb- bb- dd- aax ab- aax ae- bb- dd- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax ab- aax",
                    "aax ab- aax ab- aax aax aax ab- aax ab- aax aax aax ab- aax ab- aax be- aax ab- aax aax ad- bb- bb- bb- bb- bb- cd- aax",
                    "aax ab- aax ab- aax ad- bb- cd- aax ab- aax ad- bb- cd- aax ab- aax aax aax ab- aax aax ab- aax aax aax aax aax aax aax",
                    "aax ab- aax ab- aax ab- aax aax aax ab- aax ab- aax aax aax bd- bb- ac- bb- da- bb- bb- dc- aax ad- bb- bb- dd- aax aax",
                    "aax ab- aax ab- aax ab- aax ad- bb- dc- aax bc- bb- ce- aax aax aax ab- aax ab- aax aax ab- aax ab- aax aax ab- aax aax",
                    "aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax ab- aax ab- aax aax ab- aax ab- aax aax ab- aax aax",
                    "aax bd- bb- cd- aax bd- bb- cd- aax ab- aax ab- aax ad- bb- bb- bb- cd- aax ab- aax ad- cd- aax ab- aax ad- dg- dd- aax",
                    "aax aax aax aax aax aax aax aax aax ab- aax ab- aax ab- aax aax aax aax aax ab- aax ab- aax aax ab- aax bc- aa- dc- aax",
                    "aax ae- bb- bb- bb- bb- bb- bb- bb- cc- bb- cd- aax bd- bb- bb- bb- ce- aax be- aax bd- bb- bb- cd- aax bd- cc- cd- aax",
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
                };

            }

            else if (level == 10)
            {
                px = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 3 - tileSize) + ((tileSize - characterSize) / 2);
                character.SetFrame(0);
                characterState = 0;
                mgil = 0;
                holdingItem = false;
                itemHolding = -1;

                if (srl == true) startTime = std::chrono::steady_clock::now();

                dA = 0;
                iA = 5;

                iX = { tileSize * 27 - tileSize, tileSize * 27 - tileSize, tileSize * 29 - tileSize, tileSize * 29 - tileSize, tileSize * 28 - tileSize };
                iY = { tileSize * 2 - tileSize, tileSize * 4 - tileSize, tileSize * 2 - tileSize, tileSize * 4 - tileSize, tileSize * 3 - tileSize };
                iF = { 0, 0, 0, 0, 1 };
                iPU = { false, false, false, false, false };
                iU = { false, false, false, false, false };
                iH = { false, false, false, false, false };

                mapHeight = 5;
                mapWidth = 30;
                map = {
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                    "aax ad- ac- dd- aax ad- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- dd- aax ad- ac- dd- aax",
                    "aax bc- aa- cg- bb- ag- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- cg- bb- ag- aa- dc- aax",
                    "aax bd- cc- cd- aax bd- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax bd- cc- cd- aax",
                    "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
                };

            }
            else if (level == 11) //end menu
            {
                px = (tileSize * 1 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 1 - tileSize) + ((tileSize - characterSize) / 2);
                mgil = 0;
                finished = true;
                holdingItem = false;
                itemHolding = -1;
                srm = false;
                srf = false;
                srl = false;

                dA = 0;
                iA = 0;

                mapHeight = 1;
                mapWidth = 1;
                map = { "bax" };
            }
            else if (level == 12) //times speedrun mode
            {
                px = (tileSize * 1 - tileSize) + ((tileSize - characterSize) / 2);
                py = (tileSize * 1 - tileSize) + ((tileSize - characterSize) / 2);
                mgil = 0;
                finished = true;
                holdingItem = false;
                itemHolding = -1;
                srm = false;
                srf = false;
                srl = false;

                dA = 0;
                iA = 0;

                mapHeight = 1;
                mapWidth = 1;
                map = { "bax" };
            }

            begin = true;
        }
        
        if (level == 7 && px + characterCenter >= tileSize * 8 - tileSize && px + characterCenter <= tileSize * 9 && py + characterCenter >= tileSize * 14 - tileSize && py + characterCenter <= tileSize * 15)
        {
            map[14] = "aax aax aax aax aax aax aax bd- ce- bcx aa- aa- bb- cd- aax aax aax aax aax aax aax";
        }
        else if (level == 7)
        {
            map[14] = "aax aax aax aax aax aax aax bd- cex bc- aa- aa- bb- cd- aax aax aax aax aax aax aax";
        }

        if (level == 8)
        {
            for (int i = 0; i < dA; i++)
            {
                if (dL[1] == false)
                {
                    map[12] = "aax aax aax aax abx aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[13] = "aax aax ad- ac- ac- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax ab- aax aax";
                }
                if (dL[4] == false)
                {
                    map[19] = "aax aax aax abx aax abx aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax";
                    map[20] = "aax ad- ac- ac- ac- ac- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax aax ab- aax aax";
                }
                if (dL[11] == false)
                {
                    map[15] = "aax aax bd- bg- cc- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- cc- cc- bg- cc- cc- cc- cc- cc- cd- aax aax ab- aax aax";
                    map[16] = "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax abx aax abx aax ab- aax abx aax abx aax aax aax aax ab- aax aax";
                }
                if (dL[15] == false)
                {
                    map[8] = "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    map[9] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                }

                if (dL[20] == false)
                {
                    map[1] = "aax aax aax aax ad- ac- dd- aax aax ad- bb- bb- dd- aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    map[2] = "aax aax aax aax bc- aa- dc- aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[3] = "aax aax aax aax bd- bg- cd- aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[4] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[5] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[6] = "aax aax aax ad- ac- dg- ac- dd- aax ab- aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    map[7] = "aax aax aax bc- aa- aa- aa- dc- aax ab- aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    map[8] = "aax aax aax bd- bg- cc- bg- cd- aax ab- aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    map[9] = "aax aax aax aax ab- aax ab- aax aax ab- aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                    map[10] = "aax aax aax aax ab- aax ab- aax aax bc- ac- dd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[11] = "aax aax aax aax ab- aax ab- aax aax bd- cc- cd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { iH[j] = false; }
                }
                if (dL[27] == false)
                {
                    dH[27] = false;
                    map[1] = "aax aax aax aax ad- ac- dd- aax aax ad- bb- bb- dd- aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    map[2] = "aax aax aax aax bc- aa- cg- bb- bb- dc- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[3] = "aax aax aax aax bd- bg- cd- aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[4] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[5] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[6] = "aax aax aax ad- ac- dg- ac- dd- aax ab- aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    map[7] = "aax aax aax bc- aa- aa- aa- dc- aax ab- aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    map[8] = "aax aax aax bd- bg- cc- bg- cd- aax ab- aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    map[9] = "aax aax aax aax ab- aax ab- aax aax ab- aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                    map[10] = "aax aax aax aax ab- aax ab- aax aax bc- ac- dd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[11] = "aax aax aax aax ab- aax ab- aax aax bd- cc- cd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { iH[j] = false; }
                    if (dL[20] == true) dF[20] = 38;
                }
                if (dL[28] == false)
                {
                    dH[28] = false;
                    map[14] = "aax aax bc- aa- aa- aa- aa- aa- cg- bb- bb- bb- ag- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                }
                else if(dL[28] == true)
                {
                    dH[28] = true;
                    map[14] = "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                }
                if (dL[29] == false)
                {
                    dH[29] = false;
                    map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- cg- bb- bb- bb- ag- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                }
                else if(dL[29] == true)
                {
                    dH[29] = true;
                    map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                }
                if (dL[20] == true && dL[27] == true && dL[28] == true && dL[29] == true && dL[15] == false)
                {
                    dH[27] = true, dH[28] = true, dH[29] = true;
                    dL[27] = true, dL[28] = true, dL[29] = true;
                    map[1] = "aax aax aax aax ad- ac- dd- aax aax aax aax aax aax aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    map[2] = "aax aax aax aax bc- aa- dc- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[3] = "aax aax aax aax bd- bg- cd- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[4] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[5] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[6] = "aax aax aax ad- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    map[7] = "aax aax aax bc- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    map[8] = "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    map[9] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                    map[10] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[11] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[14] = "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                    map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { iH[j] = true; }
                    if (dL[20] == true) dF[20] = 36;
                }
                if(dL[20] == true && dL[27] == true && dL[28] == true && dL[29] == true && dL[15] == true)
                {
                    dH[27] = true, dH[28] = true, dH[29] = true;
                    dL[27] = true, dL[28] = true, dL[29] = true;
                    map[1] = "aax aax aax aax ad- ac- dd- aax aax aax aax aax aax aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    map[2] = "aax aax aax aax bc- aa- dc- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[3] = "aax aax aax aax bd- bg- cd- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[4] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[5] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    map[6] = "aax aax aax ad- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    map[7] = "aax aax aax bc- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    map[8] = "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- ccx cc- bg- cc- ccx cc- ccx cc- ccx cc- ccx cc- cd- aax ab- aax aax";
                    map[9] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[10] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[11] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    map[14] = "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                    map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { iH[j] = true; }
                    if (dL[20] == true) dF[20] = 36;
                }
                if (dL[27] == true) dH[27] = true;
            }
            checkDoor(px, py);
        }

        for (int y = 0; y < mapHeight; y++)
            for (int x = 0; x < mapWidth; x++)
            {
                int tx = map[y][x * 4] - 'a';
                int ty = map[y][x * 4 + 1] - 'a';
                DrawTile(tx, ty, screen, x * tileSize - plx + startmidX, y * tileSize - ply + startmidY);
            }

        //doors creation
        for (int i = 0; i < dA; i++)
        {
            //if (dX[i] + startmidX >= screen->GetWidth() - tileSize || dX[i] + startmidX < 0 || dY[i] + startmidY >= screen->GetHeight() - tileSize || dY[i] + startmidY < 0) continue;
            if (level != 8 || level == 8 && dH[i] == false)
            {
                doors.SetFrame(dF[i]);
                doors.Draw(screen, dX[i] - plx + startmidX, dY[i] - ply + startmidY);
            }
        }

        /*for (int i = 0; i < dA; i++)
        {
            doors.SetFrame(dF[i]);
            doors.Draw(screen, dX[i] - plx + startmidX, dY[i] - ply + startmidY);
        }*/

        //item creation
        for (int i = 0; i < iA; i++)
        {
            if (iPU[i] == false && iU[i] == false && iH[i] == false)
            {
                items.SetFrame(iF[i]);
                items.Draw(screen, iX[i] - plx + startmidX, iY[i] - ply + startmidY);
            }
        }

        //tutorial creation
        for (int i = 0; i < 10; i++)
        {
            if (tutH[i] == false)
            {
                tutorial.SetFrame(i);
                tutorial.Draw(screen, tutX[i] - plx + startmidX, tutY[i] - ply + startmidY);
            }
        }

        if (level == 10) tfp.Draw(screen, (tileSize * 7 - tileSize) - plx + startmidX, (tileSize * 3 - tileSize) - ply + startmidY);
    }

    void tutorialCheck(int px, int py)
    {
        px = px + characterCenter;
        py = py + characterCenter;
        for (int i = 0; i < 10; i++) { tutH[i] = true; }
        if (level == 0)
        {
            if (px >= tileSize * 2 - tileSize && px <= tileSize * 5 - tileSize && py >= tileSize * 5 - tileSize && py <= tileSize * 8 - tileSize && dL[3] == true) tutH[6] = false;
            if (px >= tileSize * 3 - tileSize && px <= tileSize * 4 - tileSize && py >= tileSize * 4 - tileSize && py <= tileSize * 7 - tileSize && dL[3] == true) tutH[0] = false;
            if (px >= tileSize * 3 - tileSize && px <= tileSize * 4 - tileSize && py >= tileSize * 4 - tileSize && py <= tileSize * 7 - tileSize && dL[3] == true) tutH[1] = false;
            if (px >= tileSize * 4 - tileSize && px <= tileSize * 6 - tileSize && py >= tileSize * 2 - tileSize && py <= tileSize * 3 - tileSize && dL[3] == true) tutH[2] = false;
            if (px >= tileSize * 7 - tileSize && px <= tileSize * 8 - tileSize && py >= tileSize * 3 - tileSize && py <= tileSize * 5 - tileSize && dL[3] == true) tutH[3] = false;
            if (px >= tileSize * 5 - tileSize && px <= tileSize * 7 - tileSize && py >= tileSize * 6 - tileSize && py <= tileSize * 7 - tileSize && dL[3] == true) tutH[4] = false;
            if (px >= tileSize * 2 - tileSize && px <= tileSize * 5 - tileSize && py >= tileSize * 5 - tileSize && py <= tileSize * 8 - tileSize && dL[3] == false) tutH[5] = false;
        }
        else if (level == 5 && px >= tileSize * 6 - tileSize && px <= tileSize * 9 - tileSize && py >= tileSize * 9 - tileSize && py <= tileSize * 12 - tileSize) tutH[7] = false;
        else if (level == 6 && px >= tileSize * 4 - tileSize && px <= tileSize * 7 - tileSize && py >= tileSize * 4 - tileSize && py <= tileSize * 7 - tileSize) tutH[8] = false;
        else if (level == 7 && px >= tileSize * 10 - tileSize && px <= tileSize * 13 - tileSize && py >= tileSize * 6 - tileSize && py <= tileSize * 9 - tileSize) tutH[9] = false;
        else
        {
            return;
        }
    }


    void Game::Tick(float deltaTime)
    {
        int startmidX = (screen->GetWidth() - 32) / 2;
        int startmidY = (screen->GetHeight() - 32) / 2;

        screen->Clear(0);

        createLevel(screen, startmidX, startmidY, px, py);
                
        if (level >= 5) stickUnlocked = true;
        if (srm == true) currentTime = std::chrono::steady_clock::now(), time = std::chrono::duration<float>(currentTime - startTime).count();

        if (level != 11 && level != 12)
        {
            if (isPT == false)
            {
                character.SetFrame(characterState);
                character.Draw(screen, startmidX, startmidY);
            }

            int nx = px, ny = py;
            if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
                nx--;
                nx--;
            }
            if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
                nx++;
                nx++;
            }
            if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
                ny--;
                ny--;
            }
            if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
                ny++;
                ny++;
            }
            if (CheckPos(nx, ny) && CheckPos(nx + 40, ny + 40) && CheckPos(nx + 40, ny) && CheckPos(nx, ny + 40) &&
                checkDoor(nx, ny))
                px = nx, py = ny;
        }

        tutorialCheck(px, py);

        if (level >= 1 && level <= 10)
        {
            char mC[32]; //money counter
            std::snprintf(mC, sizeof(mC), "coins: %d", money);
            screen->PrintScaled(mC, 8, 8, 3, 3, 0xffffff);

            if (srm == true)
            {
                char tC[32]; //time counter
                std::snprintf(tC, sizeof(tC), "%f", time);
                screen->PrintScaled(tC, 608, 8, 3, 3, 0xffffff);
            }
        }
        else if (level == 11)
        {
            char mC[32]; //money counter
            std::snprintf(mC, sizeof(mC), "you have %d out 0f 84 coins", money);
            /*if (mb == true) */screen->PrintScaled(mC, 240, 32, 2, 2, 0xffff00), mb = false;/*
            else if (mb == false) screen->PrintScaled(mC, 160, 32, 3, 3, 0xffff00), mb = true;*/
            screen->PrintScaled("nice job! if you want you can:", 144, 64, 3, 3, 0xffffff);
            screen->PrintScaled("replay everything from level 1 (press r)", 32, 144, 3, 3, 0xff8c00);
            screen->PrintScaled("ps: try getting all the coins", 224, 176, 2, 2, 0xff8c00);
            screen->PrintScaled("choose a specific level to play:", 104, 224, 3, 3, 0xff00ff);
            screen->PrintScaled("do speedrun mode (press s)", 160, 352, 3, 3, 0x0000ff);
            screen->PrintScaled("info: there is a timer and you start from level 1", 112, 384, 2, 2, 0x0000ff);
            screen->PrintScaled("special buttons: r = reset level, t = total reset to level 1", 48, 400, 2, 2, 0x0000ff);
            screen->PrintScaled("              your time will reset  start all over again", 48, 416, 2, 2, 0x0000ff);
            screen->PrintScaled("to see all your times press t (on this menu)", 128, 432, 2, 2, 0x0000ff);
            screen->PrintScaled("from now on you can come back here by pressing m", 112, 480, 2, 2, 0x00ff00);

            for (int i = 0; i < 11; i++)
            {
                lvlbuttons.SetFrame(i);
                lvlbuttons.Draw(screen, (i * 48) + 136, 256);

                if (mousex >= (i * 48) + 136 && mousex <= (i * 48) + 168 && mousey >= 256 && mousey <= 288 && GetAsyncKeyState(VK_LBUTTON)) level = i, begin = false, money = 0;
            }

            if (GetAsyncKeyState('R')) level = 1, begin = false, money = 0;
            if (GetAsyncKeyState('T')) level = 12, begin = false;
            if (GetAsyncKeyState('S')) level = 1, begin = false, srm = true, srf = true;
        }
        else if (level == 12)
        {
            char tC[64]; //time counter

            screen->PrintScaled("best times", 288, 8, 4, 4, 0x0000ff);

            for (int i = 1; i < 11; i++)
            {
                lvlbuttons.SetFrame(i);

                if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9)
                {
                    lvlbuttons.Draw(screen, 244, (i * 44) + 32);
                    if (mousex >= 244 && mousex <= 276 && mousey >= (i * 44) + 32 && mousey <= (i * 44) + 64 && GetAsyncKeyState(VK_LBUTTON)) level = i, begin = false, money = 0, srm = true, srl = true;
                }
                else if (i == 2 || i == 4 || i == 6 || i == 8 || i == 10)
                {
                    lvlbuttons.Draw(screen, 552, (i * 44) - 44 + 32);
                    if (mousex >= 552 && mousex <= 584 && mousey >= (i * 44) - 44 + 32 && mousey <= (i * 44) - 44 + 64 && GetAsyncKeyState(VK_LBUTTON)) level = i, begin = false, money = 0, srm = true, srl = true;
                }
            }

            //could make shorter
            std::snprintf(tC, sizeof(tC), "full game: %f", fastestTime[0]); //total time
            screen->PrintScaled(tC, 224, 32, 3, 3, 0x0000ff);
            screen->PrintScaled("(press s to try again)", 272, 52, 2, 2, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[1]); //lvl 1
            screen->PrintScaled(tC, 176, (1 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[2]); //lvl 2
            screen->PrintScaled(tC, 480, (1 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[3]); //lvl 3
            screen->PrintScaled(tC, 176, (2 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[4]); //lvl 4
            screen->PrintScaled(tC, 480, (2 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[5]); //lvl 5
            screen->PrintScaled(tC, 176, (3 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[6]); //lvl 6
            screen->PrintScaled(tC, 480, (3 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[7]); //lvl 7
            screen->PrintScaled(tC, 176, (4 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[8]); //lvl 8
            screen->PrintScaled(tC, 480, (4 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[9]); //lvl 9
            screen->PrintScaled(tC, 176, (5 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[10]); //lvl 10
            screen->PrintScaled(tC, 480, (5 * 88) + 32, 3, 3, 0x0000ff);

            if (GetAsyncKeyState('S')) level = 1, begin = false, srm = true, srf = true;
        }
        
        if (GetAsyncKeyState('E'))
        {
            if (eIsPressed == false)
            {
                checkItem(px, py);
                eIsPressed = true;
            }
        }
        else
        {
            eIsPressed = false;
        }

        //reset level
        if (GetAsyncKeyState('R'))
        {
            if (srm == false && level >= 7 && level < 11)
            {
                money = money - mgil;
                begin = false;
            }
            else if (srm == true && srf == true)
            {
                money = money - mgil;
                begin = false;
            }
            else if (srm == true && srl == true)
            {
                money = money - mgil;
                begin = false;
            }
        }

        if (GetAsyncKeyState('M') && finished == true)
        {
            begin = false;
            level = 11;
        }

        //character transformation
        if (isPT == true)
        {
            Ttimer += deltaTime;

            if (Ttimer >= TFtime)
            {
                currentFT++;
                Ttimer = 0.0f;

                if (currentT)
                {
                    currentT->SetFrame(currentFT);
                    currentT->Draw(screen, startmidX, startmidY);
                }

                if (currentFT >= maxFT) {
                    isPT = false;
                    character.SetFrame(targetCS);
                    characterState = targetCS;
                }
            }
            else
            {
                if (currentT) {
                    currentT->Draw(screen, startmidX, startmidY);
                }
            }
        }

        if (isPT == false) {
            if (GetAsyncKeyState('C')) {
                if (!TrKeyIsPressed) {
                    if (characterState == 1) {
                        isPT = true;
                        currentT = &BtC;
                        currentFT = 0;
                        maxFT = 45 - 1;
                        Ttimer = 0.0f;
                        targetCS = 0;
                    }
                    else if (characterState == 2) {
                        isPT = true;
                        currentT = &TtC;
                        currentFT = 0;
                        maxFT = 50 - 1;
                        Ttimer = 0.0f;
                        targetCS = 0;
                    }
                    else if (characterState == 3) {
                        isPT = true;
                        currentT = &StC;
                        currentFT = 0;
                        maxFT = 55 - 1;
                        Ttimer = 0.0f;
                        targetCS = 0;
                    }
                    TrKeyIsPressed = true;
                }
            }
            else if (GetAsyncKeyState('B')) {
                if (!TrKeyIsPressed) {
                    if (characterState == 0) {
                        isPT = true;
                        currentT = &CtB;
                        currentFT = 0;
                        maxFT = 45 - 1;
                        Ttimer = 0.0f;
                        targetCS = 1;
                    }
                    else if (characterState == 2) {
                        isPT = true;
                        currentT = &TtB;
                        currentFT = 0;
                        maxFT = 35 - 1;
                        Ttimer = 0.0f;
                        targetCS = 1;
                    }
                    else if (characterState == 3) {
                        isPT = true;
                        currentT = &StB;
                        currentFT = 0;
                        maxFT = 55 - 1;
                        Ttimer = 0.0f;
                        targetCS = 1;
                    }
                    TrKeyIsPressed = true;
                }
            }
            else if (GetAsyncKeyState('V')) {
                if (!TrKeyIsPressed) {
                    if (characterState == 0) {
                        isPT = true;
                        currentT = &CtT;
                        currentFT = 0;
                        maxFT = 50 - 1;
                        Ttimer = 0.0f;
                        targetCS = 2;
                    }
                    else if (characterState == 1) {
                        isPT = true;
                        currentT = &BtT;
                        currentFT = 0;
                        maxFT = 35 - 1;
                        Ttimer = 0.0f;
                        targetCS = 2;
                    }
                    else if (characterState == 3) {
                        isPT = true;
                        currentT = &StT;
                        currentFT = 0;
                        maxFT = 55 - 1;
                        Ttimer = 0.0f;
                        targetCS = 2;
                    }
                    TrKeyIsPressed = true;
                }
            }
            else if (GetAsyncKeyState('N') && stickUnlocked == true) {
                if (!TrKeyIsPressed) {
                    if (characterState == 0) {
                        isPT = true;
                        currentT = &CtS;
                        currentFT = 0;
                        maxFT = 55 - 1;
                        Ttimer = 0.0f;
                        targetCS = 3;
                    }
                    else if (characterState == 1) {
                        isPT = true;
                        currentT = &BtS;
                        currentFT = 0;
                        maxFT = 55 - 1;
                        Ttimer = 0.0f;
                        targetCS = 3;
                    }
                    else if (characterState == 2) {
                        isPT = true;
                        currentT = &TtS;
                        currentFT = 0;
                        maxFT = 55 - 1;
                        Ttimer = 0.0f;
                        targetCS = 3;
                    }
                    TrKeyIsPressed = true;
                }
            }
            else {
                TrKeyIsPressed = false;
            }

        }
    }
};