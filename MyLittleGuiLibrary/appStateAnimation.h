/* 
 *    Copyright [2012] Olaf - blinky0815 - christ ]
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 * 
 * Author: blinky0815
 * email: christ_o@gmx.de
 */

#ifndef APPSTATEANIMATION_H
#define	APPSTATEANIMATION_H

#include <iostream>
#include <vector>
#include <string>
#include <mouseEventHandler.h>
#include <Point.h>
#include "RGBA.h"

using namespace std;

class AppStateAnimation {
public:

    AppStateAnimation() : point(new Point<int>()), lastTime(SDL_GetTicks()), animationDelay(200), enabled(false), animationStep(0), maxAnimationsSteps(5) {
        circleColor.setColor(100, 100, 255, 255);
    };

    virtual ~AppStateAnimation() {
        delete point;
    };

    void setCircleColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->circleColor.setColor(r, g, b, a);
    }

    void paint(SDL2Image* image) {
        if (enabled) {
            if ((SDL_GetTicks() - lastTime) > animationDelay) {
                lastTime = SDL_GetTicks();
                if (animationStep == maxAnimationsSteps) {
                    animationStep = 0;
                }
                animationStep++;
            }
            image->_filledCircleRGBA(getPosition()->getX() - 1 + getWidth() / 2, getPosition()->getY() + getHeight() / 2, (getWidth() / 2) - 3 + animationStep, circleColor.getR(), circleColor.getG(), circleColor.getB(), circleColor.getA());
        }
    }

    void setDimensions(int width, int height) {
        this->width = width;
        this->height = height;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    void setPosition(int x, int y) {
        point->setX(x);
        point->setY(y);
    }

    Point<int>* getPosition() {
        return this->point;
    }

    void setEnabled(bool value) {
        this->enabled = value;
    }

    bool isEnabled() {
        return this->enabled;
    }

private:
    uint32_t lastTime;
    int animationStep;
    int maxAnimationsSteps;
    uint32_t animationDelay;
    int width;
    int height;
    Point<int>* point;
    bool enabled;
    RGBA circleColor;
};

#endif	/* APPSTATEANIMATION_H */

