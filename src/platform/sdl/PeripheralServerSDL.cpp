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
                send_mouse_motion(event.motion.which, Vector2(event.motion.xrel, event.motion.yrel));
                
                break;
            
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                send_mouse_button(event.button.which, event.button.button, true);

                break;
            
            case SDL_EVENT_MOUSE_BUTTON_UP:
                send_mouse_button(event.button.which, event.button.button, false);

                break;
            
            case SDL_EVENT_MOUSE_ADDED:
                UtilityFunctions::print("SDL_EVENT_MOUSE_ADDED ", event.mdevice.which);
                attach_mouse(event.mdevice.which);

                break;
            
            case SDL_EVENT_MOUSE_REMOVED:
                UtilityFunctions::print("SDL_EVENT_MOUSE_REMOVED");
                detach_mouse(event.mdevice.which);

                break;
            
            case SDL_EVENT_KEY_DOWN:
                // TODO
                break;
            
            case SDL_EVENT_KEYBOARD_ADDED:

                break;
            
            case SDL_EVENT_KEYBOARD_REMOVED:

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
    
    sdl_window = SDL_CreateWindowWithProperties(properties);
    
    if (!sdl_window)
    {
        printf("invalid handle");
        return;
    }
}

void PeripheralServerSDL::attach_mouse(DeviceID device_id)
{

#if defined(MACOS_ENABLED)
    // Ignore the SDL_DEFAULT_MOUSE_ID
    if (device_id == 1) {
        return;
    }
#endif

    if (has_device(device_id)) {
        // error
        return;
    }

    add_device(device_id);

    emit_signal("device_added", device_id);
}

void PeripheralServerSDL::detach_mouse(DeviceID device_id)
{
    if (!has_device(device_id)) {
        // error
        return;
    }

    remove_device(device_id);

    emit_signal("device_removed", device_id);
}

void PeripheralServerSDL::send_mouse_button(DeviceID device_id, int button_mask, bool pressed)
{
    //UtilityFunctions::print("send_mouse_button ", pressed);
    
    Dictionary data;
    data["device_id"] = device_id;
    data["button"] = button_mask;
    data["pressed"] = pressed;

    TypedArray<Callable> callbacks = device_callbacks[device_id];

    for (int i = 0; i < callbacks.size(); i++) {
        Callable callback = callbacks[i];
        callback.call(data);
    }
}

void PeripheralServerSDL::send_mouse_motion(DeviceID device_id, Vector2 relative)
{
    Dictionary data;
    data["device_id"] = device_id;
    data["relative"] = relative;

    //UtilityFunctions::print("send_mouse_motion", data);
    
    TypedArray<Callable> callbacks = device_callbacks[device_id];

    for (int i = 0; i < callbacks.size(); i++) {
        Callable callback = callbacks[i];
        callback.call(data);
    }
}

void godot::PeripheralServerSDL::add_device(DeviceID device_id)
{
    int device_index = device_list.size();
    //UtilityFunctions::print("add_device ", device_index);

    device_list.append(device_id);
    device_id_to_index[device_id] = device_index;
}

void godot::PeripheralServerSDL::remove_device(DeviceID device_id)
{
    int device_index = get_device_index(device_id);
    device_list.remove_at(device_index);
    device_id_to_index.erase(device_id);
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
        //add_device(device_id);
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
        // hmm
    }

    if (!device_callbacks.has(device_id)) {
        return;
    }

    TypedArray<Callable> device_callbacks_array = device_callbacks[device_id];
    device_callbacks_array.erase(callback);

    if (device_callbacks_array.is_empty()) {
        //device_callbacks.erase(device_callbacks_array);
    }
}

void PeripheralServerSDL::set_mouse_captured(bool is_captured)
{
    if (sdl_window != nullptr) {
        SDL_SetWindowRelativeMouseMode(sdl_window, is_captured);
    }
}
