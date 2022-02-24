#pragma once

#include <iostream>

#include "glad/glad.h"

void GLClearError();
bool GLLogError(const char *file, int line, const char *func);


#ifdef V_DEBUG
	#define GLcall(expr) { GLClearError(); expr; if(GLLogError(__FILE__, __LINE__, #expr)) { __debugbreak(); } }
#else
	#define GLcall(expr) expr
#endif


struct GLName { GLuint _id; };