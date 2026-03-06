@tool
extends Node3D

func _ready() -> void:
	print(PeripheralServer.get_device_list())
