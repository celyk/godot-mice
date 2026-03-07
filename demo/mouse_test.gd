@tool
class_name MouseTest extends Control

@export var target_index := 0

func _ready() -> void:
	#_setup()
	pass

var known_device := false
func _process(delta: float) -> void:
	#return
	
	#print(PeripheralServer.get_device_list())
	
	if known_device:
		pass
	elif PeripheralServer.get_device_list().size() > target_index:
		_setup()
		known_device = true
	
	queue_redraw()

func _setup() -> void:
	_setup_callback()

func _setup_callback() -> void:
	var list = PeripheralServer.get_device_list()
	print(list)
	if list.size() > target_index:
		PeripheralServer.device_register_input_callback(list[target_index], _mouse_input.bind(target_index))



func _mouse_input(data:Dictionary, target_id:int) -> void:
	print("Mouse ", target_id, " ", data)
	_mouse_input_deffered.call_deferred(data, target_id)

var is_pressed := false
func _mouse_input_deffered(data:Dictionary, target_id:int) -> void:
	if data.has("relative"):
		var relative : Vector2 = data.relative
	
		#relative = relative * relative / 100.0
	
		position += relative * Vector2(1,1)
	else:
		
		is_pressed = data.pressed
		pass


func _draw() -> void:
	#draw_circle(Vector2(), 40.0, Color.WHITE)
	#draw_texture(preload("res://cursor_hand.png"), Vector2(), Color.WHITE)
	var rect_size := Vector2(23, 26) * 8
	
	if is_pressed:
		rect_size *= 0.7
	
	
	var rect := Rect2(-rect_size/2, rect_size)
	
	var color := Color.WHITE
	
	match target_index:
		0:
			color = Color.RED
		1:
			color = Color.BLUE
	
	color = color.lightened(0.7)
	
	draw_texture_rect(preload("res://cursor_hand.png"), rect, false, color)
	
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
