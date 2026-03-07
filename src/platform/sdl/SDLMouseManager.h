#pragma once

#include <functional>
#include <map>

#include <SDL3/SDL.h>

typedef int MouseID;

class SDLMouseManager {
    void registerMouse(MouseID mouse);
    bool hasMouse(MouseID mouse);

    MouseID getMouseID(MouseID mouse_id) {
        return mouse_to_id[mouse_id];
    }

    std::map<MouseID, int> id_to_mouse;
    std::map<int, MouseID> mouse_to_id;

protected:
    void* setup_sdl_window(void* window_handle_ptr);

    std::function<void(int)> mouseConnected = nullptr;
    std::function<void(int, float, float)> mouseMoved = nullptr;
    std::function<void(int, float, float, int)> mouseButton = nullptr;

    void initializeMice();
    void processMice();
    void processMouseEvent(SDL_Event event);

public:
};