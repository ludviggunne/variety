
cmake_minimum_required(VERSION 3.17)

project(variety)

add_subdirectory(extern/glfw)

add_executable(${PROJECT_NAME}

    variety/src/gl/gl.cpp
    variety/src/gl/attributes.cpp
    variety/src/gl/misc.cpp
    variety/src/gl/program.cpp
    variety/src/gl/vertex_array.cpp
    variety/src/gl/vertex.cpp
    
    variety/src/app.cpp
    variety/src/camera.cpp
    variety/src/main.cpp
    variety/src/meshbuilder.cpp
    variety/src/settings.cpp
    

    extern/imgui/imgui/imgui.cpp
    extern/imgui/imgui/imgui_demo.cpp
    extern/imgui/imgui/imgui_draw.cpp
    extern/imgui/imgui/imgui_tables.cpp
    extern/imgui/imgui/imgui_widgets.cpp
    extern/imgui/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/imgui/backends/imgui_impl_opengl3.cpp


    extern/glad/src/glad.c

)

target_include_directories(${PROJECT_NAME}

PRIVATE

    extern/glad/include/

    extern/imgui/imgui/

    extern/glfw/include/
    extern/glm/
    extern/exprtk/

)

target_link_libraries(${PROJECT_NAME} glfw)

add_compile_definitions(V_DEBUG)
target_compile_options(${PROJECT_NAME} PRIVATE "/bigobj")