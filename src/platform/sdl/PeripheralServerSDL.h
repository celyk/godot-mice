#pragma once

#include "../../PeripheralServer.h"

#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

namespace godot{

class PeripheralServerSDL : public PeripheralServer {
	GDCLASS(PeripheralServerSDL, PeripheralServer);

    void process_events();
    void initialize();
    void initialize_sdl_window();

    void attach_mouse(DeviceID device_id);
    void detach_mouse(DeviceID device_id);
    void send_mouse_button(DeviceID device_id, int button_mask, bool pressed);
    void send_mouse_motion(DeviceID device_id, Vector2 relative);


    SDL_Window* sdl_window = nullptr;
    TypedArray<DeviceID> device_list;
    TypedDictionary<DeviceID, Variant> device_callbacks;
    
protected:
	static void _bind_methods() {};

public:

    PeripheralServerSDL();
    ~PeripheralServerSDL();

    virtual DeviceID get_primary_device() override;
    virtual TypedArray<DeviceID> get_device_list() override;

    virtual void device_register_input_callback(DeviceID device_id, Callable callback) override;
    virtual void device_unregister_input_callback(DeviceID device_id, Callable callback) override;

    virtual void set_mouse_captured(bool is_captured) override;
};

}
