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

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

using namespace std;

template <typename T> class Point {
public:

    Point() {

    }

    Point(T x, T y) {
        this->point.first = x;
        this->point.second = y;
    }

    bool operator<(Point<T> &p) {
        return getX() < p.getX() || (getX() == p.getX() && getY() < p.getY());
    }

    T getX() {
        return this->point.first;
    }

    T getY() {
        return this->point.second;
    }

    void setX(T x) {
        this->point.first = x;
    }

    void setY(T y) {
        this->point.second = y;
    }

    double euclideanDistance(Point<T>& p) {
        int dx = getX() - p.getX();
        int dy = getY() - p.getY();
        int dx2 = dx*dx;
        int dy2 = dy*dy;
        return sqrt(dx2 + dy2);
    }

    double cross(Point &A, Point &B) {
        return (A.getX() - getX()) * (B.getY() - getY()) - (A.getY() - getY()) * (B.getX() - getX());
    }

    float getAngleOfLineBetweenTwoPoints(Point<float> p) {
        float xDiff = getX() - p.getX();
        float yDiff = getY() - p.getY();
        return atan2(yDiff, xDiff) * (180 / M_PI);
    }

private:
    pair<T, T > point;
};

#endif /* POINT_H */

