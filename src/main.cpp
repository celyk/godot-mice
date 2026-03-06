//#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

//#include <godot_cpp/core/version.hpp>
//#include <godot_cpp/core/class_db.hpp>
//#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "PeripheralServer.h"
#include "PeripheralServerDefault.h"


using namespace godot;

static void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

    printf("What on earth0\n");

    if (ClassDB::class_exists("PeripheralServer")){ return; }


	GDREGISTER_ABSTRACT_CLASS(PeripheralServer);
    GDREGISTER_INTERNAL_CLASS(PeripheralServerDefault);

    printf("What on earth1\n");

	PeripheralServer::singleton = memnew(PeripheralServerDefault);

    printf("What on earth2\n");

	Engine::get_singleton()->register_singleton("PeripheralServer", PeripheralServer::get_singleton());
}

static void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT gdextension_main(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(&initialize_gdextension_types);
		init_obj.register_terminator(&uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}