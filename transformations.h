#pragma once

namespace Tmpl8
{
    class Surface;
    class Sprite;

    class transformations
    {
    public:
        transformations();
        ~transformations();

        //update and draw transformations
        void update(float deltaTime, int& characterState, bool& isTransforming);
        void draw(Surface* screen, int x, int y);

        //check for transformation key presses
        void handleInput(int currentState, bool stickUnlocked);

        //checks if transforrmation is playing
        bool isPlaying() const { return isATransitionPlaying; }

    private:
        //transformation info
        bool isATransitionPlaying;
        int maxFramesOfTransition;
        int currentFrameOfTransition;
        Sprite* currentTransitionPlaying;
        float transitionTimer;
        const float FPS = 1.0f / 60.0f;
        int targetedCharacterState;
        bool transitionKeyIsPressed;

        //transformation sprites
        Sprite* cubeToBall;
        Sprite* cubeToTriangle;
        Sprite* cubeToStickfigure;
        Sprite* ballToCube;
        Sprite* ballToTriangle;
        Sprite* ballToStickfigure;
        Sprite* triangleToCube;
        Sprite* triangleToBall;
        Sprite* triangleToStickfigure;
        Sprite* stickfigureToCube;
        Sprite* stickfigureToBall;
        Sprite* stickfigureToTriangle;

        //starts transformation
        void startTransformation(Sprite* sprite, int frames, int targetState);
    };

} // namespace Tmpl8