WIP! More information coming soon. For now, enjoy this video.

https://github.com/user-attachments/assets/24062dc8-5da7-4b17-bb3e-90c43f13577f

# Build

The GDExtension is being developed on macOS. Other platforms need testing.

To build place the SDL library under `./dependencies/SDL3/` and run scons:

```
scons
```

# macOS problems

Currently, SDL3 does not support multiple mice and keyboards on macOS, only iOS. You need to build SDL from [this PR](https://github.com/libsdl-org/SDL/pull/14741).

# See also

Another GDExtension I made to enhance mouse support on macOS:

https://github.com/celyk/godot-trackpad
