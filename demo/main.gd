@tool
extends Node3D

func _ready() -> void:
	_initialize.call_deferred()

func _initialize() -> void:
	print(PeripheralServer.get_device_list())
