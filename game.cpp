#include "game.h"
#include "surface.h"
#include "doors.h"
#include "items.h"
#include "level creation.h"
#include "transformations.h"
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

    //tile spritesheet info
    Surface tiles("assets/tiles.png");
    int spritesheetWidth = 261;
    int spritesheetSpace = 1;

    int characterSize = 40;
    int characterCenter = characterSize / 2; //character center finer based on character size
    int level = 0; //current level
    int money = 0; //total money
    int moneyGainedInLevel = 0;
    bool stickUnlocked = false; //is the stickman unlocked (unlocks at level 5)
    int characterState = 0; //0=cube, 1=ball, 2=triangle, 3=stickman
    bool isATransitionPlaying = false;
    bool eIsPressed = false;
    bool finished = false; //have you completed level 10

    //speedrun info
    bool speedrunMode = false;
    bool fullGameSpeedrun = false;
    bool oneLevelSpeedrun = false;
    std::vector<float> fastestTime = { 9999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999 };
    auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto time = std::chrono::duration<float>(currentTime - startTime).count();

    bool holdingItem = false; //is the player holding an item
    int itemHolding = -1; //what item is the player holding

    bool begin = false; //is the level created

    // Sprites
    Sprite doorsSprite(new Surface("assets/doors.png"), 44);
    Sprite itemsSprite(new Surface("assets/items.png"), 8);
    Sprite character(new Surface("assets/character sprites.png"), 4);
    Sprite tutorialSprite(new Surface("assets/tutorial.png"), 10);
    Sprite thanksForPlaying(new Surface("assets/thanks for playing.png"), 1);
    Sprite lvlbuttons(new Surface("assets/level buttons.png"), 11);

    // Transformation system
    transformations playerTransformations;

    // LevelCreation instance
    LevelCreation levelCreation;

    //sets the character in the center of the screen
    int px = ((2 - 1) * TILE_SIZE) + ((TILE_SIZE - characterSize) / 2);
    int py = ((2 - 1) * TILE_SIZE) + ((TILE_SIZE - characterSize) / 2);

    //sets all the tutorial baloons at the correct possition
    std::vector<int> tutorialX = { (1 - 1) * TILE_SIZE, (1 - 1) * TILE_SIZE,
                                   (4 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE,
                                   (5 - 1) * TILE_SIZE, (1 - 1) * TILE_SIZE,
                                   ((2 - 1) * TILE_SIZE) / 2, (9 - 1) * TILE_SIZE,
                                   (7 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE };
    std::vector<int> tutorialY = { (3 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE,
                                   (1 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE,
                                   (7 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE,
                                   (7 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE,
                                   (4 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE };
    std::vector<bool> tutorialHidden = { true, true, true, true, true, true, true, true, true, true };

    void DrawTile(int tx, int ty, Surface* screen, int x, int y)
    {
        int screenWidth = screen->GetWidth();
        int screenHeight = screen->GetHeight();

        //calculate visible portion of the tile
        int startX = 0, startY = 0;
        int endX = TILE_SIZE, endY = TILE_SIZE;

        //cut left
        if (x < 0) startX = -x;
        //cut right
        if (x + TILE_SIZE > screenWidth) endX = screenWidth - x;
        //cut top
        if (y < 0) startY = -y;
        //cut bottom
        if (y + TILE_SIZE > screenHeight) endY = screenHeight - y;

        //checks if tile is completely offscreen
        if (startX >= TILE_SIZE || startY >= TILE_SIZE || endX <= 0 || endY <= 0) return;
        if (x + endX <= 0 || y + endY <= 0) return;

        Pixel* src = tiles.GetBuffer() + 1 + tx * (TILE_SIZE + spritesheetSpace) +
            (1 + ty * (TILE_SIZE + spritesheetSpace)) * spritesheetWidth;
        Pixel* dst = screen->GetBuffer();

        //draws tiles
        for (int i = startY; i < endY; i++)
        {
            int screenY = y + i;
            if (screenY < 0 || screenY >= screenHeight) continue;

            for (int j = startX; j < endX; j++)
            {
                int screenX = x + j;
                if (screenX < 0 || screenX >= screenWidth) continue;

                dst[screenX + screenY * screenWidth] = src[j + i * spritesheetWidth];
            }
        }
    }

    void createLevel(Surface* screen, int startmidX, int startmidY, int plx, int ply)
    {
        if (begin == false)
        {
            //initialise levelcreation
            levelCreation.createLevel(level);

            //sets players startposition
            px = levelCreation.playerStartX;
            py = levelCreation.playerStartY;

            //emptys variables
            character.SetFrame(0);
            characterState = 0;
            moneyGainedInLevel = 0;
            holdingItem = false;
            itemHolding = -1;

            //startspeedrun timer when needed
            if ((oneLevelSpeedrun || fullGameSpeedrun) && level >= 1 && level <= 10)
            {
                startTime = std::chrono::steady_clock::now();
            }

            begin = true;
        }

        //draws map
        for (int y = 0; y < levelCreation.mapHeight; y++)
        {
            for (int x = 0; x < levelCreation.mapWidth; x++)
            {
                int tx = levelCreation.map[y][x * 4] - 'a';
                int ty = levelCreation.map[y][x * 4 + 1] - 'a';
                DrawTile(tx, ty, screen, x * TILE_SIZE - plx + startmidX,
                    y * TILE_SIZE - ply + startmidY);
            }
        }

        //updates doors
        levelCreation.updateDoors(characterState);
        levelCreation.processDoorStates();

        //draws doors
        for (const auto& door : levelCreation.doors)
        {
            if (level != 8 || !door.hidden)
            {
                doorsSprite.SetFrame(door.frame);
                doorsSprite.Draw(screen, door.x - plx + startmidX, door.y - ply + startmidY);
            }
        }

        //draws items
        for (const auto& item : levelCreation.items)
        {
            if (!item.pickedUp && !item.used && !item.hidden)
            {
                itemsSprite.SetFrame(item.frame);
                itemsSprite.Draw(screen, item.x - plx + startmidX, item.y - ply + startmidY);
            }
        }

        //draws tutorials
        for (int i = 0; i < 10; i++)
        {
            if (!tutorialHidden[i])
            {
                tutorialSprite.SetFrame(i);
                tutorialSprite.Draw(screen, tutorialX[i] - plx + startmidX,
                    tutorialY[i] - ply + startmidY);
            }
        }

        if (level == 10)
        {
            thanksForPlaying.Draw(screen,
                ((7 - 1) * TILE_SIZE) - plx + startmidX,
                ((3 - 1) * TILE_SIZE) - ply + startmidY);
        }

        //makes it posible to have 2 open tiles next to each other but you cant cross them
        if (level == 7)
        {
            if (px + characterCenter >= (8 - 1) * TILE_SIZE &&
                px + characterCenter <= (9 - 1) * TILE_SIZE &&
                py + characterCenter >= (14 - 1) * TILE_SIZE &&
                py + characterCenter <= (15 - 1) * TILE_SIZE)
            {
                levelCreation.map[14] = "aax aax aax aax aax aax aax bd- ce- bcx aa- aa- bb- cd- aax aax aax aax aax aax aax";
            }
            else
            {
                levelCreation.map[14] = "aax aax aax aax aax aax aax bd- cex bc- aa- aa- bb- cd- aax aax aax aax aax aax aax";
            }
        }

        //level 8 secret areas
        if (level == 8)
        {
            for (int i = 0; i < levelCreation.doors.size(); i++)
            {
                if (levelCreation.doors[1].locked == false)
                {
                    levelCreation.map[12] = "aax aax aax aax abx aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[13] = "aax aax ad- ac- ac- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax ab- aax aax";
                }
                if (levelCreation.doors[4].locked == false)
                {
                    levelCreation.map[19] = "aax aax aax abx aax abx aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax";
                    levelCreation.map[20] = "aax ad- ac- ac- ac- ac- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax aax ab- aax aax";
                }
                if (levelCreation.doors[11].locked == false)
                {
                    levelCreation.map[15] = "aax aax bd- bg- cc- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- cc- cc- bg- cc- cc- cc- cc- cc- cd- aax aax ab- aax aax";
                    levelCreation.map[16] = "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax abx aax abx aax ab- aax abx aax abx aax aax aax aax ab- aax aax";
                }
                if (levelCreation.doors[15].locked == false)
                {
                    levelCreation.map[8] = "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    levelCreation.map[9] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                }
                if (levelCreation.doors[20].locked == false)
                {
                    levelCreation.map[1] = "aax aax aax aax ad- ac- dd- aax aax ad- bb- bb- dd- aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    levelCreation.map[2] = "aax aax aax aax bc- aa- dc- aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[3] = "aax aax aax aax bd- bg- cd- aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[4] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[5] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[6] = "aax aax aax ad- ac- dg- ac- dd- aax ab- aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    levelCreation.map[7] = "aax aax aax bc- aa- aa- aa- dc- aax ab- aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    levelCreation.map[8] = "aax aax aax bd- bg- cc- bg- cd- aax ab- aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    levelCreation.map[9] = "aax aax aax aax ab- aax ab- aax aax ab- aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                    levelCreation.map[10] = "aax aax aax aax ab- aax ab- aax aax bc- ac- dd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[11] = "aax aax aax aax ab- aax ab- aax aax bd- cc- cd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { levelCreation.items[j].hidden = false; }
                }
                if (levelCreation.doors[27].locked == false)
                {
                    levelCreation.doors[27].hidden = false;
                    levelCreation.map[1] = "aax aax aax aax ad- ac- dd- aax aax ad- bb- bb- dd- aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    levelCreation.map[2] = "aax aax aax aax bc- aa- cg- bb- bb- dc- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[3] = "aax aax aax aax bd- bg- cd- aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[4] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[5] = "aax aax aax aax aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[6] = "aax aax aax ad- ac- dg- ac- dd- aax ab- aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    levelCreation.map[7] = "aax aax aax bc- aa- aa- aa- dc- aax ab- aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    levelCreation.map[8] = "aax aax aax bd- bg- cc- bg- cd- aax ab- aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    levelCreation.map[9] = "aax aax aax aax ab- aax ab- aax aax ab- aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                    levelCreation.map[10] = "aax aax aax aax ab- aax ab- aax aax bc- ac- dd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[11] = "aax aax aax aax ab- aax ab- aax aax bd- cc- cd- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { levelCreation.items[j].hidden = false; }
                    if (levelCreation.doors[20].locked == true) levelCreation.doors[20].frame = 38;
                }
                if (levelCreation.doors[28].locked == false)
                {
                    levelCreation.doors[28].hidden = false;
                    levelCreation.map[14] = "aax aax bc- aa- aa- aa- aa- aa- cg- bb- bb- bb- ag- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                }
                else if (levelCreation.doors[28].locked == true)
                {
                    levelCreation.doors[28].hidden = true;
                    levelCreation.map[14] = "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                }
                if (levelCreation.doors[29].locked == false)
                {
                    levelCreation.doors[29].hidden = false;
                    levelCreation.map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- cg- bb- bb- bb- ag- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                }
                else if (levelCreation.doors[29].locked == true)
                {
                    levelCreation.doors[29].hidden = true;
                    levelCreation.map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                }
                if (levelCreation.doors[20].locked == true && levelCreation.doors[27].locked == true && levelCreation.doors[28].locked == true && levelCreation.doors[29].locked == true && levelCreation.doors[15].locked == false)
                {
                    levelCreation.doors[27].hidden = true; levelCreation.doors[28].hidden = true; levelCreation.doors[29].hidden = true;
                    levelCreation.doors[27].locked = true; levelCreation.doors[28].locked = true; levelCreation.doors[29].locked = true;
                    levelCreation.map[1] = "aax aax aax aax ad- ac- dd- aax aax aax aax aax de- aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    levelCreation.map[2] = "aax aax aax aax bc- aa- dc- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[3] = "aax aax aax aax bd- bg- cd- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[4] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[5] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[6] = "aax aax aax ad- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    levelCreation.map[7] = "aax aax aax bc- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    levelCreation.map[8] = "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- bg- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax ab- aax aax";
                    levelCreation.map[9] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax abx aax ab- aax abx aax abx aax abx aax abx aax aax aax ab- aax aax";
                    levelCreation.map[10] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[11] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[14] = "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                    levelCreation.map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { levelCreation.items[j].hidden = true; }
                    if (levelCreation.doors[20].locked == true) levelCreation.doors[20].frame = 36;
                }
                if (levelCreation.doors[20].locked == true && levelCreation.doors[27].locked == true && levelCreation.doors[28].locked == true && levelCreation.doors[29].locked == true && levelCreation.doors[15].locked == true)
                {
                    levelCreation.doors[27].hidden = true; levelCreation.doors[28].hidden = true; levelCreation.doors[29].hidden = true;
                    levelCreation.doors[27].locked = true; levelCreation.doors[28].hidden = true; levelCreation.doors[29].hidden = true;
                    levelCreation.map[1] = "aax aax aax aax ad- ac- dd- aax aax aax aax aax de- aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax";
                    levelCreation.map[2] = "aax aax aax aax bc- aa- dc- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[3] = "aax aax aax aax bd- bg- cd- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[4] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[5] = "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    levelCreation.map[6] = "aax aax aax ad- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax";
                    levelCreation.map[7] = "aax aax aax bc- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax";
                    levelCreation.map[8] = "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- ccx cc- bg- cc- ccx cc- ccx cc- ccx cc- ccx cc- cd- aax ab- aax aax";
                    levelCreation.map[9] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[10] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[11] = "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax";
                    levelCreation.map[14] = "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax";
                    levelCreation.map[21] = "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax";
                    for (int j = 16; j <= 33; j++) { levelCreation.items[j].hidden = true; }
                    if (levelCreation.doors[20].locked == true) levelCreation.doors[20].frame = 36;
                }
                if (levelCreation.doors[27].locked == true)
                {
                    levelCreation.doors[27].hidden = true;
                    levelCreation.map[2] = "aax aax aax aax bc- aa- dc- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax";
                    if (levelCreation.doors[20].locked == true) levelCreation.doors[20].frame = 36;
                }
            }
            levelCreation.updateDoors(characterState);
            levelCreation.processDoorStates();
        }
    }

    void checkItem(int px, int py)
    {
        for (int i = 0; i < levelCreation.items.size(); i++)
        {
            Item& item = levelCreation.items[i];

            if (px + characterCenter >= item.x &&
                px + characterCenter <= item.x + 64 &&
                py + characterCenter >= item.y &&
                py + characterCenter <= item.y + 64 &&
                !item.hidden && !item.used)
            {
                if (itemHolding != i)
                {
                    //coins
                    if (item.isCoin())
                    {
                        item.pickedUp = true;
                        item.x = -64;
                        item.y = -64;
                        money++;
                        moneyGainedInLevel++;
                        return;
                    }
                    //diamonds/ finish)
                    else if (item.isDiamond())
                    {
                        itemHolding = -1;
                        holdingItem = false;
                        item.used = true;
                        begin = false;

                        if (oneLevelSpeedrun)
                        {
                            if (time < fastestTime[level])
                                fastestTime[level] = time;
                            level = 12;
                        }
                        else if (fullGameSpeedrun && level == 10)
                        {
                            if (time < fastestTime[0])
                                fastestTime[0] = time;
                            level = 12;
                        }
                        else
                        {
                            if (level == 10)
                            {
                                finished = true;
                                level = 11; //go to menu after completing game
                            }
                            else
                            {
                                level++;
                            }
                        }
                        return;
                    }
                    //keys
                    else if (!holdingItem)
                    {
                        item.pickedUp = true;
                        itemHolding = i;
                        holdingItem = true;
                        return;
                    }
                    else //swsitch items
                    {
                        int previousItem = itemHolding;
                        levelCreation.items[previousItem].x = item.x;
                        levelCreation.items[previousItem].y = item.y;
                        levelCreation.items[previousItem].pickedUp = false;

                        item.pickedUp = true;
                        itemHolding = i;
                        holdingItem = true;
                        return;
                    }
                }
            }

            //drop item
            if (itemHolding == i)
            {
                int previousItem = itemHolding;
                levelCreation.items[previousItem].x =
                    static_cast<int>((px + characterCenter) / TILE_SIZE) * TILE_SIZE;
                levelCreation.items[previousItem].y =
                    static_cast<int>((py + characterCenter) / TILE_SIZE) * TILE_SIZE;
                levelCreation.items[previousItem].pickedUp = false;
                holdingItem = false;
                itemHolding = -1;
            }
        }
    }

    bool checkDoor(int nx, int ny)
    {
        //update doors based on character state
        levelCreation.updateDoors(characterState);

        //unlocks door if carrying correct key
        if (itemHolding >= 0)
        {
            Item& heldItem = levelCreation.items[itemHolding];
            if (levelCreation.tryUnlockDoorWithKey(nx, ny, characterSize, heldItem.frame))
            {
                heldItem.used = true;
                holdingItem = false;
                itemHolding = -1;
            }
        }

        //process doors
        levelCreation.processDoorStates();

        //shows diamond on unlock last door in tutorial level
        if (level == 0 && levelCreation.doors.size() > 3 && !levelCreation.doors[3].locked)
        {
            if (levelCreation.items.size() > 1)
                levelCreation.items[1].hidden = false;
        }

        //checks door collision
        return levelCreation.checkDoorCollision(nx, ny, characterSize);
    }

    void tutorialCheck(int px, int py)
    {
        px = px + characterCenter;
        py = py + characterCenter;

        for (int i = 0; i < 10; i++)
            tutorialHidden[i] = true;

        if (level == 0)
        {
            if (px >= (3 - 1) * TILE_SIZE && px <= (4 - 1) * TILE_SIZE &&
                py >= (4 - 1) * TILE_SIZE && py <= (7 - 1) * TILE_SIZE &&
                levelCreation.doors[3].locked == true)
                tutorialHidden[0] = false; //movement tutorial

            if (px >= (3 - 1) * TILE_SIZE && px <= (4 - 1) * TILE_SIZE &&
                py >= (4 - 1) * TILE_SIZE && py <= (7 - 1) * TILE_SIZE &&
                levelCreation.doors[3].locked == true)
                tutorialHidden[1] = false; //door1 tutorial

            if (px >= (4 - 1) * TILE_SIZE && px <= (6 - 1) * TILE_SIZE &&
                py >= (2 - 1) * TILE_SIZE && py <= (3 - 1) * TILE_SIZE &&
                levelCreation.doors[3].locked == true)
                tutorialHidden[2] = false; //door2 tutorial

            if (px >= (7 - 1) * TILE_SIZE && px <= (8 - 1) * TILE_SIZE &&
                py >= (3 - 1) * TILE_SIZE && py <= (5 - 1) * TILE_SIZE &&
                levelCreation.doors[3].locked == true)
                tutorialHidden[3] = false; //triangle door tutorial

            if (px >= (5 - 1) * TILE_SIZE && px <= (7 - 1) * TILE_SIZE &&
                py >= (6 - 1) * TILE_SIZE && py <= (7 - 1) * TILE_SIZE &&
                levelCreation.doors[3].locked == true)
                tutorialHidden[4] = false; //ball door tutorial

            if (px >= (2 - 1) * TILE_SIZE && px <= (5 - 1) * TILE_SIZE &&
                py >= (5 - 1) * TILE_SIZE && py <= (8 - 1) * TILE_SIZE &&
                levelCreation.doors[3].locked == false)
                tutorialHidden[5] = false; //key tutorial

            if (px >= (2 - 1) * TILE_SIZE && px <= (5 - 1) * TILE_SIZE &&
                py >= (5 - 1) * TILE_SIZE && py <= (8 - 1) * TILE_SIZE &&
                levelCreation.doors[3].locked == true)
                tutorialHidden[6] = false; //finish tutorial
        }
        else if (level == 5 && px >= (6 - 1) * TILE_SIZE &&
            px <= (9 - 1) * TILE_SIZE &&
            py >= (9 - 1) * TILE_SIZE &&
            py <= (12 - 1) * TILE_SIZE)
            tutorialHidden[7] = false; //stickman unlocked tutorial

        else if (level == 6 && px >= (4 - 1) * TILE_SIZE &&
            px <= (7 - 1) * TILE_SIZE &&
            py >= (4 - 1) * TILE_SIZE &&
            py <= (7 - 1) * TILE_SIZE)
            tutorialHidden[8] = false; //drop key tutorial

        else if (level == 7 && px >= (10 - 1) * TILE_SIZE &&
            px <= (13 - 1) * TILE_SIZE &&
            py >= (6 - 1) * TILE_SIZE &&
            py <= (9 - 1) * TILE_SIZE)
            tutorialHidden[9] = false; //reset tutorial
    }

    void Game::Tick(float deltaTime)
    {
        //starts character at the center
        int startmidX = (screen->GetWidth() - 32) / 2;
        int startmidY = (screen->GetHeight() - 32) / 2;

        //clears screen
        screen->Clear(0);

        //creates level
        createLevel(screen, startmidX, startmidY, px, py);

        //condition checkers
        if (level >= 5) stickUnlocked = true;
        if (speedrunMode)
        {
            currentTime = std::chrono::steady_clock::now();
            time = std::chrono::duration<float>(currentTime - startTime).count();
        }

        //throughout the game
        if (level >= 0 && level <= 10)
        {
            //rechecks delta time
            float dt = (deltaTime > 0.0001f && deltaTime < 1.0f) ? deltaTime : 0.0167f;

            //determines movement speed of characters
            float pixelsPerSecond = (characterState == 3) ? 200.0f : 120.0f;
            float moveDistance = pixelsPerSecond * dt;

            //new x,y is x,y
            int nx = px, ny = py;

            //checks for movement
            if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) nx -= static_cast<int>(moveDistance);
            if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) nx += static_cast<int>(moveDistance);
            if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) ny -= static_cast<int>(moveDistance);
            if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) ny += static_cast<int>(moveDistance);

            //check collision with walls and doors
            if (levelCreation.CheckPos(nx, ny) &&
                levelCreation.CheckPos(nx + 40, ny + 40) &&
                levelCreation.CheckPos(nx + 40, ny) &&
                levelCreation.CheckPos(nx, ny + 40) &&
                checkDoor(nx, ny))
            {
                px = nx;
                py = ny;
            }

            //draws character
            if (!isATransitionPlaying)
            {
                character.SetFrame(characterState);
                character.Draw(screen, startmidX, startmidY);

                //draws item held by player
                if (holdingItem && itemHolding >= 0 && itemHolding < levelCreation.items.size())
                {
                    itemsSprite.SetFrame(levelCreation.items[itemHolding].frame);
                    itemsSprite.Draw(screen, startmidX, startmidY);
                }
            }

            //UI
            char mC[32];
            std::snprintf(mC, sizeof(mC), "coins: %d", money);
            screen->PrintScaled(mC, 8, 8, 3, 3, 0xffffff);

            if (speedrunMode)
            {
                char tC[32];
                std::snprintf(tC, sizeof(tC), "%f", time);
                screen->PrintScaled(tC, 608, 8, 3, 3, 0xffffff);
            }
        }

        tutorialCheck(px, py);

        if (level == 11) //menu after completing game
        {
            char mC[64];
            std::snprintf(mC, sizeof(mC), "you have %d out of 84 coins", money);
            screen->PrintScaled(mC, 240, 32, 2, 2, 0xffff00);

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

            //draw level buttons
            for (int i = 0; i < 11; i++)
            {
                lvlbuttons.SetFrame(i);
                lvlbuttons.Draw(screen, (i * 48) + 136, 256);

                //check for click on button
                if (mousex >= (i * 48) + 136 && mousex <= (i * 48) + 168 &&
                    mousey >= 256 && mousey <= 288 && GetAsyncKeyState(VK_LBUTTON))
                {
                    level = i;
                    begin = false;
                    money = 0;
                }
            }

            //key inputs on menu
            if (GetAsyncKeyState('R')) { level = 1; begin = false; money = 0; }
            if (GetAsyncKeyState('T')) { level = 12; begin = false; }
            if (GetAsyncKeyState('S')) { level = 1; begin = false; speedrunMode = true; fullGameSpeedrun = true; }
        }

        else if (level == 12) //speedrun times menu
        {
            char tC[64];

            screen->PrintScaled("best times", 288, 8, 4, 4, 0x0000ff);

            //draw level buttons for speedrun
            for (int i = 1; i < 11; i++)
            {
                lvlbuttons.SetFrame(i);

                if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9)
                {
                    lvlbuttons.Draw(screen, 244, (i * 44) + 32);
                    if (mousex >= 244 && mousex <= 276 &&
                        mousey >= (i * 44) + 32 && mousey <= (i * 44) + 64 &&
                        GetAsyncKeyState(VK_LBUTTON))
                    {
                        level = i;
                        begin = false;
                        money = 0;
                        speedrunMode = true;
                        oneLevelSpeedrun = true;
                    }
                }
                else if (i == 2 || i == 4 || i == 6 || i == 8 || i == 10)
                {
                    lvlbuttons.Draw(screen, 552, (i * 44) - 44 + 32);
                    if (mousex >= 552 && mousex <= 584 &&
                        mousey >= (i * 44) - 44 + 32 && mousey <= (i * 44) - 44 + 64 &&
                        GetAsyncKeyState(VK_LBUTTON))
                    {
                        level = i;
                        begin = false;
                        money = 0;
                        speedrunMode = true;
                        oneLevelSpeedrun = true;
                    }
                }
            }

            //display times
            std::snprintf(tC, sizeof(tC), "full game: %f", fastestTime[0]);
            screen->PrintScaled(tC, 224, 32, 3, 3, 0x0000ff);
            screen->PrintScaled("(press s to try again)", 272, 52, 2, 2, 0x0000ff);

            std::snprintf(tC, sizeof(tC), "%f", fastestTime[1]);
            screen->PrintScaled(tC, 176, (1 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[2]);
            screen->PrintScaled(tC, 480, (1 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[3]);
            screen->PrintScaled(tC, 176, (2 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[4]);
            screen->PrintScaled(tC, 480, (2 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[5]);
            screen->PrintScaled(tC, 176, (3 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[6]);
            screen->PrintScaled(tC, 480, (3 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[7]);
            screen->PrintScaled(tC, 176, (4 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[8]);
            screen->PrintScaled(tC, 480, (4 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[9]);
            screen->PrintScaled(tC, 176, (5 * 88) + 32, 3, 3, 0x0000ff);
            std::snprintf(tC, sizeof(tC), "%f", fastestTime[10]);
            screen->PrintScaled(tC, 480, (5 * 88) + 32, 3, 3, 0x0000ff);

            if (GetAsyncKeyState('S'))
            {
                level = 1;
                begin = false;
                speedrunMode = true;
                fullGameSpeedrun = true;
            }
        }

        //picking up and dropping items
        if (GetAsyncKeyState('E'))
        {
            if (!eIsPressed)
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
        if (GetAsyncKeyState('R') && level >= 7 || GetAsyncKeyState('R') && speedrunMode == true)
        {
            money -= moneyGainedInLevel;
            begin = false;
        }

        //return to menu after finished
        if (GetAsyncKeyState('M') && finished)
        {
            begin = false;
            level = 11;
        }

        //update transformations
        playerTransformations.update(deltaTime, characterState, isATransitionPlaying);

        //draw transformation animation if playing
        playerTransformations.draw(screen, startmidX, startmidY);

        //handle transformation input
        playerTransformations.handleInput(characterState, stickUnlocked);
    }
}