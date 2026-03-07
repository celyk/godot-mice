#include "PeripheralServerSDL.h"

#include <godot_cpp/core/class_db.hpp>
// #include <godot_cpp/core/math.hpp>
// #include <godot_cpp/classes/engine.hpp>
// #include <godot_cpp/classes/scene_tree.hpp>
// #include <godot_cpp/classes/display_server.hpp>
// #include <godot_cpp/classes/thread.hpp>

#include <SDL3/SDL.h>

using namespace godot;

void PeripheralServerSDL::process_events()
{
}

void PeripheralServerSDL::send_mouse_event(DeviceID device_id, Vector2 relative)
{
    //UtilityFunctions::print("send_mouse_event ", relative);

    if (!device_list.has(device_id)) {
        return;
    }

    if (!device_callbacks.has(device_id)) {
        return;
    }

    Dictionary data;
    data["relative"] = relative;

    TypedArray<Callable> callbacks = device_callbacks[device_id];

    //for (Callable callback in device_callbacks[device_id]) {
    for (int i = 0; i < callbacks.size(); i++) {
        Callable callback = callbacks[i];

        callback.call(data);
    }

    //Callable callback = device_callbacks[device_id];
}

void PeripheralServerSDL::initialize()
{
    SDL_Init(SDL_INIT_VIDEO);

    //void* window_handle = (__bridge void*) mainWindow;
    void* window_handle;

    SDL_PropertiesID properties = SDL_CreateProperties();
    
    SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, window_handle);

    SDL_Window* sdl_window_handle = SDL_CreateWindowWithProperties(properties);

    printf("Driver: %s\n", SDL_GetCurrentVideoDriver());
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
