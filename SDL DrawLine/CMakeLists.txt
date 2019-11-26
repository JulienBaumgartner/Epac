cmake_minimum_required(VERSION 3.10)
project(SoftwareGL)
find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
add_library(SoftwareGL STATIC
${PROJECT_SOURCE_DIR}/DrawLine/Algebra.h
${PROJECT_SOURCE_DIR}/DrawLine/Camera.cpp
${PROJECT_SOURCE_DIR}/DrawLine/Camera.h
${PROJECT_SOURCE_DIR}/DrawLine/EventsManagerInterface.h
${PROJECT_SOURCE_DIR}/DrawLine/Image.cpp
${PROJECT_SOURCE_DIR}/DrawLine/Image.h
${PROJECT_SOURCE_DIR}/DrawLine/Mesh.cpp
${PROJECT_SOURCE_DIR}/DrawLine/Mesh.h
${PROJECT_SOURCE_DIR}/DrawLine/Vertex.h
)
target_link_libraries(SoftwareGL PRIVATE
    SDL2::SDL2
    GLEW::GLEW
)
add_executable(Game
${PROJECT_SOURCE_DIR}/DrawLine/main.cpp
${PROJECT_SOURCE_DIR}/DrawLine/EventsManagerExample.cpp
${PROJECT_SOURCE_DIR}/DrawLine/EventsManagerExample.h
${PROJECT_SOURCE_DIR}/DrawLine/Window.cpp
${PROJECT_SOURCE_DIR}/DrawLine/Window.h
)
target_link_libraries(Game PRIVATE
    SoftwareGL
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
)
add_executable(gl_shader
${PROJECT_SOURCE_DIR}/gl_shader/main.cpp
${PROJECT_SOURCE_DIR}/gl_shader/EventsManagerShaderGl.cpp
${PROJECT_SOURCE_DIR}/gl_shader/EventsManagerShaderGl.h
${PROJECT_SOURCE_DIR}/gl_shader/WindowShaderGl.cpp
${PROJECT_SOURCE_DIR}/gl_shader/WindowShaderGl.h
    )
target_link_libraries(gl_shader PRIVATE
    SoftwareGL
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW)


