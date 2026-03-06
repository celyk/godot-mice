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
    NSArray *connectedMice = GCMouse.mice;
    
    NSLog(@"Intialize");

    for (GCMouse *mouse in connectedMice) {
        //NSLog(mouse);
        NSLog(@"Mouse found!!!");

        device_list.append(device_list.size());

        if ([mouse isKindOfClass:[GCMouse class]]) {
            GCMouse *mouse2 = (GCMouse *)mouse;
            //subscribeMouseEvents(mouse);
        }
    }

    // [[NSNotificationCenter defaultCenter] addObserver:[GCMouseEvents class]
    //                                          selector:@selector(mouseDidConnect:)
    //                                              name:GCMouseDidConnectNotification
    //                                            object:nil];
    // [[NSNotificationCenter defaultCenter] addObserver:[GCMouseEvents class]
    //                                          selector:@selector(mouseDidDisconnect:)
    //                                              name:GCMouseDidDisconnectNotification
    //                                            object:nil];
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
    if (device_list.size() < 1) {
        return -1;
    }

    return device_list[0];
}

TypedArray<DeviceID> PeripheralServerMacOS::get_device_list()
{
    return device_list;
}

void PeripheralServerMacOS::device_register_input_callback(DeviceID device_id, Callable callback)
{
    if (!device_list.has(device_id)) {
        return;
    }

    if (!device_callbacks.has(device_id)) {
        device_callbacks[device_id] = TypedArray<Callable>();
    }

    TypedArray<Callable> device_callbacks_array = device_callbacks[device_id];

    device_callbacks_array.append(callback);
}

void PeripheralServerMacOS::device_unregister_input_callback(DeviceID device_id, Callable callback)
{
    if (!device_list.has(device_id)) {
        return;
    }

    if (!device_callbacks.has(device_id)) {
        return;
    }

    TypedArray<Callable> device_callbacks_array = device_callbacks[device_id];

    device_callbacks_array.erase(callback);
}
