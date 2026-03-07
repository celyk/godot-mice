#include "PeripheralServer.h"

//#include <godot_cpp/core/version.hpp>
#include <godot_cpp/core/class_db.hpp>
//#include <godot_cpp/core/mutex_lock.hpp>
//#include <godot_cpp/classes/ref.hpp>
//#include <godot_cpp/variant/array.hpp>
//#include <godot_cpp/variant/typed_dictionary.hpp>
//#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

PeripheralServer *PeripheralServer::singleton = nullptr;

void PeripheralServer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_primary_device"), &PeripheralServer::get_primary_device);
	ClassDB::bind_method(D_METHOD("get_device_list"), &PeripheralServer::get_device_list);
	ClassDB::bind_method(D_METHOD("device_register_input_callback", "device", "callback"), &PeripheralServer::device_register_input_callback);
	ClassDB::bind_method(D_METHOD("device_unregister_input_callback", "device", "callback"), &PeripheralServer::device_unregister_input_callback);
	ClassDB::bind_method(D_METHOD("capture_mouse", "device", "callback"), &PeripheralServer::device_register_input_callback);
	ClassDB::bind_method(D_METHOD("set_mouse_captured", "is_captured"), &PeripheralServer::set_mouse_captured);

	ADD_SIGNAL(MethodInfo("device_added", PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("device_removed", PropertyInfo(Variant::INT, "id")));
}

PeripheralServer::PeripheralServer()
{
}

PeripheralServer::~PeripheralServer()
{
}
