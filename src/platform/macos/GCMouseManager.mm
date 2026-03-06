#include "GCMouseManager.h"

void GCMouseManager::registerMouse(void* mouse)
{
    printf("registerMouse");

    ((GCMouse*)mouse).mouseInput.mouseMovedHandler = ^(GCMouseInput *mouseInput, float deltaX, float deltaY) {
        //printf("mouseMovedHandler");

        if (mouseMoved != nullptr) {
            mouseMoved(getMouseID(nullptr), deltaX, deltaY);
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
        //NSLog(mouse);
        printf("Mouse found!!!");

        if ([mouse isKindOfClass:[GCMouse class]]) {
            GCMouse *mouse2 = (GCMouse *)mouse;
            //subscribeMouseEvents(mouse);
        }

        registerMouse((void*)mouse);
    }
}