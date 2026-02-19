#include "doors.h"

namespace Tmpl8
{
    Door::Door(int x, int y, int criteria, bool locked, int frame, bool hidden)
        : x(x), y(y), criteria(criteria), locked(locked), frame(frame), hidden(hidden), open(false)
    {
    }

    void Door::updateLockState(int characterState)
    {
        if (criteria >= 1 && criteria <= 4)
            locked = (criteria != (characterState + 1));
    }

    bool Door::tryUnlockWithKey(int itemFrame)
    {
        if (criteria < 5 || criteria > 10 || !locked) return false;
        if (criteria != (itemFrame + 3)) return false;

        locked = false;
        return true;
    }

    void Door::openDoor()
    {
        if (locked || open) return;

        frame = (frame % 4 == 3) ? frame - 3 : frame + 1;
        open = true;
    }

    void Door::closeDoor()
    {
        if (!locked || !open) return;

        frame = (frame % 4 == 0) ? frame + 3 : frame - 1;
        open = false;
    }

    bool Door::blocksMovement(int nx, int ny, int charSize) const
    {
        if (!locked) return false;

        switch (frame % 4)
        {
        case 0: //UP
            return nx + charSize >= x && nx <= x + TILE_SIZE
                && ny + charSize >= y && ny <= y + DOOR_THICKNESS;
        case 1: //LEFT
            return nx + charSize >= x && nx <= x + DOOR_THICKNESS
                && ny >= y && ny <= y + TILE_SIZE;
        case 2: //DOWN
            return nx >= x && nx <= x + TILE_SIZE
                && ny + charSize >= y + 52 && ny <= y + TILE_SIZE;
        case 3: //RIGHT
            return nx + charSize >= x + 52 && nx <= x + TILE_SIZE
                && ny >= y && ny <= y + TILE_SIZE;
        }
        return false;
    }

} // namespace Tmpl8