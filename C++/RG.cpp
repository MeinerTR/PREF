#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

#define UI unsigned int
#define CUI const unsigned int
#define UC unsigned char
#define CUC const unsigned char

GLFWwindow *Window;
UI SCR_W, SCR_H,
    W_SCR, H_SCR;
std::string Player;

#define ERROR(MSG) {                  \
    throw std::invalid_argument(#MSG); \
}

// #include "Headers/Texture.h"
#include "Headers/Prefs.h"

#include "Headers/Init.h"

int main(void) {
    Init init;
    init.UserPrefs(); init.OpenGL();
    return 0;
}