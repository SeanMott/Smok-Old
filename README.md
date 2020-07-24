# Smok
Smok (Polish for dragon, pronounced like smoke) is a game engine for 3D and 2D with ECS. The engine is being created as a learning experience.

# Project Overview
The Smok engine is made of four parts SmokCore, SmokGUI, Smok2D, and Smok3D.

- SmokCore

SmokCore is the heart of the engine, it holds the Platform and Render API specific code. It also manages the engine, and input events. When making a new module you need to link to this lib.

- SmokGUI

SmokGUI has all the GUI based componets and systems. This is buttons, text, bars, ect. This module can be disabled by defining DISABLE_SMOK_GUI.

- Smok2D

Smok2D has all the 2D based componets and systems. This is sprite renderer, 2D physics, tile map, ect. This module can be disabled by defining DISABLE_SMOK_2D.

- Smok3D

Smok3D has all the 3D based componets and systems. This is mesh renderer, 3D physics, particals, ect. This module can be disabled by defining DISABLE_SMOK_3D.

# Libraries
- [GLM - Math](http://glm.g-truc.net/0.9.8/index.html)
- [GLFW - Input](https://www.glfw.org/)
- [Glad - Opengl](https://github.com/Dav1dde/glad)
- [ImGUI - GUI](https://github.com/ocornut/imgui)
- [stb - Image Loading](https://github.com/nothings/stb)
- [entt - ECS](https://github.com/skypjack/entt)
- [Fast Delegate - C++ Delegates](https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible)