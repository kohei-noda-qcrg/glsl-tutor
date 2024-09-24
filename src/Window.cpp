#include "GL/glew.h"

#include "Window.hpp"
#include "macros/assert.hpp"

Window::Window(int width, int height, const char* title)
    : window(glfwCreateWindow(width, height, title, NULL, NULL)) {
    if(window == NULL) {
        warn("failed to create GLFW window");
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        warn("failed to initialize GLEW");
        exit(1);
    }

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, resize);
    resize(window, width, height);
}

auto Window::swapBuffers() const -> void {
    glfwSwapBuffers(window);
}

auto Window::resize(GLFWwindow* window, int width, int height) -> void {
    int fbwidth, fbheight;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);
    glViewport(0, 0, fbwidth, fbheight);

    auto* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(instance != NULL) {
        instance->aspect = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
    }
}

auto Window::getAspect() const -> GLfloat {
    return aspect;
}