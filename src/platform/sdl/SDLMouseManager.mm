#include "SDLMouseManager.h"



void* SDLMouseManager::setup_sdl_window(void* window_handle_ptr)
{
    SDL_PropertiesID properties = SDL_CreateProperties();
    
    bool use_view = false;

    if (use_view) {
        int64_t view_handle = (int64_t)window_handle_ptr;
        SDL_Log("view_handle: %lld", view_handle);

        SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_VIEW_POINTER, (void*)view_handle);
    }
    else {
        int64_t window_handle = (int64_t)window_handle_ptr;
        SDL_Log("window_handle: %lld", window_handle);
        
        SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, (void*)window_handle);
    }

    SDL_Window* sdl_window_handle = SDL_CreateWindowWithProperties(properties);

    if (!sdl_window_handle)
    {
        printf("invalid handle");
        return nullptr;
    }

    SDL_SetWindowRelativeMouseMode(sdl_window_handle, true);

    return (void*)sdl_window_handle;
}

void SDLMouseManager::registerMouse(MouseID mouse_id)
{
    MouseID mouse_number = id_to_mouse.size();
    printf("registerMouse %d", mouse_number);

    mouseConnected(mouse_number);
    
    id_to_mouse[mouse_id] = mouse_number;
    mouse_to_id[mouse_number] = mouse_id;
}

bool SDLMouseManager::hasMouse(MouseID mouse_id)
{   
    if (id_to_mouse.find(mouse_id) != id_to_mouse.end()) {
        return true;
    }

    return false;
}

void SDLMouseManager::initializeMice()
{

}

void SDLMouseManager::processMice()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
       processMouseEvent(event);
    }
}

void SDLMouseManager::processMouseEvent(SDL_Event event)
{
    if (event.type == SDL_EVENT_KEY_DOWN) {
        SDL_Log("SDL_EVENT_KEY_DOWN: %d\n", event.key.key);
    }
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        //SDL_Log("SDL_EVENT_MOUSE_MOTION %d: %f %f", event.motion.which, event.motion.x, event.motion.y);
        
        if (!hasMouse(event.motion.which)) {
            registerMouse(event.motion.which);
        }

        mouseMoved(id_to_mouse[event.motion.which], event.motion.xrel, event.motion.yrel);
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        //SDL_Log("SDL_EVENT_MOUSE_BUTTON_DOWN %d: %f %f", event.button.which, event.button.x, event.button.y);
        
        mouseButton(id_to_mouse[event.button.which], 0.0, 0.0, event.button.button);
    }
}