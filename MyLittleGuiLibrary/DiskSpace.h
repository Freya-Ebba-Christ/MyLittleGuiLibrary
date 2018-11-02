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

#ifndef DISKSPACE_H
#define DISKSPACE_H

#include <sys/statfs.h>
#include <iomanip>
#include <sstream>
#include <SDL2Panel.h>
#include <Point.h>

using namespace std;

class DiskSpace : public SDL2Panel {
public:

    DiskSpace() {
        textColor.setColor(255, 255, 255, 200);
    }

    virtual ~DiskSpace() {

    }

    void paint(SDL2Image* image) {
        float usage = getFreeDiskSpace(path);
        Point<int>& position = getPosition();
        image->_boxRGBA(position.getX(), position.getY(), position.getX() + SDL2Panel::getWidth(), position.getY() + SDL2Panel::getHeight() - 2, backgroundColor.getR(), backgroundColor.getG(), backgroundColor.getB(), backgroundColor.getA());
        image->_boxRGBA(position.getX(), position.getY(), position.getX() + SDL2Panel::getWidth() * usage, position.getY() + getHeight() - 2, barColor.getR(), barColor.getG(), barColor.getB(), barColor.getA());
        image->_rectangleRGBA(position.getX(), position.getY(), position.getX() + SDL2Panel::getWidth(), position.getY() + SDL2Panel::getHeight(), borderColor.getR(), borderColor.getG(), borderColor.getB(), borderColor.getA());
        std::ostringstream buff;
        buff << "Disk usage: %" << setprecision(2) << usage * 100;
        string freeSpace = buff.str();
        image->_stringRGBA(position.getX() + 30, position.getY() + (SDL2Panel::getHeight() / 2) - 4, freeSpace.c_str(), textColor.getR(), textColor.getG(), textColor.getB(), textColor.getA());
    }

    void setPath(const char* path) {
        this->path = path;
    }

    void setTextColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->textColor.setColor(r, g, b, a);
    }

    void setBackgroundColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->backgroundColor.setColor(r, g, b, a);
    }

    void setBarColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->barColor.setColor(r, g, b, a);
    }

    void setBorderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        this->borderColor.setColor(r, g, b, a);
    }
    
private:

    float getFreeDiskSpace(const char* absoluteFilePath) {
        struct statfs buf;
        if (!statfs(absoluteFilePath, &buf)) {
            unsigned long blksize, blocks, freeblks, free;
            float disk_size, used;
            blksize = buf.f_bsize;
            blocks = buf.f_blocks;
            freeblks = buf.f_bfree;

            disk_size = blocks*blksize;
            free = freeblks*blksize;
            used = disk_size - free;
            return used / disk_size;
        } else {
            return -1;
        }
    }

    const char* path;
    RGBA backgroundColor;
    RGBA barColor;
    RGBA borderColor;
    RGBA textColor;
};

#endif /* DISKSPACE_H */

