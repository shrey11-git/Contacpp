#include <GLFW/glfw3.h>
#include "db.h"
#include "gui.h"
#include <iostream>

void runAppGUI() {
    if (!initDatabase()) {
        std::cerr << "Failed to initialize database.\n";
        return;
    }

    if (!glfwInit()) {
        std::cerr << "GLFW init failed.\n";
        return;
    }

    // create 800x600 size window with title 'Contac++'
    GLFWwindow* window = glfwCreateWindow(800, 600, "Contacpp", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // temporary console menu for testing
        printBanner();
        showMenu();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
