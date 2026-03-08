#@tool
extends Node3D

func _ready() -> void:
	_initialize.call_deferred()

func _initialize() -> void:
	for id in range(0,4):
		_create_mouse_test(id)
	
	#DisplayServer.mouse_set_mode(DisplayServer.MOUSE_MODE_VISIBLE)
	#
	#print(PeripheralServer.get_device_list())
	#
	#for id in PeripheralServer.get_device_list():
		#PeripheralServer.device_register_input_callback(id, _mouse_input.bind(id))

var known_devices : Dictionary

func _create_mouse_test(id:int):
	print("Added mouse ", id)
	var mouse0 := MouseTest.new()
	mouse0.target_index = id
	mouse0.position = get_tree().root.size / 2.0
	mouse0.position.x += id * 100
	get_tree().root.add_child(mouse0)

func _process(delta: float) -> void:
	
	#print(PeripheralServer.get_device_list())
	
	#for id in PeripheralServer.get_device_list():
		#if known_devices.has(id):
			#pass
		#else:
			#_create_mouse_test(id)
	pass

func _mouse_input(data:Dictionary, id:int) -> void:
	print("Mouse ", id, " ", data)
