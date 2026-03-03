#include "PeripheralServerDefault.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void PeripheralServerDefault::process_events()
{
    SDL_PumpEvents();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            printf("Key!");
        }
        printf("Event!");
    }
    
    //printf("Process events!");
}

void PeripheralServerDefault::initialize()
{
	ERR_FAIL_COND_MSG(!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO), SDL_GetError());

    SDL_CreateWindow("Test window", 320, 240, SDL_WINDOW_RESIZABLE);

    //Engine::get_main_loop()
    SceneTree* tree = (SceneTree*)Engine::get_singleton()->get_main_loop();
    tree->connect("process_frame", callable_mp(this, &PeripheralServerDefault::process_events));

    process_events();
}

PeripheralServerDefault::PeripheralServerDefault()
{
    callable_mp(this, &PeripheralServerDefault::initialize).call_deferred();
}

PeripheralServerDefault::~PeripheralServerDefault()
{
#ifndef SDL_ENABLED
	//SDL_Quit();
#endif
}

DeviceID PeripheralServerDefault::get_primary_device()
{
    return DeviceID();
}

TypedArray<DeviceID> PeripheralServerDefault::get_device_list()
{
    return TypedArray<DeviceID>();
}

void PeripheralServerDefault::device_register_input_callback(DeviceID device_id, Callable callback)
{
}

void PeripheralServerDefault::device_unregister_input_callback(DeviceID device_id, Callable callback)
{
}
