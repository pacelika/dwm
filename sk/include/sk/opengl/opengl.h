#pragma once

#define WLN_GLSL_VERSION_NAME "#version 410 core\n"

#ifndef __APPLE_OPENGL_HEADERS__
    #include "glad/glad41.h"
#endif

#ifdef __APPLE_OPENGL_HEADERS__
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/gl.h>
#endif

#define _WLN_GL_MAJOR_VERSION 4
#define _WLN_GL_MINOR_VERSION 1