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

#ifndef SLIDERBUTTON_H
#define	SLIDERBUTTON_H

#include <iostream>
#include <vector>
#include <string>
#include <mouseEventHandler.h>
#include <SDL2Image.h>
#include <RGBA.h>
#include <button.h>

using namespace std;

template <typename T> class SliderButton : public Button<T> {
public:

    void checkCollision(SDL_Event* event) {
        Button<T>::checkCollision(event);
    }

    void paint(SDL2Image* image) {
        Button<T>::paint(image);
    }

    int getSliderHeight() {
        return this->sliderHeight;
    }

    void setSliderHeight(int value) {
        this->sliderHeight = value;
    }

    int getSliderWidth() {
        return this->sliderWidth;
    }

    void setSliderWidth(int value) {
        this->sliderWidth = value;
    }

private:
    int sliderWidth;
    int sliderHeight;
    double sliderValue;
};

#endif	/* SLIDERBUTTON_H */

