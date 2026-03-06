#include "GCMouseManager.h"

void GCMouseManager::registerMouse(void* mouse)
{   
    MouseID id = id_to_mouse.size();

    id_to_mouse[id] = mouse;
    mouse_to_id[mouse] = id;

    GCMouse* gc_mouse = (GCMouse*)mouse;
    
    gc_mouse.handlerQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);

    gc_mouse.mouseInput.mouseMovedHandler = [this, gc_mouse](GCMouseInput *mouseInput, float deltaX, float deltaY) {
        //printf("mouseMovedHandler");

        if (mouseMoved != nullptr) {
            mouseMoved(getMouseID(gc_mouse), deltaX, deltaY);
        }
    };
}

void mouseMoved(MouseID id, float x, float y) {

}

void GCMouseManager::setupMouse()
{
    NSArray *connectedMice = GCMouse.mice;
    
    //printf("Intialize ", fooCPP());

    for (GCMouse *mouse in connectedMice) {
        registerMouse((void*)mouse);
    }
}