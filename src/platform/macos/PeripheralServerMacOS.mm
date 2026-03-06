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

void PeripheralServerMacOS::mouseMovedTest(MouseID id, float x, float y)
{
    //UtilityFunctions::print("mouseMovedTest ", x, y);

    ((PeripheralServerMacOS*)PeripheralServer::get_singleton())->send_mouse_event(id, Vector2(x, y));
}

void PeripheralServerMacOS::send_mouse_event(DeviceID device_id, Vector2 relative)
{
    //UtilityFunctions::print("send_mouse_event ", relative);

    if (!device_list.has(device_id)) {
        return;
    }

    if (!device_callbacks.has(device_id)) {
        return;
    }

    Dictionary data;
    data["relative"] = relative;

    TypedArray<Callable> callbacks = device_callbacks[device_id];

    //for (Callable callback in device_callbacks[device_id]) {
    for (int i = 0; i < callbacks.size(); i++) {
        Callable callback = callbacks[i];

        callback.call(data);
    }

    //Callable callback = device_callbacks[device_id];
}

void PeripheralServerMacOS::initialize()
{
    setupMouse();

    NSArray *connectedMice = GCMouse.mice;
    
    UtilityFunctions::print("Intialize ", fooCPP());

    

    for (GCMouse *mouse in connectedMice) {
        //NSLog(mouse);
        UtilityFunctions::print("Mouse found!!!");

        device_list.append(device_list.size());

        if ([mouse isKindOfClass:[GCMouse class]]) {
            GCMouse *mouse2 = (GCMouse *)mouse;
            //subscribeMouseEvents(mouse);
        }
        
        
    }

    mouseMoved = &PeripheralServerMacOS::mouseMovedTest;

    // mouseMoved = [this](MouseID id, float x, float y) {
    //     //GCMouse* gc_mouse = (GCMouse*)mouse;

        
    //     //gc_mouse;

    //    //this->send_mouse_event(id, Vector2(x, y));
    // };

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
