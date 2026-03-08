@tool
class_name GDMiceCursor extends Node2D

@export var mouse_index := 0
@export var cursor_icon : Texture2D
@export var pixel_size := 3.0

const TouchscreenEmulation = preload("touchscreen_emulation.gd")
var touchscreen_emulation : Node

func _ready() -> void:
	touchscreen_emulation = TouchscreenEmulation.new()
	
	PeripheralServer.device_added.connect(_device_added)

func _device_added(device_id:int) -> void:
	var list := PeripheralServer.get_device_list()
	
	if list.size() <= mouse_index:
		return
	
	var desired_device_id : int = list[mouse_index]
	if device_id != desired_device_id:
		return
	
	PeripheralServer.device_register_input_callback(desired_device_id, _on_mouse_input)

func _on_mouse_input(data:Dictionary) -> void:
	var is_button := not data.has("relative")
	
	var prev_position := global_position
	
	if not is_button:
		var relative : Vector2 = data.relative
		position += relative
	else:
		pass
	
	touchscreen_emulation._set_input(mouse_index, data, prev_position, global_position)

func _process(delta: float) -> void:
	queue_redraw()

func _draw() -> void:
	if cursor_icon == null:
		return
	
	var rect_size := cursor_icon.get_size()
	rect_size *= pixel_size
	
	var rect := Rect2(-rect_size/2, rect_size)
	
	draw_texture_rect(cursor_icon, rect, false, Color.WHITE)
