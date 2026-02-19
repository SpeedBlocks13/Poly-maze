#pragma once

namespace Tmpl8
{
    class Item
    {
    public:
        Item(int x, int y, int frame, bool hidden = false);

        bool isCoin() const { return frame == 0; }
        bool isDiamond() const { return frame == 1; }
        bool isKey() const { return frame >= 2 && frame <= 7; }

        //getters
        int getFrame() const { return frame; }
        int getX() const { return x; }
        int getY() const { return y; }
        bool isPickedUp() const { return pickedUp; }
        bool isUsed() const { return used; }
        bool isHidden() const { return hidden; }

        //setters
        void setPickedUp(bool p) { pickedUp = p; }
        void setUsed(bool u) { used = u; }
        void setHidden(bool h) { hidden = h; }
        void setX(int newX) { x = newX; }
        void setY(int newY) { y = newY; }

    private:
        int x, y;
        int frame;
        bool pickedUp;
        bool used;
        bool hidden;
    };

} // namespace Tmpl8