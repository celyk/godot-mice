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
        return mouse_to_id[mouse];
    }

    std::map<MouseID, void*> id_to_mouse;
    std::map<void*, MouseID> mouse_to_id;

protected:
    void (*mouseMoved)(MouseID id, float x, float y) = nullptr;

    int fooCPP() {
        return 67;
    }

    void setupMouse();
public:
};