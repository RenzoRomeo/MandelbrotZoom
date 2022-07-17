# MandelbrotZoom

Mandelbrot Set explorer.

All calculations are done on the GPU, using OpenGL compute shaders.

I used:
- OpenGL as the graphics API.
- GLFW for window/OpenGL context handling.
- GLAD for OpenGL bindings.

# User Input

- [W,A,S,D] -> Movement in the XY axis.
- [LMB] -> Zoom in.
- [RMB] -> Zoom out.
- [MouseScrollUp] -> Increase zoom speed.
- [MouseScrollDown] -> Decrease zoom speed.


# Screenshots

![image](https://user-images.githubusercontent.com/46039237/179419756-81c0213f-a1c6-4eea-966f-a67d36df568c.png)

![image](https://user-images.githubusercontent.com/46039237/179419887-20658716-0480-4b76-801a-1ab638f9d90d.png)

![image](https://user-images.githubusercontent.com/46039237/179419870-5dce6c0c-82e4-435b-97fb-01f1fa4bee95.png)

# TODO

- Improve precision. Currently, the deepest level of zoom is limited by floating point number precision.
- Custom color palette.
- Make the number of iterations customizable.
