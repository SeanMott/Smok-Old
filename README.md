# Smok
Smok (Polish for dragon, pronounced like smoke) is a game engine for 3D and 2D with ECS. The engine is being created as a learning experience.

# Project Overview
The Smok engine is made of three parts SmokCore, Smok2D, and Smok3D.

SmokCore handles the core of the engine, it handles the RenderLayer and the origin of Window, Input, and ECS events.
Smok2D and Smok3D handles their respective dimentions, they hold the Systems and Components needed for that type of application. They can be disabled with SMOK_DISABLE_3D or SMOK_DISABLE_2D. In the case of basic GUI it is stored in core, but 3D text would be stored in Smok3D.

# Libraries
- [GLM - Math](http://glm.g-truc.net/0.9.8/index.html)
- [GLFW - Input](https://www.glfw.org/)
- [Glad - Opengl](https://github.com/Dav1dde/glad)
- [ImGUI - GUI](https://github.com/ocornut/imgui)
- [stb - Image Loading](https://github.com/nothings/stb)
- [entt - ECS](https://github.com/skypjack/entt)
- [Fast Delegate - C++ Delegates](https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible)
