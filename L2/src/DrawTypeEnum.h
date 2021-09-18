#pragma once
#include "gl.h"

enum class DrawType : GLenum {
	UNDEFINED = 0,
	STATIC = GL_STATIC_DRAW,
	DYNAMIC = GL_DYNAMIC_DRAW,
	STREAM = GL_STREAM_DRAW
};

enum class Usage : GLenum {
	POINT = GL_POINTS,
	TRIANGLE = GL_TRIANGLES,
	LINE = GL_LINES,
	UNDEFINED = 2
};
