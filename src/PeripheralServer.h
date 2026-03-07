#pragma once

#include <godot_cpp/core/class_db.hpp>

namespace godot{

typedef int DeviceID;

class PeripheralServer : public Object {
	GDCLASS(PeripheralServer, Object);

protected:
	static void _bind_methods();

public:
    PeripheralServer();
    virtual ~PeripheralServer();

    static PeripheralServer* singleton;
    static PeripheralServer* get_singleton() { return singleton; }

    virtual DeviceID get_primary_device() { return -1; }
    virtual TypedArray<DeviceID> get_device_list() { return TypedArray<DeviceID>(); }

    virtual void device_register_input_callback(DeviceID device_id, Callable callback) { }
    virtual void device_unregister_input_callback(DeviceID device_id, Callable callback) { }

    virtual void set_mouse_captured(bool is_captured) { }
};

}