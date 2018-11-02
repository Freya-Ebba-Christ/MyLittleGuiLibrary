/* 
 *    Copyright [2014] Olaf - blinky0815 - christ ]
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

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <SDL2Image.h>
#include <Point.h>
#include <RGBA.h>

class ProgressBar {
public:

    ProgressBar() : percentage(1.0) {
    }

    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->color.setColor(r, g, b, a);
    }

    void paint(SDL2Image* image) {
        if (isVisible()) {
            image->_boxRGBA(position.getX(), position.getY(), getWidth() + position.getX(), getHeight() + position.getY(), color.getR(), color.getG(), color.getB(), color.getA());
            image->_boxRGBA(position.getX() + 20, (position.getY() + getHeight() / 2) - (getHeight() / 2) + 20, position.getX() + 20 + (getWidth() - 40) * percentage, (position.getY() + getHeight() / 2) + (getHeight() / 2) - 20, color.getR(), color.getG(), color.getB(), color.getA()*1.5);
            SDL_RenderCopy(image->getRenderer(), this->text, NULL, &rect);
        }
    }

    void setPosition(int x, int y) {
        position.setX(x);
        position.setY(y);
    }

    void setText(SDL_Texture *text) {
        this->text = text;
        int w, h;
        SDL_QueryTexture(text, NULL, NULL, &w, &h);
        rect.x = position.getX() + (getWidth() / 2) - (w / 2);

        rect.y = position.getY() + (getHeight() / 2) - (h / 2);
        rect.w = w;
        rect.h = h;
    }

    void update(int steps) {

        this->percentage = (float) steps / (float) getNumSteps();
    }

    Point<int>& getPosition() {

        return this->position;
    }

    bool isVisible() {

        return this->visble;
    }

    void setVisible(bool value) {

        this->visble = value;
    }

    int getWidth() {

        return this->width;
    }

    int getHeight() {

        return this->height;
    }

    void setWidth(int value) {

        this->width = value;
    }

    void setHeight(int value) {

        this->height = value;
    }

    int getNumSteps() {

        return this->numSteps;
    }

    void setNumSteps(int value) {

        this->numSteps = value;
    }

    virtual ~ProgressBar() {

    }
private:
    int width;
    int height;
    Point<int> position;
    RGBA color;
    int numSteps;
    float percentage;
    SDL_Texture *text;
    SDL_Rect rect;
    bool visble = false;
};

#endif /* PROGRESSBAR_H */

