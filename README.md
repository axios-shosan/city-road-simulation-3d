# Introduction
The provided code is a graphical application using OpenGL and GLFW to display a 3D scene containing various objects such as a road, cars, walls, trees, etc. The main goal is to simulate a 3D road environment.

# Code Structure
## Library Inclusions
The code begins by including several libraries, including iostream, glad, GLFW, GLM libraries for 3D-related mathematics, utilities for shaders, model and texture handling, and the stb_image library for image loading.
## Declaration of Global Variables
The code declares several global variables, including identifiers for textures, objects, matrices for 3D transformations, and an instance of the Camera class.
## Callback and Initialization Functions
There are defined functions to handle window resizing (framebuffer_size_callback) and key management (keyCallback).
## Initialization and Loading Functions
The code includes functions to initialize textures (InitTexture), load textures (LoadTextures), bind objects from OBJ files (bindObj), and draw objects (drawObj). There is also a function to move the car (driveCar).
## Main Function (main)
The main function starts by initializing GLFW, loading OpenGL, creating a window, and loading shaders. Then, it creates several objects representing scene elements (road, cars, walls, trees) and sets their positions, sizes, and rotations.
The main rendering loop (while(!glfwWindowShouldClose(window))) handles events, calculates elapsed time, updates the camera, and draws objects.
Finally, the code deallocates allocated memory and closes GLFW.
## Shaders
The shader is used for rendering based on ambient, diffuse, and specular lighting.
Placing the Car on the Light

# Notes
Code Organization: The code could benefit from better organization, especially by grouping related functionalities into classes or distinct functions (drawObject, Camera…).
Encapsulation: The Object class could benefit from stricter encapsulation to better adhere to object-oriented principles.


## demo

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2007-28-29.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2007-29-06.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2007-40-47.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2007-41-06.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2010-34-07.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2010-34-36.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2010-35-00.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2010-35-50.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2010-35-59.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2011-22-10.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2011-22-34.png)

![Demo](https://github.com/axios-shosan/city-road-simulation-3d/blob/master/demo/Screenshot%20from%202024-01-29%2011-22-43.png)
