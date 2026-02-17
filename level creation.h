#pragma once
#include "doors.h"
#include "items.h"
#include <vector>
#include <string>

namespace Tmpl8
{
    class LevelCreation
    {
    public:
        std::vector<Door> doors;
        std::vector<Item> items;
        std::vector<std::string> map;
        int mapWidth;
        int mapHeight;
        int playerStartX;
        int playerStartY;

        LevelCreation();

        //initialize a specific level
        void createLevel(int level);

        //clear current level data
        void clear();

        //check if a position is walkable
        bool CheckPos(int x, int y) const;

        //update all doors based on character state
        void updateDoors(int characterState);

        //check if any door blocks movement
        bool checkDoorCollision(int nx, int ny, int charSize) const;

        //try to unlock a door with a key at player position
        bool tryUnlockDoorWithKey(int px, int py, int charSize, int itemFrame);

        //process door opening/closing animations
        void processDoorStates();
    };

} // namespace Tmpl8