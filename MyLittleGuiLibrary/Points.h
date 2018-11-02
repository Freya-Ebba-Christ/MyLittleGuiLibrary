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

#ifndef POINTS_H
#define	POINTS_H

#include <string.h>
#include <iostream>
#include <Point.h>

using namespace std;

template <typename T> class Points {
public:

    Points() {
    }

    void clear() {
        vector < Point < T >> ().swap(points);
    }

    void add(Point < T > point) {
        points.push_back(point);
    }

    Point<T>& getPoint(int index) {
        return this->points.at(index);
    }

    T getX(int index) {
        return points.at(index).getX();

    }

    T getY(int index) {
        return points.at(index).getY();
    }

    int getLastX() {
        return points.at(points.size() - 1).getX();
    }

    int getLastY() {
        return points.at(points.size() - 1).getY();
    }

    bool isEmpty() {
        return points.size() == 0;
    }

    double size() {
        return (double) points.size();
    }

private:
    vector<Point<T >> points;
};

#endif	/* POINTS_H */

