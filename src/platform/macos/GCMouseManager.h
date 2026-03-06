#pragma once

#include <iostream>
#include <map>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <GameController/GameController.h>
#else
#endif

typedef int MouseID;

class GCMouseManager {
    void registerMouse(void* mouse);

    MouseID getMouseID(void* mouse) {
        return 0;
    }

    std::map<MouseID, void*> mouse;

protected:
    void (*mouseMoved)(MouseID id, float x, float y) = nullptr;

    int fooCPP() {
        return 67;
    }

    void setupMouse();
public:
};