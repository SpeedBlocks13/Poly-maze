#pragma once

namespace Tmpl8
{
    constexpr int TILE_SIZE = 64;
    constexpr int DOOR_THICKNESS = 12;

    class Door
    {
    public:
        Door(int x, int y, int criteria, bool locked, int frame, bool hidden = false);

        void updateLockState(int characterState);
        bool tryUnlockWithKey(int itemFrame);
        void openDoor();
        void closeDoor();
        bool blocksMovement(int nx, int ny, int charSize) const;

        //getters
        int getX() const { return x; }
        int getY() const { return y; }
        int getFrame() const { return frame; }
        bool isLocked() const { return locked; }
        bool isOpen() const { return open; }
        bool isHidden() const { return hidden; }

        //setters (lvl 8)
        void setHidden(bool h) { hidden = h; }
        void setLocked(bool l) { locked = l; }
        void setFrame(int f) { frame = f; }

    private:
        int x, y;
        int criteria;
        bool locked;
        bool open;
        int frame;
        bool hidden;
    };

} // namespace Tmpl8