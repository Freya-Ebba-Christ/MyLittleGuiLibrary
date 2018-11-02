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

#ifndef FILEINFO_H
#define	FILEINFO_H

#include <iostream>
#include <sys/statfs.h>
#include <SDL2Image.h>
#include <RGBA.h>
#include <Point.h>
#include <sstream>

using namespace std;

class FileInfo {
public:

    FileInfo() {

    }

    void paint(SDL2Image* image) {
        image->_boxRGBA(position.getX(), position.getY(), position.getX() + getWidth(), position.getY() + getHeight(), backgroundColor.getR(), backgroundColor.getG(), backgroundColor.getB(), backgroundColor.getA());
        image->_rectangleRGBA(position.getX(), position.getY(), position.getX() + getWidth(), position.getY() + getHeight(), borderColor.getR(), borderColor.getG(), borderColor.getB(), borderColor.getA());
        image->_stringRGBA(position.getX() + 5, position.getY() + (getHeight() / 2) - 4, pathInfo.c_str(), 255, 255, 255, 200);
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

    void setPath(const char* path) {
        this->path = path;
        std::ostringstream buff;
        buff << "Path:" << this->path;
        pathInfo.clear();
        pathInfo = buff.str();
    }

    void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->backgroundColor.setColor(r, g, b, a);
    }

    void setBorderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->borderColor.setColor(r, g, b, a);
    }

    virtual ~FileInfo() {

    }
private:
    Point<int> position;
    int width;
    int height;
    const char* path;
    RGBA backgroundColor;
    RGBA borderColor;
    string pathInfo;
};

#endif	/* FILEINFO_H */

