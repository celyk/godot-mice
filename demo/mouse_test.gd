@tool
class_name MouseTest extends Control

@export var target_id := 0

func _ready() -> void:
	_setup()

func _setup() -> void:
	_setup_callback()

func _setup_callback() -> void:
	PeripheralServer.device_register_input_callback(target_id, _mouse_input.bind(target_id))



func _mouse_input(data:Dictionary, target_id:int) -> void:
	#print("Mouse ", target_id, " ", data)
	_mouse_input_deffered.call_deferred(data, target_id)

func _mouse_input_deffered(data:Dictionary, target_id:int) -> void:
	var relative : Vector2 = data.relative
	
	position += relative * Vector2(1,-1)


func _process(delta: float) -> void:
	queue_redraw()

func _draw() -> void:
	draw_circle(Vector2(), 40.0, Color.WHITE)
