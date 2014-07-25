#include <windows.h>
#include <windowsx.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "DrawingClass.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#define WIN32_LEAN_AND_MEAN

#define BUTTON_GL_POINT				1001
#define BUTTON_GL_LINE				1002
#define BUTTON_GL_LINE_STRIP		1003
#define BUTTON_GL_LINE_LOOP			1004
#define BUTTON_GL_TRIANGLE			1005
#define BUTTON_GL_TRIANGLE_STRIP	1006
#define BUTTON_GL_TRIANGLE_FAN		1007
#define BUTTON_GL_QUAD				1008
#define BUTTON_GL_QUAD_STRIP		1009
#define BUTTON_GL_POLYGON			1010
#define BUTTON_GL_SIN				1011


using namespace std;

float GetRand();