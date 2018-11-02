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

#ifndef MOUSEEVENTHANDLER_H
#define	MOUSEEVENTHANDLER_H

#include <iostream>
#include <vector>
#include <SDL2Image.h>

using namespace std;

template <typename T> class MouseEventHandler {
public:

    MouseEventHandler() {
    }

    MouseEventHandler(T* t) {
        this->t = t;
    }

    MouseEventHandler(const MouseEventHandler& orig) {
    }

    virtual ~MouseEventHandler() {
    }

    virtual void onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle) {

    }

    virtual void onLButtonDown(int mX, int mY) {

    }

    virtual void onLButtonUp(int mX, int mY) {

    }

    virtual void onRButtonDown(int mX, int mY) {

    }

    virtual void onRButtonUp(int mX, int mY) {

    }

    virtual void onMButtonDown(int mX, int mY) {

    }

    virtual void onMButtonUp(int mX, int mY) {

    }

    virtual T* getT() {
        return t;
    }

    virtual int getButtonID() {
    }

    virtual void setButtonID(int value) {
    }


private:
    T* t;
};

#endif	/* MOUSEEVENTHANDLER_H */

