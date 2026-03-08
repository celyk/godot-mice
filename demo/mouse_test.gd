@tool
class_name MouseTest extends Control

@export var target_index := 0

func _ready() -> void:
	PeripheralServer.device_added.connect(_device_added)

func _process(delta: float) -> void:
	queue_redraw()

func _device_added(device_id:int) -> void:
	var list := PeripheralServer.get_device_list()
	var device_is_at_index : bool = target_index < list.size() and list[target_index] == device_id
	if device_is_at_index:
		print("_device_added ", device_id)
		_setup_callback()

func _setup_callback() -> void:
	var list = PeripheralServer.get_device_list()
	if PeripheralServer.get_device_list().size() > target_index:
		PeripheralServer.device_register_input_callback(list[target_index], _mouse_input)

func _mouse_input(data:Dictionary) -> void:
	print("Mouse ", target_index, " ", data)
	_mouse_input_deffered(data)

var is_pressed := false
func _mouse_input_deffered(data:Dictionary) -> void:
	var is_button := not data.has("relative")
	
	if not is_button:
		var relative : Vector2 = data.relative
	
		#relative = relative * relative / 100.0
	
		position += relative * Vector2(1,1)
	else:
		
		is_pressed = data.pressed
		
		
		if not is_pressed:
			scale = Vector2.ONE
		else:
			scale = Vector2.ONE * 0.7
		#print(is_pressed, "aaaa")


func _draw() -> void:
	var rect_size := Vector2(23, 26) * 8
	
	
	var rect := Rect2(-rect_size/2, rect_size)
	
	var color : Color = [Color.WHITE, Color.RED, Color.BLUE, Color.GREEN, Color.YELLOW][target_index + 1]
	
	
	color = color.lightened(0.7)
	
	draw_texture_rect(preload("res://cursor_hand.png"), rect, false, color)
	
	var char_size := 100
	draw_char(get_theme_default_font(), char_size * Vector2(-0.21, 0.88), str(target_index+1), char_size, Color.BLACK)
	
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
