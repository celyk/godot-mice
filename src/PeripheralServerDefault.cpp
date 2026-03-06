#include "PeripheralServerDefault.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/thread.hpp>


using namespace godot;

void PeripheralServerDefault::process_events_internal() {
}

void PeripheralServerDefault::process_events()
{
    
}

void PeripheralServerDefault::initialize()
{
}

PeripheralServerDefault::PeripheralServerDefault()
{
    callable_mp(this, &PeripheralServerDefault::initialize).call_deferred();
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