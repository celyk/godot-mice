#include "PeripheralServerDefault.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/thread.hpp>


using namespace godot;

static void process_events_static(PeripheralServerDefault* context) {
ERR_FAIL_COND(!Thread::is_main_thread());
    ERR_FAIL_COND(!SDL_IsMainThread());
    
    return;

    //SDL_PumpEvents();
    //return;

    //_THREAD_SAFE_LOCK_

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            SDL_Log("Key process_events!");
        }
		if (event.type == SDL_EVENT_MOUSE_MOTION) {
            SDL_Log("Mouse process_events!");
        }
        //SDL_Log("Event!");
    }

    //_THREAD_SAFE_UNLOCK_

    //printf("Process events!");
}

void PeripheralServerDefault::process_events_internal() {
    //initialize();
    
    //callable_mp(this, &PeripheralServerDefault::process_events).call_deferred();
    SDL_RunOnMainThread((SDL_MainThreadCallback)process_events_static, (void*)this, false);
}

void PeripheralServerDefault::process_events()
{
    
}


static bool SDLCALL handle_event(void* userdata, SDL_Event* event) {
    return false;

    if (SDL_IsMainThread()){
        if (event->type == SDL_EVENT_KEY_DOWN) {
            UtilityFunctions::print("Key!");
        }
        UtilityFunctions::print("Event!");
    }
    else{
        UtilityFunctions::print("Not main thread!");
    }

    return false;
}

void PeripheralServerDefault::initialize()
{
    UtilityFunctions::print("Potential error0: ", SDL_GetError());
    
    SDL_Quit();
	ERR_FAIL_COND_MSG(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS), SDL_GetError());
    SDL_SetHint(SDL_HINT_EVENT_LOGGING, "2");

    UtilityFunctions::print("Potential error1: ", SDL_GetError());

    bool use_view = true;

    SDL_PropertiesID properties = SDL_CreateProperties();
    
    if (use_view) {
        int64_t view_handle = DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::WINDOW_VIEW, 0);
        SDL_Log("view_handle: %lld", view_handle);

        
        SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_VIEW_POINTER, (void*)view_handle);
    }
    else {
        int64_t window_handle = DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::WINDOW_HANDLE, 0);
        SDL_Log("window_handle: %lld", window_handle);
        
        SDL_SetPointerProperty(properties, SDL_PROP_WINDOW_CREATE_COCOA_WINDOW_POINTER, (void*)window_handle);
    }
    /*
    // Title
    SDL_SetStringProperty(
        properties,
        SDL_PROP_WINDOW_CREATE_TITLE_STRING,
        "Hello Window"
    );
    
    SDL_SetBooleanProperty(
        properties,
        SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,
        true
    );
    SDL_SetBooleanProperty(properties, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, false);
    SDL_SetBooleanProperty(properties, SDL_PROP_WINDOW_CREATE_MOUSE_GRABBED_BOOLEAN, true);

    SDL_SetNumberProperty(properties, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 640);
    SDL_SetNumberProperty(properties, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 480);
    */

    UtilityFunctions::print("Potential error2: ", SDL_GetError());

    //SDL_CreateWindow("Test window", 320, 240, SDL_WINDOW_RESIZABLE);
    SDL_Window* sdl_window_handle = SDL_CreateWindowWithProperties(properties);

    if (!sdl_window_handle)
    {
        UtilityFunctions::print("invalid handle");
        return;
    }

    UtilityFunctions::print("Potential error3: ", SDL_GetError());

    //m_windowId = SDL_GetWindowID(m_handle);
    //SetEventListener(true);

    //SDL_AddEventWatch(handle_event, this);

    //Engine::get_main_loop()
    SceneTree* tree = (SceneTree*)Engine::get_singleton()->get_main_loop();
    tree->connect("process_frame", callable_mp(this, &PeripheralServerDefault::process_events_internal));

    process_events();

    /*
    CFRunLoopObserver pre_wait_observer = CFRunLoopObserverCreateWithHandler(kCFAllocatorDefault, kCFRunLoopBeforeWaiting, true, 0, ^(CFRunLoopObserverRef observer, CFRunLoopActivity activity) {
					@autoreleasepool {
						@try {
							GodotProfileFrameMark;
							GodotProfileZone("macOS main loop godot-mice");

                            process_events();

						} @catch (NSException *exception) {
							ERR_PRINT("NSException: " + String::utf8([exception reason].UTF8String));
						}
					}
					if (wait_timer == nil) {
						CFRunLoopWakeUp(CFRunLoopGetCurrent()); // Prevent main loop from sleeping.
					}
				});
            
	CFRunLoopAddObserver(CFRunLoopGetCurrent(), pre_wait_observer, kCFRunLoopCommonModes);
    */
}

PeripheralServerDefault::PeripheralServerDefault()
{
    UtilityFunctions::print("PeripheralServerDefault\n");
    callable_mp(this, &PeripheralServerDefault::initialize).call_deferred();
}

PeripheralServerDefault::~PeripheralServerDefault()
{
#ifndef SDL_ENABLED
	//SDL_Quit();
#endif
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
