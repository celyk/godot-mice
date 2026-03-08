@tool
extends EditorPlugin

var settings = preload("settings.gd").new()

func _enter_tree() -> void:
	add_autoload_singleton("GodotMiceAddon", "autoload.gd")

func _exit_tree() -> void:
	remove_autoload_singleton("GodotMiceAddon")
