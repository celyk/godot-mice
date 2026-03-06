@tool
extends Node3D

func _ready() -> void:
	_initialize.call_deferred()

func _initialize() -> void:
	print(PeripheralServer.get_device_list())
	
	PeripheralServer.device_register_input_callback(0, _mouse_input)

func _mouse_input(data:Dictionary) -> void:
	print(data)
