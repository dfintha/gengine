#if !defined(GENGINE_SYSTEM)
#define GENGINE_SYSTEM

#if defined(__APPLE__)
#include <GLUT/GLUE.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#endif
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#endif
