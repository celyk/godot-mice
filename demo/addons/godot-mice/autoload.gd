@tool
extends Node

func _enter_tree() -> void:
	if not Engine.is_editor_hint():
		PeripheralServer.set_mouse_captured.call_deferred(true)

func _exit_tree() -> void:
	pass
