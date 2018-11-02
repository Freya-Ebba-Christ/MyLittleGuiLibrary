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

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <SDL2Image.h>
#include <TimeConverter.h>
#include <iomanip>
#include <RGBA.h>
#include <chrono>
#include <Point.h>

using namespace std;

class Stopwatch {
public:

    Stopwatch() : running(false), startTime(0), stopTime(0), currentTime(0), currentHours(0), currentMinutes(0), currentSeconds(0), currentMilliseconds(0), width(200), height(150), delay(1000), blink(true), normalClock(true), showDate(false) {
        setPosition(0, 0);
        lastTime = SDL_GetTicks();
        title = string("Timer");
    }

    virtual ~Stopwatch() {
        TTF_CloseFont(this->font);
    }

    void paint(SDL2Image* image) {

        updateTime();
        //timeStringStream.clear();
        stringstream timeStringStream;
        timeStringStream << std::setfill('0') << std::setw(2) << currentHours << ":" << std::setfill('0') << std::setw(2) << currentMinutes << ":" << std::setfill('0') << std::setw(2) << currentSeconds << endl;
        image->_roundedBoxRGBA(position.getX() + 25, position.getY() + 12, position.getX() + getWidth(), position.getY() + getHeight(), 5, backgroundColor.getR(), backgroundColor.getG(), backgroundColor.getB(), backgroundColor.getA());

        SDL_Color textColor;
        textColor.r = digitColor.getR();
        textColor.g = digitColor.getG();
        textColor.b = digitColor.getB();
        textColor.a = digitColor.getA();
        string strg = timeStringStream.str();
        //changeDigitColor();

        SDL_Surface *surf = TTF_RenderText_Blended(font, strg.c_str(), textColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(image->getRenderer(), surf);
        SDL_FreeSurface(surf);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, digitColor.getA());
        int w, h;
        SDL_Rect rect;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        rect.x = position.getX() + 25;
        rect.y = position.getY() + 12;
        rect.w = w;
        rect.h = h;
        SDL_RenderCopy(image->getRenderer(), texture, NULL, &rect);
        image->_stringRGBA(position.getX() + 25, position.getY() + 12, title.c_str(), 0, 0, 0, 255);


        if (blink) {
            image->_boxRGBA(rect.x + 44, rect.y + 19, rect.x + 49, rect.y + 24, 255, 0, 0, digitColor.getA());
            image->_boxRGBA(rect.x + 44, rect.y + 30, rect.x + 49, rect.y + 35, 255, 0, 0, digitColor.getA());
            image->_boxRGBA(rect.x + 97, rect.y + 19, rect.x + 102, rect.y + 24, 255, 0, 0, digitColor.getA());
            image->_boxRGBA(rect.x + 97, rect.y + 30, rect.x + 102, rect.y + 35, 255, 0, 0, digitColor.getA());
        }

        if ((SDL_GetTicks() - lastTime) > delay) {
            blink = !blink;
            lastTime = SDL_GetTicks();
        }
        SDL_DestroyTexture(texture);
    }

    void setDelay(int value) {
        this->delay = value;
    }

    void reset() {

        currentHours = 0;
        currentMinutes = 0;
        currentSeconds = 0;
    }

    void start() {

        reset();
        this->running = true;
        startTime = SDL_GetTicks();
    }

    void pause() {
        this->running = false;
    }

    void resume() {
        this->running = true;
    }

    void stop() {

        this->running = false;
        stopTime = SDL_GetTicks();
    }

    void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {

        this->backgroundColor.setColor(r, g, b, a);
    }

    void setDigitColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {

        this->digitColor.setColor(r, g, b, a);
    }

    void setColonColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {

        this->colonColor.setColor(r, g, b, a);
    }

    void setWidth(int value) {

        this->width = value;
    }

    int getWidth() {

        return this->width;
    }

    void setHeight(int value) {

        this->height = value;
    }

    int getHeight() {

        return this->height;
    }

    void setPosition(int x, int y) {

        this->position.setX(x);
        this->position.setY(y);
    }

    Point<int>& getPosition() {

        return this->position;
    }

    void setFont(TTF_Font* font) {
        this->font = font;
        if (font == nullptr) {

            cout << "font is NULL" << endl;
        }
    }

    RGBA& getBackgroundColor() {

        return this->backgroundColor;
    }

    RGBA& getDigitColor() {

        return this->digitColor;
    }

    RGBA& getColonColor() {
        return this->colonColor;
    }

    int getCurrentTime() {
        return this->currentTime;
    }

    void setTitle(string title) {
        this->title = title;
    }

    string& getTitle() {
        return this->title;
    }

    tm* getDate() {
        return this->date;
    }

    double getMilliseconds() {
        std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_span = t1 - t0;
        return time_span.count();
    }

    int getHour() {
        return timeConverter.millisToHours(getMilliseconds()) % 24;
    }

    int getMinute() {
        return timeConverter.millisToMinutes(getMilliseconds()) % 60;
    }

    int getSeconds() {
        return timeConverter.millisToSeconds(getMilliseconds()) % 60;
    }

    int getMillis() {
        return timeConverter.millisToMillis(getMilliseconds()) % 1000;
    }

    void updateTime() {
        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        time_t tnow = std::chrono::high_resolution_clock::to_time_t(now);

        this->date = std::localtime(&tnow);

        if (this->running) {
            currentTime = SDL_GetTicks() - startTime;
        }

        currentHours = timeConverter.millisToHours(currentTime) % 24;
        currentMinutes = timeConverter.millisToMinutes(currentTime) % 60;
        currentSeconds = timeConverter.millisToSeconds(currentTime) % 60;

        if (!this->running && normalClock) {
            currentHours = date->tm_hour;
            currentMinutes = date->tm_min;
            currentSeconds = date->tm_sec;
        }

        currentMilliseconds = currentTime;
    }

private:

    void changeDigitColor() {
        if (this->currentHours == 17 && currentMinutes == 21 && currentSeconds == 0) {
            digitColor.setColor((int) (digitColor.getR() / 2.0), (int) (digitColor.getG() / 2.0), (int) (digitColor.getB() / 2.0), digitColor.getA());
        } else if (this->currentHours == 17 && currentMinutes == 23 && currentSeconds == 0) {
            digitColor.setColor((int) (digitColor.getR() * 2.0), (int) (digitColor.getG() * 2.0), (int) (digitColor.getB() * 2.0), digitColor.getA());
        }
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> t0 = std::chrono::high_resolution_clock::now();
    tm *date;
    int startTime;
    int stopTime;
    int currentTime;
    bool running;
    bool normalClock;
    bool showDate;
    int currentHours;
    int currentMinutes;
    int currentSeconds;
    int currentMilliseconds;
    TimeConverter timeConverter;
    RGBA backgroundColor;
    RGBA digitColor;
    RGBA colonColor;
    Point<int> position;
    int width;
    int height;
    TTF_Font* font;
    int delay;
    bool blink;
    int lastTime;
    string title;
};

#endif /* STOPWATCH_H */

