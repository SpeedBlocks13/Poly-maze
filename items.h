#pragma once

namespace Tmpl8
{
    enum class ItemType
    {
        COIN = 0,       //frame 0
        DIAMOND = 1,    //frame 1
        RED_KEY = 2,    //frame 2
        BLUE_KEY = 3,   //frame 3
        YELLOW_KEY = 4, //frame 4
        GREEN_KEY = 5,  //frame 5
        PURPLE_KEY = 6, //frame 6
        ORANGE_KEY = 7  //frame 7
    };

    class Item
    {
    public:
        int x, y;
        int frame;
        bool pickedUp;
        bool used;
        bool hidden;

        //constructor
        Item(int x, int y, int frame, bool hidden = false);

        //check if item is a coin
        bool isCoin() const { return frame == 0; }

        //check if item is the diamond (finish)
        bool isDiamond() const { return frame == 1; }

        //check if item is a key
        bool isKey() const { return frame >= 2 && frame <= 7; }

        //get the key type
        int getKeyValue() const { return frame; }
    };

} // namespace Tmpl8