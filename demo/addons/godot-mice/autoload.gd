@tool
extends Node

func _enter_tree() -> void:
	if not Engine.is_editor_hint():
		Input.mouse_mode = Input.MOUSE_MODE_CAPTURED
		PeripheralServer.set_mouse_captured.call_deferred(true)

func _exit_tree() -> void:
	PeripheralServer.set_mouse_captured.call_deferred(false)

func _input(event: InputEvent) -> void:
	if event is InputEventKey and event.keycode == KEY_ESCAPE and event.is_pressed():
		if Input.mouse_mode == Input.MOUSE_MODE_CAPTURED:
			Input.mouse_mode = Input.MOUSE_MODE_VISIBLE
			PeripheralServer.set_mouse_captured.call_deferred(false)
		else:
			Input.mouse_mode = Input.MOUSE_MODE_CAPTURED
			PeripheralServer.set_mouse_captured.call_deferred(true)
