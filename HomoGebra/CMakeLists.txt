cmake_minimum_required(VERSION 3.20)
project(HomoGebra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio system REQUIRED)
# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(IMGUI_DIR "C:/imgui")

# Add ImGui source files
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_stdlib.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui-SFML.cpp
)

# Specify the path to the library
set(THOR_INCLUDE_PATH "C:/thor-v2.0-msvc2015/include")

# Add the library
add_library(Thor SHARED IMPORTED GLOBAL)
set_target_properties(Thor PROPERTIES
    IMPORTED_LOCATION_DEBUG "C:/thor-v2.0-msvc2015/bin/thor-d.dll"
    IMPORTED_IMPLIB_DEBUG "C:/thor-v2.0-msvc2015/bin/thor-d.lib"
    IMPORTED_LOCATION_REALESE "C:/thor-v2.0-msvc2015/bin/thor.dll"
    IMPORTED_IMPLIB_REALESE "C:/thor-v2.0-msvc2015/bin/thor.lib"
)

file(GLOB SOURCES "*.cpp")

# Add ImGui source files to your target
add_executable(HomoGebra ${SOURCES} ${IMGUI_SOURCES})

# Link SFML, ImGui to your target and Thor
target_link_libraries(HomoGebra sfml-graphics sfml-audio sfml-system Thor ${OPENGL_LIBRARIES})
target_include_directories(HomoGebra PRIVATE "${THOR_INCLUDE_PATH}")
target_include_directories(HomoGebra PRIVATE "${IMGUI_DIR}")

target_compile_definitions(HomoGebra PRIVATE _DEBUG=1)