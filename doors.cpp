#include "doors.h"

namespace Tmpl8
{
    Door::Door(int x, int y, int criteria, bool locked, int frame, bool hidden)
        : x(x), y(y), criteria(criteria), locked(locked), frame(frame), hidden(hidden), open(false)
    {
    }

    DoorDirection Door::getDirection() const
    {
        //checks door direction 
        //frame % 4 == 0 -> UP
        //frame % 4 == 1 -> LEFT
        //frame % 4 == 2 -> DOWN
        //frame % 4 == 3 -> RIGHT
        int direction = frame % 4;
        return static_cast<DoorDirection>(direction);
    }

    void Door::updateLockState(int characterState)
    {
        //updates character state based doors
        if (criteria >= 1 && criteria <= 4)
        {
            locked = (criteria != (characterState + 1));
        }
    }

    bool Door::tryUnlockWithKey(int itemFrame)
    {
        //checks if the key currently holded and the door corespond
        if (criteria >= 5 && criteria <= 10 && locked)
        {
            if (criteria == (itemFrame + 3))
            {
                locked = false;
                return true; //key gets used
            }
        }
        return false;
    }

    void Door::openDoor()
    {
        if (!locked && !open)
        {
            int direction = frame % 4;

            if (direction == 0) //UP door
            {
                frame = frame + 1;
                open = true;
            }
            else if (direction == 1) //LEFT door
            {
                frame = frame + 1;
                open = true;
            }
            else if (direction == 2) //DOWN door
            {
                frame = frame + 1;
                open = true;
            }
            else if (direction == 3) //RIGHT door
            {
                frame = frame - 3;
                open = true;
            }
        }
    }

    void Door::closeDoor()
    {
        if (locked && open)
        {
            int direction = frame % 4;

            if (direction == 0) //UP door (when opened)
            {
                frame = frame + 3;
                open = false;
            }
            else if (direction == 1) //LEFT door (when opened)
            {
                frame = frame - 1;
                open = false;
            }
            else if (direction == 2) //DOWN door (when opened)
            {
                frame = frame - 1;
                open = false;
            }
            else if (direction == 3) //RIGHT door (when opened)
            {
                frame = frame - 1;
                open = false;
            }
        }
    }

    bool Door::blocksMovement(int nx, int ny, int charSize) const
    {
        if (!locked) return false;

        int direction = frame % 4;

        //check UP doors (frame % 4 == 0)
        if (direction == 0 &&
            nx + charSize >= x && nx <= x + TILE_SIZE &&
            ny + charSize >= y && ny <= y + DOOR_THICKNESS)
        {
            return true;
        }
        //check LEFT doors (frame % 4 == 1)
        else if (direction == 1 &&
            nx + charSize >= x && nx <= x + DOOR_THICKNESS &&
            ny >= y && ny <= y + TILE_SIZE)
        {
            return true;
        }
        //check DOWN doors (frame % 4 == 2)
        else if (direction == 2 &&
            nx >= x && nx <= x + TILE_SIZE &&
            ny + charSize >= y + 52 && ny <= y + TILE_SIZE)
        {
            return true;
        }
        //check RIGHT doors (frame % 4 == 3)
        else if (direction == 3 &&
            nx + charSize >= x + 52 && nx <= x + TILE_SIZE &&
            ny >= y && ny <= y + TILE_SIZE)
        {
            return true;
        }

        return false;
    }

} // namespace Tmpl8