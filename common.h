#ifndef __COMMON_H__
#define __COMMON_H__

#include <GL/glew.h>
#include <glfw3.h>

#define MUGFACES 1717	// mode 0
#define TEAPOTFACES 4357 // mode 1
#define COWFACES 9096	// mode 2
#define HANDFACES 45643	// mode 3
#define ARMADILLOFACES 155906 // mode 4
#define MAXFACES 208354
 
static char* mug =	 "<enter path here> \\mug.off";
static char* teapot= "<enter path here> \\teapot.off";
static char* cow =	 "<enter path here> \\cow.off";
static char* hand =	 "<enter path here> \\hand.off";
static char* arma =  "<enter path here> \\armadillo.off";
static char* bunny = "<enter path here> \\bunny.off";

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

#ifdef __APPLE__  
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif  // __APPLE__

GLuint initshader(const char* vertexShaderFile, const char* fragmentShaderFile);

#define FALSE 0
#define TRUE 1
#endif // __COMMON_H__
