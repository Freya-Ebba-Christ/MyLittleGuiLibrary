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

#ifndef DOWNARROWBUTTONEVENTHANDLER_H
#define DOWNARROWBUTTONEVENTHANDLER_H
#include <mouseEventHandler.h> 

template <typename T> class DownArrowButtonEventHandler : public MouseEventHandler<T> {
public:

    DownArrowButtonEventHandler() {
    }

    DownArrowButtonEventHandler(T* t) : MouseEventHandler<T>(t) {

    }

    DownArrowButtonEventHandler(const DownArrowButtonEventHandler & orig) {
    }

    virtual ~DownArrowButtonEventHandler() {
    }

    int getButtonID() {
        return this->buttonID;
    }

    void setButtonID(int value) {
        this->buttonID = value;
    }

    void onLButtonUp(int mX, int mY) {
        MouseEventHandler<T>::getT()->handleDownArrowButton(getButtonID());
    }
private:
    int buttonID;
};

#endif /* DOWNARROWBUTTONEVENTHANDLER_H */

