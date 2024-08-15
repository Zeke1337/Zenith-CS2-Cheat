#pragma once
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 // Define before including glfw3native.h
#include <GLFW/glfw3native.h>   // Include GLFW native header
#include <iostream>


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "menu.h"
#include "datatypes.h"
#include "utilities.h"
#include "draw.h"
#include "calculations.h"

#include <vector>
#include "functions.h"
#include "protection.h"


int Start(bool status);