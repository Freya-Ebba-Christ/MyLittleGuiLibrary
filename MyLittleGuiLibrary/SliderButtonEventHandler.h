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

#ifndef SLIDERBUTTONEVENTHANDLER_H
#define	SLIDERBUTTONEVENTHANDLER_H
#include <mouseEventHandler.h> 

template <typename T> class SliderButtonEventHandler : public MouseEventHandler<T> {
public:

    SliderButtonEventHandler() {
    }

    SliderButtonEventHandler(T* t) : MouseEventHandler<T>(t) {

    }

    SliderButtonEventHandler(const SliderButtonEventHandler & orig) {
    }

    virtual ~SliderButtonEventHandler() {
    }

    int getButtonID() {
        return this->buttonID;
    }

    void setButtonID(int value) {
        this->buttonID = value;
    }

    void onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle) {
        if (buttonPressed) {
            MouseEventHandler<T>::getT()->onMouseMove(mX, mY, relX, relY, left, right, middle);
        }
    }

    void onLButtonUp(int mX, int mY) {
        MouseEventHandler<T>::getT()->onLButtonUp(mX, mY);
        buttonPressed = false;
    }

    void onLButtonDown(int mX, int mY) {
        MouseEventHandler<T>::getT()->onLButtonDown(mX, mY);
        buttonPressed = true;
    }

private:
    int buttonID;
    bool buttonPressed;
};

#endif	/* SLIDERBUTTONEVENTHANDLER_H */

