/* 
 *    Copyright [2013] Olaf - blinky0815 - christ ]
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

#ifndef OBSERVABLE_H
#define	OBSERVABLE_H

#include <mutex>
#include <vector>
#include <algorithm>
#include <iterator>
#include <observer.h>

using namespace std;

class Observable {
public:

    Observable() {
    }

    virtual ~Observable() {
    }

    void addObserver(Observer *observer) {
        std::lock_guard<std::mutex> lock(_mutex);

        if (!binary_search(observers.begin(), observers.end(), observer)) {
            observers.push_back(observer);
        }
    }

    void notifyObservers() {
        for (typename vector<Observer *>::iterator it = observers.begin(); it != observers.end(); it++) {
            (*it)->update();
        }
    }

    template <typename Object> inline void notifyObservers(Object* object) {
        for (typename vector<Observer *>::iterator it = observers.begin(); it != observers.end(); it++) {
            (*it)->update(object);
        }
    }

    void deleteObserver(Observer *observer) {
        std::lock_guard<std::mutex> lock(_mutex);
        const int index = std::distance(observers.begin(), std::lower_bound(observers.begin(), observers.end(), observer));
        if (observers.size() > 0 and index < observers.size()) {
            observers.erase(observers.begin() + index);
        }
    }

    void deleteObservers() {
        std::lock_guard<std::mutex> lock(_mutex);
        vector<Observer *>().swap(observers);
    }

    const int numObservers() {
        std::lock_guard<std::mutex> lock(_mutex);
        return observers.size();
    }

private:
    std::vector<Observer *> observers;
    std::mutex _mutex;
};

#endif	/* ABSTRACTOBSERVABLE_H */

