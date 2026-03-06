#pragma once

#include "../../PeripheralServer.h"

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <GameController/GameController.h>
#else
#endif

#include "GCMouseManager.h"

namespace godot{

class PeripheralServerMacOS : public PeripheralServer, public GCMouseManager {
	GDCLASS(PeripheralServerMacOS, PeripheralServer);
    //_THREAD_SAFE_CLASS_

    void process_events();
    void initialize();

    static void mouseMovedTest(MouseID id, float x, float y);

    TypedArray<DeviceID> device_list;
    TypedDictionary<DeviceID, Variant> device_callbacks;
    
public:
    void send_mouse_event(DeviceID device_id, Vector2 relative);

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
