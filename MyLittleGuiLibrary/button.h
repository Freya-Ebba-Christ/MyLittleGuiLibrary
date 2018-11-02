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

#ifndef BUTTON_H
#define	BUTTON_H

#include <iostream>
#include <vector>
#include <string>
#include <mouseEventHandler.h>
#include <SDL2Image.h>
#include <RGBA.h>


using namespace std;

template <typename T> class Button {
public:

    Button() : state(IDLE), point(new pair<int, int>()), alpha(255), buttonID(0), captionXoffset(0), captionYoffset(0) {
        captionColor.setColor(0, 0, 0, 255);
    }

    Button(const Button& orig) {
    }

    ~Button() {
        delete point;
        SDL_DestroyTexture(getTexture());
    }

    void setCaption(const char* caption) {
        this->caption = caption;
    }

    SDL_Texture* getTexture() {
        return imageTexture;
    }

    void setTexture(SDL_Texture* image) {
        this->imageTexture = image;
        SDL_SetTextureAlphaMod(this->imageTexture, this->alpha);
    }

    SDL_Texture* getMouseOverTexture() {
        return mouseOverImageTexture;
    }

    void setMouseOverTexture(SDL_Texture* image) {
        mouseOverImageTexture = image;
        SDL_SetTextureAlphaMod(this->mouseOverImageTexture, this->alpha);
    }

    SDL_Texture* getMousePressedTexture() {
        return mousePressedImageTexture;
    }

    void setMousePressedTexture(SDL_Texture* image) {
        mousePressedImageTexture = image;
        SDL_SetTextureAlphaMod(this->mousePressedImageTexture, this->alpha);
    }

    void setPosition(int x, int y) {
        point->first = x;
        point->second = y;
    }

    pair<int, int>* getPosition() {
        return point;
    }

    int getID() {
        return id;
    }

    void setID(int id) {
        this->id = id;
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

    void checkCollision(SDL_Event* event) {
        pair<int, int> center;
        center.first = getPosition()->first + (getWidth() / 2);
        center.second = getPosition()->second + (getHeight() / 2);
        int distance;
        this->state = IDLE;
        switch (event->type) {
            case SDL_MOUSEMOTION:
            {
                distance = sqrt(pow(center.first - event->motion.x, 2) + pow(center.second - event->motion.y, 2));
                if (distance < (getWidth() / 2) && distance < (getHeight() / 2)) {
                    state = MOUSE_OVER;
                    for (int i = 0; i < eventHandler.size(); i++) {
                        eventHandler[i]->onMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel, (event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                distance = sqrt(pow(center.first - event->button.x, 2) + pow(center.second - event->button.y, 2));
                switch (event->button.button) {
                    case SDL_BUTTON_LEFT:
                    {
                        if (distance < (getWidth() / 2) && distance < (getHeight() / 2)) {
                            state = MOUSE_PRESSED;
                            for (int i = 0; i < eventHandler.size(); i++) {
                                eventHandler[i]->setButtonID(getButtonID());
                                eventHandler[i]->onLButtonDown(event->button.x, event->button.y);
                            }
                        }
                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        if (distance < (getWidth() / 2) && distance < (getHeight() / 2)) {
                            state = MOUSE_PRESSED;
                            for (int i = 0; i < eventHandler.size(); i++) {
                                eventHandler[i]->setButtonID(getButtonID());
                                eventHandler[i]->onRButtonDown(event->button.x, event->button.y);
                            }
                        }
                        break;
                    }
                    case SDL_BUTTON_MIDDLE:
                    {
                        if (distance < (getWidth() / 2) && distance < (getHeight() / 2)) {
                            state = MOUSE_PRESSED;
                            for (int i = 0; i < eventHandler.size(); i++) {
                                eventHandler[i]->setButtonID(getButtonID());
                                eventHandler[i]->onMButtonDown(event->button.x, event->button.y);
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                distance = sqrt(pow(center.first - event->button.x, 2) + pow(center.second - event->button.y, 2));
                switch (event->button.button) {
                    case SDL_BUTTON_LEFT:
                    {
                        if (distance < (getWidth() / 2) && distance < (getHeight() / 2)) {
                            state = MOUSE_RELEASED;
                            for (int i = 0; i < eventHandler.size(); i++) {
                                eventHandler[i]->setButtonID(getButtonID());
                                eventHandler[i]->onLButtonUp(event->button.x, event->button.y);
                            }
                        }
                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        if (distance < (getWidth() / 2) && distance < (getHeight() / 2)) {
                            state = MOUSE_RELEASED;
                            for (int i = 0; i < eventHandler.size(); i++) {
                                eventHandler[i]->setButtonID(getButtonID());
                                eventHandler[i]->onRButtonUp(event->button.x, event->button.y);
                            }
                        }
                        break;
                    }
                    case SDL_BUTTON_MIDDLE:
                    {
                        if (distance < (getWidth() / 2) && distance < (getHeight() / 2)) {
                            state = MOUSE_RELEASED;
                            for (int i = 0; i < eventHandler.size(); i++) {
                                eventHandler[i]->setButtonID(getButtonID());
                                eventHandler[i]->onMButtonUp(event->button.x, event->button.y);
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    void setCaptionColor(RGBA& color) {
        this->captionColor.setColor(color.getR(), color.getG(), color.getB(), color.getA());
    }

    RGBA& getCaptionColor() {
        return this->captionColor;
    }

    void setAlpha(unsigned char value) {
        this->alpha = value;
        SDL_SetTextureAlphaMod(this->imageTexture, this->alpha);
        SDL_SetTextureAlphaMod(this->mouseOverImageTexture, this->alpha);
        SDL_SetTextureAlphaMod(this->mousePressedImageTexture, this->alpha);
    }

    unsigned char getAlpha() {
        return this->alpha;
    }

    void setButtonID(int value) {
        this->buttonID = value;
    }

    int getButtonID() {
        return this->buttonID;
    }

    void paint(SDL2Image* image) {
        SDL_Rect DestR;
        DestR.x = getPosition()->first;
        DestR.y = getPosition()->second;
        DestR.w = getWidth();
        DestR.h = getHeight();
        switch (state) {
            case IDLE:
                SDL_RenderCopy(image->getRenderer(), getTexture(), NULL, &DestR);
                break;
            case MOUSE_OVER:
                SDL_RenderCopy(image->getRenderer(), getMouseOverTexture(), NULL, &DestR);
                break;
            case MOUSE_PRESSED:
                SDL_RenderCopy(image->getRenderer(), getMousePressedTexture(), NULL, &DestR);
                break;
            case MOUSE_RELEASED:
                SDL_RenderCopy(image->getRenderer(), getTexture(), NULL, &DestR);
                break;
        }
        image->_stringRGBA((getPosition()->first + getWidth() / 4) + this->captionXoffset, (getPosition()->second + getHeight() + 10) + this->captionYoffset, caption, captionColor.getR(), captionColor.getG(), captionColor.getB(), captionColor.getA());
    }

    void setCaptionXoffset(int value) {
        this->captionXoffset = value;
    }

    void setCaptionYoffset(int value) {
        this->captionYoffset = value;
    }

private:

    enum STATE {
        IDLE = 0, MOUSE_OVER = 1, MOUSE_PRESSED = 2, MOUSE_RELEASED = 3
    };
    const char* caption;
    int width;
    int height;
    STATE state;
    int id;
    SDL_Texture* imageTexture;
    SDL_Texture* mouseOverImageTexture;
    SDL_Texture* mousePressedImageTexture;
    pair<int, int>* point;
    vector<T*> eventHandler;
    RGBA captionColor;
    unsigned char alpha;
    int buttonID;
    int captionXoffset;
    int captionYoffset;
};

#endif	/* BUTTON_H */

