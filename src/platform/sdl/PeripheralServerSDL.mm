#include "PeripheralServerSDL.h"

#include <godot_cpp/core/class_db.hpp>
// #include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/display_server.hpp>
// #include <godot_cpp/classes/thread.hpp>

#include <SDL3/SDL.h>

using namespace godot;


void* PeripheralServerSDL::setup_sdl_window()
{
    SDL_PropertiesID properties = SDL_CreateProperties();
    
    bool use_view = true;

    if (use_view) {
        int64_t view_handle = DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::WINDOW_VIEW, 0);
        SDL_Log("view_handle: %lld", view_handle);

        
        SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_VIEW_POINTER, (void*)view_handle);
    }
    else {
        int64_t window_handle = DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::WINDOW_HANDLE, 0);
        SDL_Log("window_handle: %lld", window_handle);
        
        SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, (void*)window_handle);
    }

    SDL_Window* sdl_window_handle = SDL_CreateWindowWithProperties(properties);

    if (!sdl_window_handle)
    {
        UtilityFunctions::print("invalid handle");
        return nullptr;
    }

    SDL_SetWindowRelativeMouseMode(sdl_window_handle, true);

    return (void*)sdl_window_handle;
}

void PeripheralServerSDL::process_events()
{
    //SDL_PumpEvents(); // Force SDL to grab what's left in the queue

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            SDL_Log("SDL_EVENT_KEY_DOWN: %d\n", event.key.key);
        }
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            SDL_Log("SDL_EVENT_MOUSE_MOTION %d: %f %f", event.motion.which, event.motion.x, event.motion.y);
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            SDL_Log("SDL_EVENT_MOUSE_BUTTON_DOWN %d: %f %f", event.button.which, event.button.x, event.button.y);
        }
    }
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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    printf("Driver: %s\n", SDL_GetCurrentVideoDriver());

    SDL_Window* sdl_window_handle = (SDL_Window*)setup_sdl_window();

    UtilityFunctions::print("Potential error3: ", SDL_GetError());

    SceneTree* tree = (SceneTree*)Engine::get_singleton()->get_main_loop();
    tree->connect("process_frame", callable_mp(this, &PeripheralServerSDL::process_events));

    process_events();
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
