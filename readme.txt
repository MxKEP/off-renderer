Files needed to compile: main.c, initshader.c, mat.c, mat.h, common.h, fragShader.glsl, vshader.glsl

Prior to compilation the paths to the files need to be changed in common.h (lines 14-19) for the .off
files, and in main.c lines (74-75) for the shaders.
After running the program, the user will be prompted by a menu to choose a mesh to load (no
command line arguments). Numbers 1-6 will load the corresponding .off file.

Controls: E : edge mode
F: face mode
V: vertex mode
Left/Right : Rotates the object

Libraries needed: GL/GLEW.h
				  glfw3.h