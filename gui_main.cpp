#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "db.h"
#include <vector>
#include <string>
#include <algorithm>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>
#else
#include <GL/gl.h>
#endif

int main() {
    if (!initDatabase()) {
        std::cerr << "Failed to initialize database.\n";
        return -1;
    }

    if (!glfwInit()) {
        std::cerr << "GLFW init failed.\n";
        return -1;
    }

    // set OpenGL 3.3 crore profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 700, "Contacpp - GUI", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

#if defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!\n";
        return -1;
    }
#endif

    // initialize imgui with dark theme
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    char nameBuf[128] = "";
    char phoneBuf[20] = "";
    char searchBuf[128] = "";
    std::vector<std::pair<std::string, long long>> searchResults;

    int sortMode = 0; // 0: NA, 1: name asc, 2: name desc, 3: phone asc, 4: phone desc
    const char* sortOptions[] = {
        "None", "Name (A-Z)", "Name (Z-A)", "Phone (Low-High)", "Phone (High-Low)"
    };

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(200, 50), ImGuiCond_FirstUseEver);


        // responsive window sizing
        int window_w, window_h;
        glfwGetWindowSize(window, &window_w, &window_h);
        ImGui::SetNextWindowSize(ImVec2(window_w * 0.9f, window_h * 0.9f), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(window_w * 0.05f, window_h * 0.05f), ImGuiCond_Always);
        ImGui::Begin("Contacpp - Contact Manager");


        ImGui::Text("Add Contact:");
        ImGui::InputText("Name", nameBuf, IM_ARRAYSIZE(nameBuf));
        ImGui::InputText("Phone", phoneBuf, IM_ARRAYSIZE(phoneBuf));
        if (ImGui::Button("Add")) {
            std::string name(nameBuf);
            long long phone = atoll(phoneBuf);
            if (addContactToDB(name, phone)) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "Contact added!");
                nameBuf[0] = phoneBuf[0] = '\0';
            }
            else {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Failed to add contact.");
            }
        }

        ImGui::Separator();
        ImGui::Text("Search Contact:");
        ImGui::InputText("Search Name", searchBuf, IM_ARRAYSIZE(searchBuf));
        if (ImGui::Button("Search")) {
            std::string query(searchBuf);
            searchResults.clear();
            searchResults = getContactsMatching(query);
        }
        ImGui::Combo("Sort By", &sortMode, sortOptions, IM_ARRAYSIZE(sortOptions));

        // sort search result based on selected mode
        switch (sortMode) {
        case 1:
            std::sort(searchResults.begin(), searchResults.end(),
                [](auto& a, auto& b) { return a.first < b.first; });  // name asc
            break;
        case 2:
            std::sort(searchResults.begin(), searchResults.end(),
                [](auto& a, auto& b) { return a.first > b.first; });  // name desc
            break;
        case 3:
            std::sort(searchResults.begin(), searchResults.end(),
                [](auto& a, auto& b) { return a.second < b.second; });  // phone asc
            break;
        case 4:
            std::sort(searchResults.begin(), searchResults.end(),
                [](auto& a, auto& b) { return a.second > b.second; });  // phone desc
            break;
        }


        if (!searchResults.empty()) {
            ImGui::Text("Results:");
            for (auto& [name, phone] : searchResults) {
                ImGui::Text("%s - %lld", name.c_str(), phone);
                ImGui::SameLine();

                std::string deleteBtnLabel = "Delete##" + name;
                if (ImGui::Button(deleteBtnLabel.c_str())) {
                    deleteContactFromDB(name);
                    searchResults = getAllContacts();
                }
            }
        }


        if (ImGui::Button("Show All Contacts")) {
            searchResults = getAllContacts();
        }
        if (ImGui::Button("Clear All Contacts")) {
            if (ImGui::BeginPopupModal("Confirm Clear", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Are you sure you want to delete ALL contacts?");
                if (ImGui::Button("Yes")) {
                    clearAllContactsFromDB();
                    searchResults.clear();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("No")) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::OpenPopup("Confirm Clear");
        }


        ImGui::End();

        // Render imgui draw data
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup imgui and glfw
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
