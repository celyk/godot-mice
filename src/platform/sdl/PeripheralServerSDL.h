#pragma once

#include "../../PeripheralServer.h"

namespace godot{

class PeripheralServerSDL : public PeripheralServer {
	GDCLASS(PeripheralServerSDL, PeripheralServer);
    //_THREAD_SAFE_CLASS_

    void process_events();
    void initialize();

    TypedArray<DeviceID> device_list;
    TypedDictionary<DeviceID, Variant> device_callbacks;
    
public:
    void send_mouse_event(DeviceID device_id, Vector2 relative);

protected:
	static void _bind_methods() {};

public:

    PeripheralServerSDL();
    ~PeripheralServerSDL();

    virtual DeviceID get_primary_device() override;
    virtual TypedArray<DeviceID> get_device_list() override;

    virtual void device_register_input_callback(DeviceID device_id, Callable callback) override;
    virtual void device_unregister_input_callback(DeviceID device_id, Callable callback) override;
};

}
