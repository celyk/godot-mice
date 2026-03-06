#include "PeripheralServerMacOS.h"

#include <godot_cpp/core/class_db.hpp>
// #include <godot_cpp/core/math.hpp>
// #include <godot_cpp/classes/engine.hpp>
// #include <godot_cpp/classes/scene_tree.hpp>
// #include <godot_cpp/classes/display_server.hpp>
// #include <godot_cpp/classes/thread.hpp>

using namespace godot;

void PeripheralServerMacOS::process_events()
{
}

void PeripheralServerMacOS::initialize()
{
}

PeripheralServerMacOS::PeripheralServerMacOS()
{
    callable_mp(this, &PeripheralServerMacOS::initialize).call_deferred();
}

PeripheralServerMacOS::~PeripheralServerMacOS()
{
}

DeviceID PeripheralServerMacOS::get_primary_device()
{
    return DeviceID();
}

TypedArray<DeviceID> PeripheralServerMacOS::get_device_list()
{
    return TypedArray<DeviceID>();
}

void PeripheralServerMacOS::device_register_input_callback(DeviceID device_id, Callable callback)
{
}

void PeripheralServerMacOS::device_unregister_input_callback(DeviceID device_id, Callable callback)
{
}
