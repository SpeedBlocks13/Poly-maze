#include "transformations.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Tmpl8
{
    transformations::transformations()
        : isATransitionPlaying(false)
        , maxFramesOfTransition(0)
        , currentFrameOfTransition(0)
        , currentTransitionPlaying(nullptr)
        , transitionTimer(0.0f)
        , targetedCharacterState(-1)
        , transitionKeyIsPressed(false)
    {
        //load all transformation sprites
        cubeToBall = new Sprite(new Surface("assets/cube to ball.png"), 45);
        cubeToTriangle = new Sprite(new Surface("assets/cube to triangle.png"), 50);
        cubeToStickfigure = new Sprite(new Surface("assets/cube to stickfigure.png"), 55);
        ballToCube = new Sprite(new Surface("assets/ball to cube.png"), 45);
        ballToTriangle = new Sprite(new Surface("assets/ball to triangle.png"), 35);
        ballToStickfigure = new Sprite(new Surface("assets/ball to stickfigure.png"), 55);
        triangleToCube = new Sprite(new Surface("assets/triangle to cube.png"), 50);
        triangleToBall = new Sprite(new Surface("assets/triangle to ball.png"), 35);
        triangleToStickfigure = new Sprite(new Surface("assets/triangle to stickfigure.png"), 55);
        stickfigureToCube = new Sprite(new Surface("assets/stickfigure to cube.png"), 55);
        stickfigureToBall = new Sprite(new Surface("assets/stickfigure to ball.png"), 55);
        stickfigureToTriangle = new Sprite(new Surface("assets/stickfigure to triangle.png"), 55);
    }

    transformations::~transformations()
    {
        delete cubeToBall;
        delete cubeToTriangle;
        delete cubeToStickfigure;
        delete ballToCube;
        delete ballToTriangle;
        delete ballToStickfigure;
        delete triangleToCube;
        delete triangleToBall;
        delete triangleToStickfigure;
        delete stickfigureToCube;
        delete stickfigureToBall;
        delete stickfigureToTriangle;
    }

    void transformations::startTransformation(Sprite* sprite, int frames, int targetState)
    {
        isATransitionPlaying = true;
        currentTransitionPlaying = sprite;
        currentFrameOfTransition = 0;
        maxFramesOfTransition = frames - 1;
        transitionTimer = 0.0f;
        targetedCharacterState = targetState;
    }

    void transformations::update(float deltaTime, int& characterState, bool& isTransforming)
    {
        if (isATransitionPlaying)
        {
            transitionTimer += deltaTime;

            if (transitionTimer >= FPS)
            {
                currentFrameOfTransition++;
                transitionTimer = 0.0f;

                if (currentFrameOfTransition >= maxFramesOfTransition)
                {
                    isATransitionPlaying = false;
                    characterState = targetedCharacterState;
                }
            }
        }

        isTransforming = isATransitionPlaying;
    }

    void transformations::draw(Surface* screen, int x, int y)
    {
        if (isATransitionPlaying && currentTransitionPlaying)
        {
            currentTransitionPlaying->SetFrame(currentFrameOfTransition);
            currentTransitionPlaying->Draw(screen, x, y);
        }
    }

    void transformations::handleInput(int currentState, bool stickUnlocked)
    {
        if (isATransitionPlaying)
            return; //don't process input during transition

        //transform to cube (C key)
        if (GetAsyncKeyState('C'))
        {
            if (!transitionKeyIsPressed)
            {
                if (currentState == 1) //ball to cube
                    startTransformation(ballToCube, 45, 0);
                else if (currentState == 2) //triangle to cube
                    startTransformation(triangleToCube, 50, 0);
                else if (currentState == 3) //stickman to cube
                    startTransformation(stickfigureToCube, 55, 0);

                transitionKeyIsPressed = true;
            }
        }
        //transform to ball (B key)
        else if (GetAsyncKeyState('B'))
        {
            if (!transitionKeyIsPressed)
            {
                if (currentState == 0) //cube to ball
                    startTransformation(cubeToBall, 45, 1);
                else if (currentState == 2) //triangle to ball
                    startTransformation(triangleToBall, 35, 1);
                else if (currentState == 3) //stickman to ball
                    startTransformation(stickfigureToBall, 55, 1);

                transitionKeyIsPressed = true;
            }
        }
        //transform to triangle (V key)
        else if (GetAsyncKeyState('V'))
        {
            if (!transitionKeyIsPressed)
            {
                if (currentState == 0) //cube to triangle
                    startTransformation(cubeToTriangle, 50, 2);
                else if (currentState == 1) //ball to triangle
                    startTransformation(ballToTriangle, 35, 2);
                else if (currentState == 3) //stickman to triangle
                    startTransformation(stickfigureToTriangle, 55, 2);

                transitionKeyIsPressed = true;
            }
        }
        //transform to stickman (N key)
        else if (GetAsyncKeyState('N') && stickUnlocked)
        {
            if (!transitionKeyIsPressed)
            {
                if (currentState == 0) //cube to stickman
                    startTransformation(cubeToStickfigure, 55, 3);
                else if (currentState == 1) //ball to stickman
                    startTransformation(ballToStickfigure, 55, 3);
                else if (currentState == 2) //triangle to stickman
                    startTransformation(triangleToStickfigure, 55, 3);

                transitionKeyIsPressed = true;
            }
        }
        else
        {
            transitionKeyIsPressed = false;
        }
    }

} // namespace Tmpl8