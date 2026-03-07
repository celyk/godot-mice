#include "PeripheralServerSDL.h"

#include <godot_cpp/core/class_db.hpp>
// #include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/display_server.hpp>
// #include <godot_cpp/classes/thread.hpp>


#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


using namespace godot;


void PeripheralServerSDL::process_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_EVENT_MOUSE_MOTION:
                send_mouse_motion(0, Vector2());
                break;
            
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                send_mouse_button(0, int(), true);

                break;
            
            case SDL_EVENT_MOUSE_BUTTON_UP:
                send_mouse_button(0, int(), false);

                break;
            
            case SDL_EVENT_KEY_DOWN:
                // TODO
                break;
            
            default:
                break;
        }
    }
}

void PeripheralServerSDL::initialize()
{   
    initialize_sdl_window();


    // Process events in the main game loop.
    SceneTree* tree = (SceneTree*)Engine::get_singleton()->get_main_loop();
    tree->connect("process_frame", callable_mp(this, &PeripheralServerSDL::process_events));
}

void PeripheralServerSDL::initialize_sdl_window()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    
    void* native_window = (void*)DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::WINDOW_HANDLE, DisplayServer::MAIN_WINDOW_ID);
    

    SDL_PropertiesID properties = SDL_CreateProperties();

#if defined(MACOS_ENABLED)
    SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, native_window);
#elif defined(IOS_ENABLED)
    SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_UIKIT_WINDOW_POINTER, native_window);
#elif defined(LINUX_ENABLED)
    SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_X11_WINDOW_NUMBER, native_window);
#elif defined(ANDROID_ENABLED)
    //SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_ANDROID_WINDOW_POINTER, native_window);
#elif defined(WINDOWS_ENABLED)
    SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, native_window);
#endif
    
    SDL_Window* sdl_window_handle = SDL_CreateWindowWithProperties(properties);
}

void PeripheralServerSDL::attach_mouse(DeviceID device_id)
{
    emit_signal("device_added", device_id);
}

void PeripheralServerSDL::detach_mouse(DeviceID device_id)
{
    emit_signal("device_removed", device_id);
}

void PeripheralServerSDL::send_mouse_button(DeviceID device_id, int button_mask, bool pressed)
{
}

void PeripheralServerSDL::send_mouse_motion(DeviceID device_id, Vector2 relative)
{
}

PeripheralServerSDL::PeripheralServerSDL()
{
    callable_mp(this, &PeripheralServerSDL::initialize).call_deferred();
}

PeripheralServerSDL::~PeripheralServerSDL()
{
}

DeviceID PeripheralServerSDL::get_primary_device()
{
    if (device_list.size() < 1) {
        return -1;
    }

    return device_list[0];
}

TypedArray<DeviceID> PeripheralServerSDL::get_device_list()
{
    return device_list;
}

void PeripheralServerSDL::device_register_input_callback(DeviceID device_id, Callable callback)
{
    if (!device_list.has(device_id)) {
        return;
    }

    if (!device_callbacks.has(device_id)) {
        device_callbacks[device_id] = TypedArray<Callable>();
    }

    TypedArray<Callable> device_callbacks_array = device_callbacks[device_id];

    device_callbacks_array.append(callback);
}

void PeripheralServerSDL::device_unregister_input_callback(DeviceID device_id, Callable callback)
{
    if (!device_list.has(device_id)) {
        return;
    }

    if (!device_callbacks.has(device_id)) {
        return;
    }

    TypedArray<Callable> device_callbacks_array = device_callbacks[device_id];

    device_callbacks_array.erase(callback);
}

void PeripheralServerSDL::set_mouse_captured(bool is_captured)
{
    if (sdl_window != nullptr) {
        SDL_SetWindowRelativeMouseMode(sdl_window, is_captured);
    }
}
