#include "PeripheralServerDefault.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>

using namespace godot;

PeripheralServerDefault::PeripheralServerDefault()
{
    
}

PeripheralServerDefault::~PeripheralServerDefault()
{
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
