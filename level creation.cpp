#include "level creation.h"

namespace Tmpl8
{
    LevelCreation::LevelCreation()
        : mapWidth(0), mapHeight(0), playerStartX(0), playerStartY(0)
    {
    }

    void LevelCreation::clear()
    {
        doors.clear();
        items.clear();
        map.clear();
        mapWidth = 0;
        mapHeight = 0;
    }

    void LevelCreation::createLevel(int level)
    {
        clear();

        if (level == 0)
        {
            playerStartX = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((6 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 8;
            mapHeight = 8;
            map = {
                "bax aax aax aax aax aax aax aax",
                "bax aax ad- bb- bb- bb- dd- aax",
                "bax aax ab- aax aax aax ab- aax",
                "aax aax ab- aax aax aax ab- aax",
                "aax ad- dg- dd- aax aax ab- aax",
                "aax bc- aa- cg- bb- bb- cd- aax",
                "aax bd- cc- cd- aax aax aax aax",
                "aax aax aax aax aax bax bax bax"
            };

            doors.push_back(Door((3 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 1, true, 4));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 3, true, 15));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 2, true, 10));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 6, true, 25));

            items.push_back(Item((7 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((3 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 1, true));
        }

        else if (level == 1)
        {
            playerStartX = ((5 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((11 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 10;
            mapHeight = 13;
            map = {
                "aax aax aax bax bax aax aax aax aax aax",
                "aax de- aax aax aax aax ad- ac- dd- aax",
                "aax ab- aax de- aax aax bc- aa- dc- aax",
                "aax ab- aax ab- aax aax bc- cc- cd- aax",
                "aax bd- bb- dc- aax ad- cd- aax aax aax",
                "aax aax aax ab- aax ab- aax aax bax bax",
                "bax bax aax bd- ac- cd- aax bax bax bax",
                "bax bax aax aax ab- aax aax bax bax bax",
                "bax bax aax aax ab- aax aax bax bax bax",
                "bax bax aax ad- aa- dd- aax bax bax bax",
                "bax bax aax bc- aa- dc- aax bax bax bax",
                "bax bax aax bd- cc- cd- aax bax bax bax",
                "bax bax aax aax aax aax aax bax bax bax"
            };

            doors.push_back(Door((2 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 3, true, 12));
            doors.push_back(Door((4 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 2, true, 10));
            doors.push_back(Door((6 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 5, true, 20));

            items.push_back(Item((2 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 2, false));
            items.push_back(Item((8 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 2)
        {
            playerStartX = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 10;
            mapHeight = 9;
            map = {
                "aax aax aax aax aax bax bax bax bax bax",
                "aax ad- ac- dd- aax aax aax aax aax aax",
                "aax bc- aa- cg- bb- bb- ac- bb- ce- aax",
                "aax bd- cc- cd- aax aax ab- aax aax aax",
                "aax aax aax aax ae- bb- da- bb- ce- aax",
                "aax ad- ac- dd- aax aax ab- aax aax aax",
                "aax bc- aa- cg- bb- bb- cc- bb- ce- aax",
                "aax bd- cc- cd- aax aax aax aax aax aax",
                "aax aax aax aax aax aax bax bax bax bax"
            };

            doors.push_back(Door((8 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 7, true, 31));
            doors.push_back(Door((8 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 2, true, 11));
            doors.push_back(Door((8 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 10, true, 43));
            doors.push_back(Door((6 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 3, true, 15));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 8, true, 33));

            items.push_back(Item((9 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 7, false));
            items.push_back(Item((5 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 4, false));
            items.push_back(Item((9 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((9 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 5, false));
            items.push_back(Item((3 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 3)
        {
            playerStartX = ((4 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 9;
            mapHeight = 13;
            map = {
                "bax aax aax aax aax aax bax bax bax",
                "bax aax ad- ac- dd- aax bax bax bax",
                "bax aax bc- aa- dc- aax bax bax bax",
                "bax aax bd- bg- cd- aax aax aax aax",
                "aax aax aax ab- aax ad- ac- dd- aax",
                "aax ae- bb- da- bb- ag- aa- dc- aax",
                "aax aax aax ab- aax bd- cc- cd- aax",
                "aax ae- bb- dc- aax aax aax aax aax",
                "aax aax aax bc- bb- ce- aax bax bax",
                "aax ae- bb- dc- aax aax aax bax bax",
                "aax aax aax ab- aax bax bax bax bax",
                "bax bax aax be- aax bax bax bax bax",
                "bax bax aax aax aax bax bax bax bax"
            };

            doors.push_back(Door((4 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 3, true, 12));
            doors.push_back(Door((3 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 10, true, 41));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 39));
            doors.push_back(Door((4 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 2, true, 8));
            doors.push_back(Door((3 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 6, true, 25));
            doors.push_back(Door((4 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 1, true, 4));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 7, true, 31));
            doors.push_back(Door((3 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 8, true, 33));
            doors.push_back(Door((4 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 3, true, 12));

            items.push_back(Item((2 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 6, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 5, false));
            items.push_back(Item((6 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 7, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 4, false));
            items.push_back(Item((8 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((8 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((6 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((6 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((7 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 4)
        {
            playerStartX = ((5 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((17 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 24;
            mapHeight = 19;
            map = {
                "bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax aax aax aax aax aax bax bax",
                "bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax bax aax ad- ac- dd- aax bax bax",
                "bax bax bax bax bax bax bax bax bax bax bax aax aax aax aax aax aax aax bc- aa- dc- aax bax bax",
                "bax bax bax bax bax bax bax bax bax bax bax aax ad- bb- bb- dd- aax aax bd- bg- cd- aax bax bax",
                "bax bax bax bax bax bax bax bax aax aax aax aax ab- aax aax ab- aax aax aax ab- aax aax bax bax",
                "bax bax bax bax bax bax bax bax aax de- aax aax ab- aax aax bc- bb- bb- bb- cd- aax bax bax bax",
                "bax aax aax aax bax bax bax bax aax ab- aax aax ab- aax aax ab- aax aax aax aax aax bax bax bax",
                "bax aax de- aax bax bax bax bax aax ab- aax aax ab- aax aax ab- aax aax aax aax aax bax bax bax",
                "bax aax ab- aax bax aax aax aax aax bc- bb- bb- cd- aax aax bd- bb- bb- bb- dd- aax bax bax bax",
                "bax aax ab- aax bax aax de- aax aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax",
                "bax aax ab- aax aax aax ab- aax aax ab- aax bax aax aax aax aax aax aax aax bc- bb- bb- ce- aax",
                "bax aax bd- bb- ac- bb- cc- bb- bb- cd- aax bax aax ae- bb- bb- bb- bb- bb- cd- aax aax aax aax",
                "aax aax aax aax ab- aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax bax bax bax",
                "aax ae- bb- bb- da- bb- bb- bb- bb- bb- bb- dd- aax bax bax bax bax bax bax bax bax bax bax bax",
                "aax aax aax aax ab- aax aax aax aax aax aax ab- aax bax bax bax bax bax bax bax bax bax bax bax",
                "bax bax aax ad- dg- dd- aax bax bax bax aax ab- aax bax bax bax bax bax bax bax bax bax bax bax",
                "bax bax aax bc- aa- dc- aax bax bax bax aax ab- aax bax bax bax bax bax bax bax bax bax bax bax",
                "bax bax aax bd- cc- cd- aax bax bax bax aax be- aax bax bax bax bax bax bax bax bax bax bax bax",
                "bax bax aax aax aax aax aax bax bax bax aax aax aax bax bax bax bax bax bax bax bax bax bax aax"
            };

            doors.push_back(Door((3 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 7, true, 28));
            doors.push_back(Door((4 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 2, true, 9));
            doors.push_back(Door((6 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 3, true, 13));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 5, true, 20));
            doors.push_back(Door((8 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 1, true, 5));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 3, true, 13));
            doors.push_back(Door((10 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 1, true, 6));
            doors.push_back(Door((10 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 2, true, 11));
            doors.push_back(Door((11 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 2, true, 9));
            doors.push_back(Door((12 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 1, true, 4));
            doors.push_back(Door((13 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 6, true, 24));
            doors.push_back(Door((14 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 3, true, 15));
            doors.push_back(Door((16 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 2, true, 10));
            doors.push_back(Door((17 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 1, true, 7));
            doors.push_back(Door((17 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 2, true, 9));
            doors.push_back(Door((19 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 1, true, 5));
            doors.push_back(Door((20 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 8, true, 32));
            doors.push_back(Door((21 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 3, true, 13));

            items.push_back(Item((3 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 2, false));
            items.push_back(Item((7 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((12 - 1) * TILE_SIZE, (18 - 1) * TILE_SIZE, 4, false));
            items.push_back(Item((23 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 5, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((10 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((14 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((20 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 5)
        {
            playerStartX = ((7 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((10 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 14;
            mapHeight = 19;
            map = {
                "bax aax aax aax aax aax aax aax bax bax bax bax bax bax",
                "bax aax ad- bb- bb- bb- dd- aax bax bax bax bax bax bax",
                "aax aax ab- aax aax aax ab- aax aax aax aax aax aax bax",
                "aax ad- dg- dd- aax ad- dg- dd- aax ad- ac- dd- aax bax",
                "aax bc- aa- dc- aax bc- aa- cg- bb- ag- aa- dc- aax bax",
                "aax bd- cc- cd- aax bd- bg- cd- aax bd- cc- cd- aax bax",
                "aax aax aax aax aax aax ab- aax aax aax aax aax aax bax",
                "aax aax aax aax aax aax ab- aax aax aax aax aax aax aax",
                "aax ad- ac- dd- aax ad- dg- dd- aax aax ad- ac- dd- aax",
                "aax bc- aa- cg- bb- ag- aa- cg- bb- bb- ag- aa- dc- aax",
                "aax bd- cc- cd- aax bd- bg- cd- aax aax bd- cc- cd- aax",
                "aax aax aax aax aax aax ab- aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax ab- aax aax aax aax aax aax bax",
                "aax ad- ac- dd- aax ad- dg- dd- aax ad- ac- dd- aax bax",
                "aax bc- aa- dc- aax bc- aa- cg- bb- ag- aa- dc- aax bax",
                "aax bd- bg- cd- aax bd- bg- cd- aax bd- cc- cd- aax bax",
                "aax aax ab- aax aax aax ab- aax aax aax aax aax aax bax",
                "bax aax bd- bb- bb- bb- cd- aax bax bax bax bax bax bax",
                "bax aax aax aax aax aax aax aax bax bax bax bax bax bax"
            };

            doors.push_back(Door((3 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 10, true, 42));
            doors.push_back(Door((3 - 1) * TILE_SIZE, (17 - 1) * TILE_SIZE, 8, true, 32));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 4, true, 19));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 1, true, 6));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 3, true, 12));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 7, true, 31));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 9, true, 39));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 6, true, 27));
            doors.push_back(Door((10 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 5, true, 23));

            items.push_back(Item((3 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((3 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 6, false));
            items.push_back(Item((7 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 5, false));
            items.push_back(Item((7 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 7, false));
            items.push_back(Item((11 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 2, false));
            items.push_back(Item((11 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 4, false));
            //coins
            items.push_back(Item((2 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((10 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((10 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((10 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((10 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((12 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((12 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((12 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((12 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            //diamond
            items.push_back(Item((12 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 6)
        {
            playerStartX = ((5 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((5 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 19;
            mapHeight = 9;
            map = {
                "aax aax aax aax aax aax bax bax bax bax bax bax bax bax bax bax bax bax bax",
                "aax ad- bb- bb- dd- aax bax bax bax bax bax bax bax bax bax bax bax bax bax",
                "aax ab- aax aax ab- aax aax bax bax bax bax bax bax bax aax aax aax aax aax",
                "aax ab- aax ad- dg- dd- aax aax aax aax aax aax aax aax aax ad- ac- dd- aax",
                "aax ab- aax bc- aa- cg- bb- bb- bb- bb- bb- bb- bb- bb- bb- ag- aa- dc- aax",
                "aax ab- aax bd- bg- cd- aax aax aax aax aax aax aax aax aax bd- cc- cd- aax",
                "aax ab- aax aax ab- aax aax bax bax bax bax bax bax bax aax aax aax aax aax",
                "aax bd- bb- bb- cd- aax bax bax bax bax bax bax bax bax bax bax bax bax bax",
                "aax aax aax aax aax aax bax bax bax bax bax bax bax bax bax bax bax bax bax"
            };

            doors.push_back(Door((7 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 4, true, 17));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 6, true, 27));
            doors.push_back(Door((8 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 10, true, 43));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 3, true, 15));
            doors.push_back(Door((10 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 1, true, 7));
            doors.push_back(Door((11 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 9, true, 39));
            doors.push_back(Door((12 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 8, true, 35));
            doors.push_back(Door((13 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 7, true, 31));
            doors.push_back(Door((14 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 2, true, 11));
            doors.push_back(Door((15 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 5, true, 23));

            items.push_back(Item((2 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 2, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 7, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 6, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 4, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 5, false));
            items.push_back(Item((17 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 7)
        {
            playerStartX = ((11 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 21;
            mapHeight = 17;
            map = {
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax aax aax ad- ac- dd- aax aax aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax aax aax bc- aa- dc- aax aax aax aax aax aax aax aax aax",
                "aax ad- bb- bb- bb- dd- aax aax aax bd- bg- cd- aax aax aax ad- bb- bb- bb- dd- aax",
                "aax ab- aax aax aax ab- aax aax aax aax ab- aax aax aax aax ab- aax aax aax ab- aax",
                "aax be- aax aax aax ab- aax aax aax ad- dg- dd- aax aax aax ab- aax aax aax be- aax",
                "aax aax aax ae- bb- da- bb- bb- bb- ag- aa- cg- bb- bb- bb- da- bb- ce- aax aax aax",
                "aax de- aax aax aax ab- aax aax aax bd- bg- cd- aax aax aax ab- aax aax aax de- aax",
                "aax ab- aax aax aax ab- aax aax aax aax ab- aax aax aax aax ab- aax aax aax ab- aax",
                "aax bd- bb- bb- bb- cd- aax aax aax aax ab- aax aax aax aax bd- bb- bb- bb- cd- aax",
                "aax aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax ad- bb- bb- cc- bb- bb- dd- aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax ab- aax aax aax aax aax ab- aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax ab- aax ad- ac- dd- aax ab- aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax bd- ce- bcx aa- cg- bb- cd- aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax aax aax bd- cc- cd- aax aax aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
            };

            doors.push_back(Door((4 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 2, true, 9));
            doors.push_back(Door((4 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 1, true, 5));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 4, true, 17));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 5, true, 21));
            doors.push_back(Door((8 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 3, true, 14));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 6, true, 25));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 8, true, 33));
            doors.push_back(Door((11 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 9, true, 38));
            doors.push_back(Door((11 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 1, true, 6));
            doors.push_back(Door((13 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 6, true, 27));
            doors.push_back(Door((13 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 7, true, 31));
            doors.push_back(Door((13 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 10, true, 41));
            doors.push_back(Door((17 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 2, true, 11));
            doors.push_back(Door((18 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 4, true, 19));
            doors.push_back(Door((18 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 3, true, 15));

            items.push_back(Item((2 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 4, false));
            items.push_back(Item((2 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 5, false));
            items.push_back(Item((4 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 7, false));
            items.push_back(Item((11 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((18 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 2, false));
            items.push_back(Item((20 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((20 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 6, false));
            items.push_back(Item((9 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((11 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 8)
        {
            playerStartX = ((6 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 30;
            mapHeight = 30;
            map = {
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                "aax aax aax aax ad- ac- dd- aax aax aax aax aax de- aax de- aax de- aax de- aax de- aax de- aax ad- bb- bb- dd- aax aax",
                "aax aax aax aax bc- aa- dc- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                "aax aax aax aax bd- bg- cd- aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                "aax aax aax aax aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax ab- aax aax",
                "aax aax aax ad- ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax ab- aax aax",
                "aax aax aax bc- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax ab- aax aax",
                "aax aax aax bd- bg- cc- bg- cd- aax aax aax bd- cc- ccx cc- bg- cc- ccx cc- ccx cc- ccx cc- ccx cc- cd- aax ab- aax aax",
                "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                "aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax ab- aax aax",
                "aax aax ad- ac- acx ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax ab- aax aax",
                "aax aax bc- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax ab- aax aax",
                "aax aax bd- bg- cc- bg- cc- bg- cd- aax aax aax bd- cc- ccx cc- ccx cc- bg- cc- ccx cc- ccx cc- cd- aax aax ab- aax aax",
                "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                "aax aax aax ab- aax ab- aax ab- aax aax aax aax aax aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax ab- aax aax",
                "aax ad- ac- acx ac- acx ac- dg- ac- dd- aax aax aax ad- dg- ac- dg- ac- dg- ac- dg- ac- dg- dd- aax aax aax ab- aax aax",
                "aax bc- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax bc- aa- aa- aa- aa- aa- aa- aa- aa- aa- dc- aax aax aax ab- aax aax",
                "aax bd- bg- cc- bg- cc- bg- cc- bg- cd- aax aax aax bd- cc- cc- cc- cc- bg- cc- cc- cc- cc- cd- aax aax aax ab- aax aax",
                "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax aax ab- aax aax",
                "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax aax ab- aax aax",
                "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax ad- dg- dd- aax",
                "aax aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax bc- aa- dc- aax",
                "aax aax acx aax ab- aax acx aax acx aax aax aax aax aax aax aax aax aax ab- aax aax aax aax aax aax aax bd- cc- cd- aax",
                "aax aax aax aax bd- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- bb- cd- aax aax aax aax aax aax aax aax aax aax aax",
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
            };

            //doors
            doors.push_back(Door((5 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 5, true, 22));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 5, true, 22));
            doors.push_back(Door((4 - 1) * TILE_SIZE, (17 - 1) * TILE_SIZE, 6, true, 26));
            doors.push_back(Door((6 - 1) * TILE_SIZE, (17 - 1) * TILE_SIZE, 6, true, 26));
            doors.push_back(Door((8 - 1) * TILE_SIZE, (17 - 1) * TILE_SIZE, 6, true, 26));
            doors.push_back(Door((3 - 1) * TILE_SIZE, (24 - 1) * TILE_SIZE, 8, true, 34));
            doors.push_back(Door((5 - 1) * TILE_SIZE, (24 - 1) * TILE_SIZE, 8, true, 34));
            doors.push_back(Door((7 - 1) * TILE_SIZE, (24 - 1) * TILE_SIZE, 8, true, 34));
            doors.push_back(Door((9 - 1) * TILE_SIZE, (24 - 1) * TILE_SIZE, 8, true, 34));
            doors.push_back(Door((15 - 1) * TILE_SIZE, (20 - 1) * TILE_SIZE, 7, true, 28));
            doors.push_back(Door((17 - 1) * TILE_SIZE, (20 - 1) * TILE_SIZE, 7, true, 28));
            doors.push_back(Door((19 - 1) * TILE_SIZE, (20 - 1) * TILE_SIZE, 7, true, 28));
            doors.push_back(Door((21 - 1) * TILE_SIZE, (20 - 1) * TILE_SIZE, 7, true, 28));
            doors.push_back(Door((23 - 1) * TILE_SIZE, (20 - 1) * TILE_SIZE, 7, true, 28));
            doors.push_back(Door((14 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 10, true, 40));
            doors.push_back(Door((16 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 10, true, 40));
            doors.push_back(Door((18 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 10, true, 40));
            doors.push_back(Door((20 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 10, true, 40));
            doors.push_back(Door((22 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 10, true, 40));
            doors.push_back(Door((24 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 10, true, 40));
            doors.push_back(Door((13 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 36));
            doors.push_back(Door((15 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 36));
            doors.push_back(Door((17 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 36));
            doors.push_back(Door((19 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 36));
            doors.push_back(Door((21 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 36));
            doors.push_back(Door((23 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 36));
            doors.push_back(Door((25 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 9, true, 36));
            //hidden doors
            doors.push_back(Door((8 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 4, true, 17, true));
            doors.push_back(Door((10 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 2, true, 9, true));
            doors.push_back(Door((11 - 1) * TILE_SIZE, (22 - 1) * TILE_SIZE, 3, true, 13, true));

            //keys
            items.push_back(Item((6 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 2, false));
            items.push_back(Item((6 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((6 - 1) * TILE_SIZE, (22 - 1) * TILE_SIZE, 5, false));
            items.push_back(Item((19 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 6, false));
            items.push_back(Item((19 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 7, false));
            items.push_back(Item((19 - 1) * TILE_SIZE, (22 - 1) * TILE_SIZE, 4, false));
            //coins
            items.push_back(Item((5 - 1) * TILE_SIZE, (29 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((11 - 1) * TILE_SIZE, (29 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((16 - 1) * TILE_SIZE, (29 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((19 - 1) * TILE_SIZE, (27 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((27 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((28 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((28 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((28 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((28 - 1) * TILE_SIZE, (20 - 1) * TILE_SIZE, 0, false));
            //diamond
            items.push_back(Item((28 - 1) * TILE_SIZE, (27 - 1) * TILE_SIZE, 1, false));
            //hidden items
            items.push_back(Item((12 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((13 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (5 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (7 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (8 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (9 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((10 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((11 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((11 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 6, true));
            items.push_back(Item((11 - 1) * TILE_SIZE, (12 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((12 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, true));
            items.push_back(Item((12 - 1) * TILE_SIZE, (11 - 1) * TILE_SIZE, 0, true));
        }

        else if (level == 9)
        {
            playerStartX = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 30;
            mapHeight = 30;
            map = {
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                "aax ad- ac- dd- aax aax aax aax ad- bb- bb- bb- bb- ac- bb- bb- bb- bb- bb- dd- aax ad- bb- bb- bb- bb- bb- bb- dd- aax",
                "aax bc- aa- cg- bb- dd- aax aax ab- aax aax aax aax ab- aax aax aax aax aax ab- aax ab- aax aax aax aax aax aax ab- aax",
                "aax bd- bg- cd- aax bd- bb- bb- cc- bb- bb- dd- aax ab- aax aax aax aax aax ab- aax ab- aax ad- bb- bb- dd- aax ab- aax",
                "aax aax ab- aax aax aax aax aax aax aax aax be- aax bd- bb- bb- dd- aax aax bc- bb- cd- aax ab- aax aax ab- aax ab- aax",
                "aax aax ab- aax aax aax aax aax aax de- aax aax aax aax aax aax ab- aax aax ab- aax aax aax ab- aax aax ab- aax be- aax",
                "aax ad- cc- bb- ac- bb- bb- dd- aax bd- dd- aax bax bax bax aax ab- aax aax ab- aax ad- bb- dc- aax aax ab- aax aax aax",
                "aax ab- aax aax ab- aax aax ab- aax aax ab- aax aax aax aax aax bc- bb- bb- dc- aax ab- aax ab- aax aax bd- bb- dd- aax",
                "aax ab- aax aax ab- aax aax bd- bb- bb- dc- aax ad- bb- bb- bb- dc- aax aax ab- aax ab- aax ab- aax aax aax aax ab- aax",
                "aax ab- aax aax ab- aax aax aax aax aax ab- aax ab- aax aax aax ab- aax aax ab- aax ab- aax ab- aax ad- ce- aax ab- aax",
                "aax bd- ac- bb- cd- aax de- aax aax aax ab- aax ab- aax aax aax bc- ac- ac- dc- aax be- aax bd- bb- cd- aax aax ab- aax",
                "aax aax ab- aax aax aax ab- aax ad- bb- cd- aax bd- bb- ce- aax bc- aa- aa- dc- aax aax aax aax aax aax aax aax ab- aax",
                "aax aax ab- aax ad- bb- cd- aax ab- aax aax aax aax aax aax aax bc- aa- aa- dc- aax ad- ac- ac- ac- ac- dd- aax ab- aax",
                "aax aax ab- aax ab- aax aax aax ab- aax aax aax ad- ac- bb- bb- cc- bg- cc- dc- aax bc- aa- aa- aa- aa- dc- aax ab- aax",
                "aax aax bd- bb- cd- aax ae- bb- cc- bb- dd- aax bd- cd- aax aax aax ab- aax ab- aax bc- aa- aa- aa- aa- dc- aax ab- aax",
                "aax aax aax aax aax aax aax aax aax aax ab- aax aax aax aax de- aax ab- aax ab- aax bd- cc- bg- cc- cc- cd- aax ab- aax",
                "aax ad- bb- bb- bb- bb- bb- bb- bb- bb- cc- bb- bb- dd- aax bd- bb- dc- aax ab- aax aax aax ab- aax aax aax aax ab- aax",
                "aax ab- aax aax aax aax aax aax aax aax aax aax aax ab- aax aax aax ab- aax bd- bb- dd- aax bd- bb- bb- dd- aax ab- aax",
                "aax bc- bb- bb- bb- bb- bb- bb- bb- ac- bb- bb- bb- cc- bb- dd- aax ab- aax aax aax ab- aax aax aax aax ab- aax ab- aax",
                "aax ab- aax aax aax aax aax aax aax ab- aax aax aax aax aax ab- aax ab- aax de- aax bd- bb- bb- bb- bb- cd- aax ab- aax",
                "aax ab- aax ad- bb- bb- bb- dd- aax ab- aax ae- bb- dd- aax ab- aax ab- aax ab- aax aax aax aax aax aax aax aax ab- aax",
                "aax ab- aax ab- aax aax aax ab- aax ab- aax aax aax ab- aax ab- aax be- aax ab- aax aax ad- bb- bb- bb- bb- bb- cd- aax",
                "aax ab- aax ab- aax ad- bb- cd- aax ab- aax ad- bb- cd- aax ab- aax aax aax ab- aax aax ab- aax aax aax aax aax aax aax",
                "aax ab- aax ab- aax ab- aax aax aax ab- aax ab- aax aax aax bd- bb- ac- bb- da- bb- bb- dc- aax ad- bb- bb- dd- aax aax",
                "aax ab- aax ab- aax ab- aax ad- bb- dc- aax bc- bb- ce- aax aax aax ab- aax ab- aax aax ab- aax ab- aax aax ab- aax aax",
                "aax ab- aax ab- aax ab- aax ab- aax ab- aax ab- aax aax aax aax aax ab- aax ab- aax aax ab- aax ab- aax aax ab- aax aax",
                "aax bd- bb- cd- aax bd- bb- cd- aax ab- aax ab- aax ad- bb- bb- bb- cd- aax ab- aax ad- cd- aax ab- aax ad- dg- dd- aax",
                "aax aax aax aax aax aax aax aax aax ab- aax ab- aax ab- aax aax aax aax aax ab- aax ab- aax aax ab- aax bc- aa- dc- aax",
                "aax ae- bb- bb- bb- bb- bb- bb- bb- cc- bb- cd- aax bd- bb- bb- bb- ce- aax be- aax bd- bb- bb- cd- aax bd- cc- cd- aax",
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
            };

            doors.push_back(Door((24 - 1) * TILE_SIZE, (17 - 1) * TILE_SIZE, 10, true, 40));
            doors.push_back(Door((28 - 1) * TILE_SIZE, (25 - 1) * TILE_SIZE, 6, true, 26));
            doors.push_back(Door((28 - 1) * TILE_SIZE, (26 - 1) * TILE_SIZE, 5, true, 22));

            //keys
            items.push_back(Item((14 - 1) * TILE_SIZE, (25 - 1) * TILE_SIZE, 3, false));
            items.push_back(Item((27 - 1) * TILE_SIZE, (10 - 1) * TILE_SIZE, 7, false));
            items.push_back(Item((29 - 1) * TILE_SIZE, (6 - 1) * TILE_SIZE, 2, false));
            //coins
            items.push_back(Item((22 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((22 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((22 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((22 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((23 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((23 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((23 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((23 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((24 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((24 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((24 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((24 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((25 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((25 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((25 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((25 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((26 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((26 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((26 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((26 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((27 - 1) * TILE_SIZE, (13 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((27 - 1) * TILE_SIZE, (14 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((27 - 1) * TILE_SIZE, (15 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((27 - 1) * TILE_SIZE, (16 - 1) * TILE_SIZE, 0, false));
            //diamond
            items.push_back(Item((28 - 1) * TILE_SIZE, (28 - 1) * TILE_SIZE, 1, false));
        }

        else if (level == 10)
        {
            playerStartX = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);
            playerStartY = ((3 - 1) * TILE_SIZE) + ((TILE_SIZE - 40) / 2);

            mapWidth = 30;
            mapHeight = 5;
            map = {
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax",
                "aax ad- ac- dd- aax ad- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- ac- dd- aax ad- ac- dd- aax",
                "aax bc- aa- cg- bb- ag- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- aa- cg- bb- ag- aa- dc- aax",
                "aax bd- cc- cd- aax bd- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cc- cd- aax bd- cc- cd- aax",
                "aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax aax"
            };

            items.push_back(Item((27 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((27 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((29 - 1) * TILE_SIZE, (2 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((29 - 1) * TILE_SIZE, (4 - 1) * TILE_SIZE, 0, false));
            items.push_back(Item((28 - 1) * TILE_SIZE, (3 - 1) * TILE_SIZE, 1, false));
        }
    }

    bool LevelCreation::CheckPos(int x, int y) const
    {
        int tx = x / TILE_SIZE;
        int ty = y / TILE_SIZE;

        if (ty < 0 || ty >= mapHeight || tx < 0 || tx >= mapWidth)
            return false;

        return map[ty][tx * 4 + 2] != 'x';
    }

    void LevelCreation::updateDoors(int characterState)
    {
        for (auto& door : doors)
        {
            door.updateLockState(characterState);
        }
    }

    bool LevelCreation::checkDoorCollision(int nx, int ny, int charSize) const
    {
        for (const auto& door : doors)
        {
            if (door.blocksMovement(nx, ny, charSize))
                return false; //door blocks movement
        }
        return true;
    }

    bool LevelCreation::tryUnlockDoorWithKey(int px, int py, int charSize, int itemFrame)
    {
        int centerX = px + charSize / 2;
        int centerY = py + charSize / 2;

        for (auto& door : doors)
        {
            //checks if player can open a door
            if (centerX >= door.x && centerX <= door.x + TILE_SIZE &&
                centerY >= door.y && centerY <= door.y + TILE_SIZE)
            {
                if (door.tryUnlockWithKey(itemFrame))
                {
                    return true; //key used
                }
            }
        }
        return false;
    }

    void LevelCreation::processDoorStates()
    {
        for (auto& door : doors)
        {
            if (!door.locked && !door.open)
            {
                door.openDoor();
            }
            else if (door.locked && door.open)
            {
                door.closeDoor();
            }
        }
    }

} // namespace Tmpl8