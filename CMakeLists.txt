cmake_minimum_required(VERSION 3.25)

project(
        Image_Viewer 
        LANGUAGES CXX 
        VERSION 1.0.0 
        HOMEPAGE_URL https://github.com/wikko75/Image-Viewer.git 
)

message(STATUS "Building with CMake ...  ${CMAKE_VERSION}")

find_package(imgui   CONFIG REQUIRED)
find_package(glfw3   CONFIG REQUIRED)
find_package(glew    CONFIG REQUIRED)
find_package(OpenCV  CONFIG REQUIRED)
find_package(glm     CONFIG REQUIRED)


if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options(
	-Wextra
	-Wconversion
	-Wall
	-pedantic
	-Wshadow
	-g
    )
else()
    add_compile_options(
	-Wextra
	-Wconversion
	-Wall
	-pedantic
	-Wshadow
    )
endif()

add_executable(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(bindings)

target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
        imgui::imgui
        glfw 
        GLEW::GLEW
        opencv::opencv
        glm::glm
)

target_include_directories(${PROJECT_NAME} 
        PRIVATE
        inc
)

install(TARGETS ${PROJECT_NAME} DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
