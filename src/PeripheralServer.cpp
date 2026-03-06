#include "PeripheralServer.h"

using namespace godot;

PeripheralServer *PeripheralServer::singleton = nullptr;

void PeripheralServer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_primary_device"), &PeripheralServer::get_primary_device);
	ClassDB::bind_method(D_METHOD("get_device_list"), &PeripheralServer::get_device_list);
	ClassDB::bind_method(D_METHOD("device_register_input_callback", "device", "callback"), &PeripheralServer::device_register_input_callback);
	ClassDB::bind_method(D_METHOD("device_unregister_input_callback", "device", "callback"), &PeripheralServer::device_unregister_input_callback);
}

PeripheralServer::PeripheralServer()
{
}

PeripheralServer::~PeripheralServer()
{
}
