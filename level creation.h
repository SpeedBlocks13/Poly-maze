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

        //read-only access to data
        const std::vector<Door>& getDoors() const { return doors; }
        const std::vector<Item>& getItems() const { return items; }
        const std::vector<std::string>& getMap() const { return map; }
        int getMapWidth() const { return mapWidth; }
        int getMapHeight() const { return mapHeight; }
        int getPlayerStartX() const { return playerStartX; }
        int getPlayerStartY() const { return playerStartY; }

        //mutable access (for level 8 mechanics and game logic)
        std::vector<Door>& doors;
        std::vector<Item>& items;
        std::vector<std::string>& map;

    private:
        std::vector<Door> doorsData;
        std::vector<Item> itemsData;
        std::vector<std::string> mapData;
        int mapWidth;
        int mapHeight;
        int playerStartX;
        int playerStartY;
    };

} // namespace Tmpl8