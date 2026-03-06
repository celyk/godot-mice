#pragma once

#include "../../PeripheralServer.h"

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <GameController/GameController.h>
#else
#endif

namespace godot{

class PeripheralServerMacOS : public PeripheralServer {
	GDCLASS(PeripheralServerMacOS, PeripheralServer);
    //_THREAD_SAFE_CLASS_

    void process_events();
    void initialize();

    void send_mouse_event(DeviceID device_id, Vector2 relative);

    TypedArray<DeviceID> device_list;
    TypedDictionary<DeviceID, Variant> device_callbacks;
    
protected:
	static void _bind_methods() {};

public:

    PeripheralServerMacOS();
    ~PeripheralServerMacOS();

    virtual DeviceID get_primary_device() override;
    virtual TypedArray<DeviceID> get_device_list() override;

    virtual void device_register_input_callback(DeviceID device_id, Callable callback) override;
    virtual void device_unregister_input_callback(DeviceID device_id, Callable callback) override;
};

}
