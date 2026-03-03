import os
#import warnings


def file_exists(self, path:str) -> bool:
    return os.path.exists(path)

def add_sub_build(self, folder_path:str, ignore_script_not_found=False) -> void:
    script_path = os.path.join(folder_path, "SConstruct")
    
    if ignore_script_not_found:
        if not file_exists(self, script_path):
            return

    SConscript(script_path)

def get_extension_name() -> str:
    return ""


# Use the global function to add a method to the Environment class:
AddMethod(Environment, add_sub_build)

env = SConscript("dependencies/godot-cpp/SConstruct")

Export("env")

# Add sources.
env.add_sub_build("src")