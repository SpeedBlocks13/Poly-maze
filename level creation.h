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
        LevelCreation();

        void createLevel(int level);
        void clear();
        bool CheckPos(int x, int y) const;
        void updateDoors(int characterState);
        bool checkDoorCollision(int nx, int ny, int charSize) const;
        bool tryUnlockDoorWithKey(int px, int py, int charSize, int itemFrame);
        void processDoorStates();

        //public data (game needs direct access for level 8 mechanics)
        std::vector<Door> doors;
        std::vector<Item> items;
        std::vector<std::string> map;

        //getters for read-only data
        int getMapWidth() const { return mapWidth; }
        int getMapHeight() const { return mapHeight; }
        int getPlayerStartX() const { return playerStartX; }
        int getPlayerStartY() const { return playerStartY; }

    private:
        int mapWidth;
        int mapHeight;
        int playerStartX;
        int playerStartY;
    };

} // namespace Tmpl8