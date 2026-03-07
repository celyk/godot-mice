@tool
class_name MouseTest extends Control

@export var target_id := 0

func _ready() -> void:
	#_setup()
	pass

var known_device := false
func _process(delta: float) -> void:
	#return
	if known_device:
		pass
	elif PeripheralServer.get_device_list().has(target_id):
		_setup()
		known_device = true
	
	queue_redraw()

func _setup() -> void:
	_setup_callback()

func _setup_callback() -> void:
	PeripheralServer.device_register_input_callback(target_id, _mouse_input.bind(target_id))



func _mouse_input(data:Dictionary, target_id:int) -> void:
	print("Mouse ", target_id, " ", data)
	_mouse_input_deffered.call_deferred(data, target_id)

func _mouse_input_deffered(data:Dictionary, target_id:int) -> void:
	var relative : Vector2 = data.relative
	
	#relative = relative * relative / 100.0
	
	position += relative * Vector2(1,1)


func _draw() -> void:
	#draw_circle(Vector2(), 40.0, Color.WHITE)
	#draw_texture(preload("res://cursor_hand.png"), Vector2(), Color.WHITE)
	var rect_size := Vector2(23, 26) * 8
	var rect := Rect2(-rect_size/2, rect_size)
	
	var color := Color.WHITE
	
	match target_id:
		0:
			color = Color.RED
		1:
			color = Color.BLUE
	
	color = color.lightened(0.7)
	
	
	draw_texture_rect(preload("res://cursor_hand.png"), rect, false, color)
