#include "Window.h"

int main()
{
    Window window(std::string("Learning OpenGL"), 800, 600);
    if (window.init() != 0)
        return -1;
    window.run();
    return 0;
}