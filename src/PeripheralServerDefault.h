#pragma once

#include "PeripheralServer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>


namespace godot{

class PeripheralServerDefault : public PeripheralServer {
	GDCLASS(PeripheralServerDefault, PeripheralServer);
    //_THREAD_SAFE_CLASS_

    void process_events_internal();
    void process_events();
    //bool handle_event(void* userdata, SDL_Event* event);
    void initialize();

    //static bool SDLCALL handle_event(void* userdata, SDL_Event* event);

protected:
	static void _bind_methods() {};

public:

    PeripheralServerDefault();
    ~PeripheralServerDefault();

    virtual DeviceID get_primary_device() override;
    virtual TypedArray<DeviceID> get_device_list() override;

    virtual void device_register_input_callback(DeviceID device_id, Callable callback) override;
    virtual void device_unregister_input_callback(DeviceID device_id, Callable callback) override;
};

}
