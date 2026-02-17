#pragma once
#include <vector>

namespace Tmpl8
{
    constexpr int TILE_SIZE = 64;
    constexpr int DOOR_THICKNESS = 12;

    //door direction is determined by frame % 4:
    //0 = UP, 1 = LEFT, 2 = DOWN, 3 = RIGHT
    enum class DoorDirection { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };

    class Door
    {
    public:
        int x, y;           //door position
        int criteria;       //0 = no criteria, 1-4 = character criteria, 5-10 = key criteria
        bool locked;        //is the door locked
        bool open;          //is the door opened
        int frame;          //current sprite frame
        bool hidden;        //is the door hidden

        //constructor
        Door(int x, int y, int criteria, bool locked, int frame, bool hidden = false);

        //get the direction of the door based on its frame
        DoorDirection getDirection() const;

        //update lock state based on character state (for character-based doors)
        void updateLockState(int characterState);

        //attempt to unlock with a key
        bool tryUnlockWithKey(int itemFrame);

        //open/close the door
        void openDoor();
        void closeDoor();

        //check if door blocks movement at the given position
        bool blocksMovement(int nx, int ny, int charSize) const;
    };

} // namespace Tmpl8