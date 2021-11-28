/*
      __ _/| _/. _  ._/__ /
    _\/_// /_///_// / /_|/
               _/
    sof digital 2021
    written by michael rinderle <michael@sofdigital.net>
    mit license
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "include/stdafx.h"
#include "include/app.h"

/// <summary>
/// constructor & GLFW3 setup
/// </summary>
app::app()
{
    if (!glfwInit()) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(app::error_callback);


    window = glfwCreateWindow(screen_width, screen_height, app_name, NULL, NULL);
    if (window == NULL) {
        std::cout << "[*] failed to create glfw window, exiting.";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, app::framebuffer_size_callback);
    glfwSetKeyCallback(window, app::key_callback);


    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[*] failed to initalize glad, exiting.";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, screen_width, screen_height);

    glfwSwapInterval(1);
}

/// <summary>
/// main context loop for renderer
/// </summary>
void
app::main_loop()
{
    while (!glfwWindowShouldClose(window)) {
        this->render();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/// <summary>
/// renderer method for main context loop
/// </summary>
void
app::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glfwSwapBuffers(window);
    glfwPollEvents();
}

/// <summary>
/// GLFW3 error callback
/// </summary>
/// <param name="error"></param>
/// <param name="description"></param>
void
app::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error : %s\n", description);
}

/// <summary>
/// GLFW3 key callback
/// </summary>
/// <param name="window"></param>
/// <param name="key"></param>
/// <param name="scancode"></param>
/// <param name="action"></param>
/// <param name="mods"></param>
void
app::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/// <summary>
/// GLFW3 framebuffer size callback
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void
app::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}