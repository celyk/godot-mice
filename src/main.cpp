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

#include "platform/sdl/PeripheralServerSDL.h"

// Platform dependent headers
#if defined(MACOS_ENABLED)
#include "platform/macos/PeripheralServerMacOS.h"
#endif

#if defined(LINUX_ENABLED)
#endif

#if defined(WINDOWS_ENABLED)
#endif

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

	//PeripheralServer::singleton = memnew(PeripheralServerDefault);

#if defined(SDL_FALLBACK)
    GDREGISTER_INTERNAL_CLASS(PeripheralServerSDL);
	PeripheralServer::singleton = memnew(PeripheralServerSDL);
#else /*!SDL_FALLBACK*/

#if defined(MACOS_ENABLED)
    GDREGISTER_INTERNAL_CLASS(PeripheralServerMacOS);
	PeripheralServer::singleton = memnew(PeripheralServerMacOS);
#endif

#if defined(LINUX_ENABLED)
    GDREGISTER_INTERNAL_CLASS(PeripheralServerLinux);
	PeripheralServer::singleton = memnew(PeripheralServerLinux);
#endif

#if defined(WINDOWS_ENABLED)
    GDREGISTER_INTERNAL_CLASS(PeripheralServerWindows);
	PeripheralServer::singleton = memnew(PeripheralServerWindows);
#endif

#endif /*!SDL_FALLBACK*/

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