@tool
extends Node

func _ready() -> void:
	name = "TouchScreenEmulation"
	PeripheralServer.device_added.connect(_device_added)

func _device_added(device_id:int) -> void:
	var list := PeripheralServer.get_device_list()
	var device_index : int = list.find(device_id)
	
	if device_index == -1:
		return
	
	PeripheralServer.device_register_input_callback(device_id, _on_mouse_input.bind(device_index))

func _on_mouse_input(data:Dictionary, device_index:int) -> void:
	var is_button := data.has("relative")
	
	var window_id : int = DisplayServer.MAIN_WINDOW_ID
	
	if not is_button:
		touch_drag(window_id, device_index, 0, 0, 0, 0, 0.0, Vector2())
	else:
		touch_press(window_id, device_index, 0, 0, data.pressed, false)

func _normalized_pos_to_screen(p:Vector2) -> Vector2:
	p = p * Vector2(get_viewport().size)
	return p

#region Send Input

func touch_press(window_id:int, p_idx:int, p_x:int, p_y:int, p_pressed:bool, p_double_click:bool) -> void:
	var event := InputEventScreenTouch.new()
	
	event.set_window_id(window_id)
	event.set_index(p_idx)
	event.set_pressed(p_pressed)
	event.set_position(Vector2(p_x, p_y))
	event.set_double_tap(p_double_click)
	
	perform_event(event)

func touch_drag(window_id:int, p_idx:int, p_prev_x:int, p_prev_y:int, p_x:int, p_y:int, p_pressure:float, p_tilt:Vector2) -> void:
	var event := InputEventScreenDrag.new()
	
	event.set_window_id(window_id)
	event.set_index(p_idx)
	event.set_pressure(p_pressure)
	event.set_tilt(p_tilt)
	event.set_position(Vector2(p_x, p_y))
	event.set_relative(Vector2(p_x - p_prev_x, p_y - p_prev_y))
	event.set_screen_relative(event.get_relative())
	
	perform_event(event)

func touch_canceled(window_id:int, p_idx:int) -> void:
	touch_press(window_id, p_idx, -1, -1, false, false)

func _push_input(viewport:Viewport, event:InputEvent) -> void:
	viewport.push_input(event)

func perform_event(event:InputEvent) -> void:
	Input.parse_input_event(event)

#endregion
