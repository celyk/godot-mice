@tool
extends Node3D

func _ready() -> void:
	_initialize.call_deferred()

func _initialize() -> void:
	for id in PeripheralServer.get_device_list():
		var mouse0 := MouseTest.new()
		mouse0.target_id = id
		mouse0.position.x += id * 100
		get_tree().root.add_child(mouse0)
	
	return
	
	print(PeripheralServer.get_device_list())
	
	for id in PeripheralServer.get_device_list():
		PeripheralServer.device_register_input_callback(id, _mouse_input.bind(id))


func _mouse_input(data:Dictionary, id:int) -> void:
	print("Mouse ", id, " ", data)
