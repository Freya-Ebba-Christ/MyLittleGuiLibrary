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

#ifndef SLIDER_H
#define	SLIDER_H
#include <sliderbutton.h>
#include <SliderButtonEventHandler.h>
#include <SDL2Image.h>
#include <Point.h>

using namespace std;

template <typename T> class ChangeEventHandler {
public:

    ChangeEventHandler() {
    }

    ChangeEventHandler(T* t) {
        this->t = t;
    }

    ChangeEventHandler(const ChangeEventHandler& orig) {
    }

    virtual void onChange() {
        getT()->handleChange();
    }

    virtual ~ChangeEventHandler() {
    }

    virtual T* getT() {
        return t;
    }

private:
    T* t;
};

template <typename T> class Slider {
public:

    Slider() : height(30), width(100), minValue(0), maxValue(255), percentage(0), doubleValue(0) {
        position.setX(10);
        position.setY(768 - 300);
        color.setColor(255, 255, 255, 255);
    }

    void init(SDL2Image* anSDL2ImagePtr) {
        SDL_Surface * sliderButtonImage = IMG_Load("./SliderButton.png");
        sliderButton = new SliderButton<SliderButtonEventHandler<Slider> > ();
        sliderButton->setTexture(SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), sliderButtonImage));
        sliderButton->setMousePressedTexture(SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), sliderButtonImage));
        sliderButton->setMouseOverTexture(SDL_CreateTextureFromSurface(anSDL2ImagePtr->getRenderer(), sliderButtonImage));
        sliderButton->setDimensions(getHeigth(), getHeigth());
        sliderButton->setCaption("");
        sliderButton->setPosition(getPosition().getX(), getPosition().getY());
        sliderButton->setButtonID(SLIDER_BUTTON_HORIZONTAL_ID);
        sliderButtonEventHandler = new SliderButtonEventHandler<Slider > (this);
        sliderButton->addEventHandler(sliderButtonEventHandler);
        SDL_FreeSurface(sliderButtonImage);
        value = 0;
        originalPosition.setX(sliderButton->getPosition()->first);
        originalPosition.setY(sliderButton->getPosition()->second);
    }

    void checkCollision(SDL_Event* event) {
        this->sliderButton->checkCollision(event);
    }

    void paint(SDL2Image* anSDL2ImagePtr) {
        anSDL2ImagePtr->_lineRGBA((sliderButton->getWidth() / 2) + position.getX(), position.getY() - 5 + (getHeigth() / 2), position.getX() + getWidth() + sliderButton->getWidth()-(sliderButton->getWidth() / 2), position.getY() - 5 + (getHeigth() / 2), color.getR(), color.getG(), color.getB(), color.getA());
        sliderButton->paint(anSDL2ImagePtr);
        //anSDL2ImagePtr->_rectangleRGBA(position.getX(), position.getY() - 5, position.getX() + getWidth() + sliderButton->getWidth(), position.getY() + getHeigth(), color.getR(), color.getG(), color.getB(), color.getA());
    }

    Slider(const Slider& orig) {
    }

    virtual ~Slider() {

    }

    void onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle) {
        if (buttonPressed) {
            int oldValue = value;
            int x = sliderButton->getPosition()->first;
            int y = sliderButton->getPosition()->second;
            value += relX;

            if (value < 0) {
                value = 0;
            }
            if (value > getWidth()) {
                value = getWidth();
            }

            percentage = ((double) value / (double) getWidth());
            if (percentage < 0.0) {
                percentage = 0;
            } else if (percentage > 1.0) {

                percentage = 1.0;
            }
            this->doubleValue = minValue + (percentage * maxValue);

            if (x >= originalPosition.getX() && x <= (originalPosition.getX() + getWidth())) {
                sliderButton->setPosition(originalPosition.getX() + value, sliderButton->getPosition()->second);
            }
            if (oldValue != value) {
                for (int i = 0; i < eventHandler.size(); i++) {
                    eventHandler[i]->onChange();
                }
            }
        }
    }

    void setSliderPosition(double percentage) {
        int oldValue = value;
        value = (double) getWidth() * percentage;
        this->doubleValue = minValue + (percentage * maxValue);
        sliderButton->setPosition(originalPosition.getX() + value, sliderButton->getPosition()->second);
        if (oldValue != value) {
            for (int i = 0; i < eventHandler.size(); i++) {
                eventHandler[i]->onChange();
            }
        }
    }

    void onLButtonUp(int mX, int mY) {

        buttonPressed = false;
    }

    void onLButtonDown(int mX, int mY) {

        buttonPressed = true;
    }

    void setWidth(int value) {

        this->width = value;
    }

    void setHeight(int value) {

        this->height = value;
    }

    int getHeigth() {

        return this->height;
    }

    int getWidth() {

        return this->width;
    }

    double getDoubleValue() {

        return this->doubleValue;
    }

    double getPercentage() {

        return this->percentage;
    }

    int getMaxValue() {

        return this->maxValue;
    }

    int getMinValue() {

        return this->minValue;
    }

    void setMaxValue(int value) {

        this->maxValue = value;
    }

    void setMinValue(int value) {

        this->minValue = value;
    }

    void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {

        this->color.setColor(r, g, b, a);
    }

    void setPosition(int x, int y) {

        this->position.setX(x);
        this->position.setY(y);
    }

    Point<int>& getPosition() {
        return this->position;
    }

    void addEventHandler(T* value) {
        eventHandler.push_back(value);
    }

    T* removeEventHandler(T* value) {
        for (int i = 0; i < eventHandler.size(); i++) {
            if (eventHandler[i] == value) {
                eventHandler.erase(eventHandler.begin() + i);
            }
        }
    }

private:
    SliderButtonEventHandler<Slider>* sliderButtonEventHandler;
    SliderButton<SliderButtonEventHandler<Slider> >* sliderButton;
    bool buttonPressed;
    int height;
    int width;
    int value;
    int minValue;
    int maxValue;
    double percentage;
    Point<int> position;
    Point<int> originalPosition;
    double doubleValue;
    RGBA color;
    vector<T*> eventHandler;
};

#endif	/* SLIDER_H */

