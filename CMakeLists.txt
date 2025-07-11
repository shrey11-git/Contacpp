cmake_minimum_required(VERSION 3.15)
project(Contacpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    app_gui.cpp
    db.cpp
    gui_main.cpp
    sqlite/sqlite3.c
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

set(HEADERS
    app_gui.h
    db.h
    gui.h
    sqlite/sqlite3.h
    imgui/*.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
    ${CMAKE_SOURCE_DIR}/glfw/include
    ${CMAKE_SOURCE_DIR}/sqlite
)

# GLFW (assumes you have it built already or included as source)
add_subdirectory(glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glfw
    OpenGL::GL
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "IMGUI_IMPL_OPENGL_LOADER_GLAD")
