#pragma once

#include "PeripheralServer.h"
#include <SDL3/SDL.h>

namespace godot{

class PeripheralServerDefault : public PeripheralServer {
	GDCLASS(PeripheralServerDefault, PeripheralServer);

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