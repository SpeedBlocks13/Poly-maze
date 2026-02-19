#pragma once
#include "level creation.h"
#include "transformations.h"
#include <vector>
#include <chrono>

namespace Tmpl8
{
    class Surface;

    class Game
    {
    public:
        void SetTarget(Surface* surface) { screen = surface; }
        void Init();
        void Shutdown();
        void Tick(float deltaTime);
        void MouseUp(int button) {}
        void MouseDown(int button) {}
        void MouseMove(int x, int y) { mousex = x; mousey = y; }
        void KeyUp(int key) {}
        void KeyDown(int key) {}

    private:
        //core systems
        Surface* screen = nullptr;
        LevelCreation levelCreation;
        transformations playerTransformations;

        //input state
        int mousex = 0, mousey = 0;
        bool eIsPressed = false;

        //level state
        int level = 0;
        bool begin = false;

        //player state
        int px = 0, py = 0;
        int characterState = 0; //0=cube, 1=ball, 2=triangle, 3=stickman
        bool stickUnlocked = false;
        bool holdingItem = false;
        int itemHolding = -1;
        bool isATransitionPlaying = false;

        //progression
        int money = 0;
        int moneyGainedInLevel = 0;
        bool finished = false;

        //speedrun
        bool speedrunMode = false;
        bool fullGameSpeedrun = false;
        bool oneLevelSpeedrun = false;
        float time = 0.0f;
        std::vector<float> fastestTime;
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point currentTime;

        //tutorial
        std::vector<int> tutorialX;
        std::vector<int> tutorialY;
        std::vector<bool> tutorialHidden;

        //helper methods
        void createLevel(Surface* screen, int startmidX, int startmidY, int plx, int ply);
        void checkItem(int px, int py);
        bool checkDoor(int nx, int ny);
        void tutorialCheck();
    };

} // namespace Tmpl8