cmake_minimum_required(VERSION 3.16)
project(tester VERSION 0.0.1)

# imgui compile
# Set where the ImGui files are stored
set(IMGUI_PATH  "libs/imgui")
    
# Compile as static library 
file(GLOB IMGUI_SOURCES 
    ${IMGUI_PATH}/*.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp    
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp    
) 
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})


# add files to a list
file(GLOB SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/tribe/*.cpp
    ${PROJECT_SOURCE_DIR}/tribe/render/*.cpp
    ${PROJECT_SOURCE_DIR}/tribe/hierarchy/*.cpp
    ${PROJECT_SOURCE_DIR}/tribe/hierarchy/components/*.cpp
)

# add file list to project executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# libraries
find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} 
    glfw
    OpenGL::GL
    ImGui
    spdlog::spdlog_header_only
)

# precompiled header
target_precompile_headers(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/tribe/pch.cpp)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON) # only works for clang

# set standard to c++20
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# set warning level 4 and warnings treated as errors
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()